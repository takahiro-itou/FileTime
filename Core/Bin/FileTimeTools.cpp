//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                      ---  File Time Tools.  ---                      **
**                                                                      **
**          Copyright (C), 2020-2024, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU General Public License (GPL) version 3,                 **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      ツール。
**
**      @file       Bin/FileTimeTools.cpp
**/

#include    "FileTime/Common/FileTimeTypes.h"

#include    <iostream>
#include    <getopt.h>

#include    <string>
#include    <vector>

#include    <windows.h>

using   namespace   FILETIME_NAMESPACE;

typedef     std::vector<std::string>    StringArray;
struct AppOpts {
    std::string     refFile;
    std::string     tmStamp;
    Boolean         overwriteCreation;

    StringArray     targetFiles;

    AppOpts()
        : refFile(),
          tmStamp(),
          overwriteCreation(BOOL_TRUE),
          targetFiles()
    { }
};

struct TimeInfo {
    FILETIME    utcFile;
    FILETIME    localFile;
    SYSTEMTIME  utcSys;
    SYSTEMTIME  localSys;
};

struct TimeStampInfo {
    TimeInfo    creationTime;
    TimeInfo    lastAccessTime;
    TimeInfo    lastWriteTime;
};


//----------------------------------------------------------------

ErrCode
fillTimeInfoFromUtcFileTime(
        TimeInfo &  timeInfo)
{
    ::FileTimeToLocalFileTime(&(timeInfo.utcFile), &(timeInfo.localFile));
    ::FileTimeToSystemTime(&(timeInfo.utcFile), &(timeInfo.utcSys));
    ::FileTimeToSystemTime(&(timeInfo.localFile), &(timeInfo.localSys));

    return ( ERR_SUCCESS );
}

ErrCode
fillTimeInfoFromLocalSystemTime(
        TimeInfo &  timeInfo)
{
    ::SystemTimeToFileTime(&(timeInfo.localSys), &(timeInfo.localFile));
    ::LocalFileTimeToFileTime(&(timeInfo.localFile), &(timeInfo.utcFile));
    ::FileTimeToSystemTime(&(timeInfo.utcFile), &(timeInfo.utcSys));

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
/**   現在時刻を取得する。
**
**/

ErrCode
getCurrentTime(
        TimeStampInfo   & timeStamp)
{
    SYSTEMTIME  systemTime;

    ::GetLocalTime(&systemTime);

    timeStamp.creationTime.localSys     = systemTime;
    timeStamp.lastAccessTime.localSys   = systemTime;
    timeStamp.lastWriteTime.localSys    = systemTime;

    fillTimeInfoFromLocalSystemTime(timeStamp.creationTime);
    fillTimeInfoFromLocalSystemTime(timeStamp.lastAccessTime);
    fillTimeInfoFromLocalSystemTime(timeStamp.lastWriteTime);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
/**   指定したファイルのタイムスタンプを取得する。
**
**/

ErrCode
getReferenceFileTime(
        const std::string & fileName,
        TimeStampInfo     & timeStamp)
{
    BOOL    ret;
    HANDLE  hFile;

    hFile = ::CreateFile(
                fileName.c_str(), GENERIC_READ, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if ( hFile == INVALID_HANDLE_VALUE ) {
        std::cerr   <<  "Cannot access to " <<  fileName
                    <<  ": No such file or directory"   <<  std::endl;
        return ( ERR_FILE_OPEN_ERROR );
    }

    ret = ::GetFileTime(
                hFile,
                &(timeStamp.creationTime.utcFile),
                &(timeStamp.lastAccessTime.utcFile),
                &(timeStamp.lastWriteTime.utcFile));
    ::CloseHandle(hFile);

    if ( ! ret ) {
        return ( ERR_FILE_IO_ERROR );
    }

    //  UTC SYSTEM
    fillTimeInfoFromUtcFileTime(timeStamp.creationTime);
    fillTimeInfoFromUtcFileTime(timeStamp.lastAccessTime);
    fillTimeInfoFromUtcFileTime(timeStamp.lastWriteTime);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
/**   指定した文字列をタイムスタンプに変換する。
**
**/

ErrCode
getFileTimeFromString(
        const std::string & textTime,
        TimeStampInfo     & timeStamp)
{
    const   size_t  len = textTime.length();
    std::vector<int>    work(len);
    size_t  posSec  = len;

    for ( size_t i = 0; i < len; ++ i ) {
        const char c = textTime[i];
        if ( c == '.') {
            posSec  = i;
            continue;
        }
        if ( ('0' <= c) && (c <= '9') ) {
            work[i] = c - '0';
        } else {
            return ( ERR_FAILURE );
        }
    }

    if ( (posSec != len) && (posSec != len - 3) ) {
        //  秒数部分の指定（桁数）が不正。
        return ( ERR_FAILURE );
    }
    if ( posSec < 8 ) {
        //  指定した文字列の桁数が不正。
        return ( ERR_FAILURE );
    }
    const int * ptrBase = nullptr;

    //  年を省略した場合は今の値をそのまま使うのでコピーしておく
    SYSTEMTIME  localTime = timeStamp.lastWriteTime.localSys;

    if ( posSec == 8 ) {
        //  MMDDhhmm
        ptrBase = &(work[0]);
    } else if ( posSec == 10 ) {
        //  YYMMDDhhmm
        ptrBase = &(work[2]);
        const WORD cc = localTime.wYear / 100;
        localTime.wYear = (cc * 100 + work[0] * 10 + work[1]);
    } else if ( posSec == 12 ) {
        //  CCYYMMDDhhmm
        ptrBase = &(work[4]);
        localTime.wYear = (
                work[0] * 1000 + work[1] * 100 + work[2] * 10 + work[3]
        );
    }
    if ( ptrBase == nullptr ) {
        return ( ERR_FAILURE );
    }

    localTime.wMonth    = ptrBase[0] * 10 + ptrBase[1];
    localTime.wDay      = ptrBase[2] * 10 + ptrBase[3];
    localTime.wHour     = ptrBase[4] * 10 + ptrBase[5];
    localTime.wMinute   = ptrBase[6] * 10 + ptrBase[7];

    if ( posSec == len - 3 ) {
        localTime.wSecond   = work[posSec+1] * 10 + work[posSec+2];
    } else {
        localTime.wSecond   = 0;
    }
    localTime.wMilliseconds = 0;

    timeStamp.creationTime.localSys     = localTime;
    timeStamp.lastAccessTime.localSys   = localTime;
    timeStamp.lastWriteTime.localSys    = localTime;

    fillTimeInfoFromLocalSystemTime(timeStamp.creationTime);
    fillTimeInfoFromLocalSystemTime(timeStamp.lastAccessTime);
    fillTimeInfoFromLocalSystemTime(timeStamp.lastWriteTime);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
/**   指定したファイルのタイムスタンプを設定する。
**
**/

ErrCode
setTargetFileTime(
        const  std::string    & fileName,
        const  TimeStampInfo  & timeStamp,
        const  AppOpts        & appOpts)
{
    BOOL    ret;
    HANDLE  hFile;

    hFile = ::CreateFile(
                fileName.c_str(), GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if ( hFile == INVALID_HANDLE_VALUE ) {
        std::cerr   <<  "Cannot access to " <<  fileName
                    <<  std::endl;
        return ( ERR_FILE_OPEN_ERROR );
    }

    const FILETIME * lpCreation = &(timeStamp.creationTime.utcFile);
    if ( ! appOpts.overwriteCreation ) {
        lpCreation  = NULL;
    }

    ret = ::SetFileTime(
                hFile,
                lpCreation,
                &(timeStamp.lastAccessTime.utcFile),
                &(timeStamp.lastWriteTime.utcFile));
    ::CloseHandle(hFile);

    if ( ! ret ) {
        return ( ERR_FILE_IO_ERROR );
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
/**   時刻情報を表示する。
**
**/

std::ostream  &
showTimeInfo(
        const FILETIME *    lpFileTime,
        const SYSTEMTIME *  lpSystemTime,
        std::ostream &      outStr)
{
    char    buf[1024];
    const char *    week[7] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };

    snprintf(
            buf, sizeof(buf),
            "%04d/%02d/%02d (%s) %02d:%02d:%02d.%d [%08lx%08x]",
            lpSystemTime->wYear,
            lpSystemTime->wMonth,
            lpSystemTime->wDay,
            week[lpSystemTime->wDayOfWeek],
            lpSystemTime->wHour,
            lpSystemTime->wMinute,
            lpSystemTime->wSecond,
            lpSystemTime->wMilliseconds,
            lpFileTime->dwHighDateTime,
            lpFileTime->dwLowDateTime);

    return ( outStr << buf );
}

std::ostream  &
showTimeInfo(
        const TimeInfo  & timeInfo,
        std::ostream    & outStr)
{
    outStr  <<  "LOC:";
    showTimeInfo(
            &(timeInfo.localFile), &(timeInfo.localSys), outStr);
    outStr  <<  ", UTC:";
    showTimeInfo(
            &(timeInfo.utcFile), &(timeInfo.utcSys), outStr);
    return ( outStr );
}

//----------------------------------------------------------------

std::ostream  &
showTimeStamp(
        const  TimeStampInfo  & timeStamp,
        std::ostream          & outStr)
{
    outStr  <<  " - Create: ";
    showTimeInfo(timeStamp.creationTime, outStr)
            <<  std::endl   <<  " - Access: ";
    showTimeInfo(timeStamp.lastAccessTime, outStr)
            <<  std::endl   <<  " - Write : ";
    showTimeInfo(timeStamp.lastWriteTime, outStr)
            <<  std::endl;
    return ( outStr );
}

//----------------------------------------------------------------
/**   エントリポイント。
**
**/

int  main(int argc, char * argv[])
{
    AppOpts appOpts;
    int     c;
    ErrCode retErr;
    int     option_index = 0;

    static struct option long_options[] = {
        { "reference", required_argument, 0, 'r' },
        { "no-overwrite-creation", no_argument, 0, 'C' },
        { 0, 0, 0, 0 }
    };

    for (;;) {
        c = getopt_long(
                argc, argv, "Ct:r:",
                long_options, &option_index);
        if ( c == -1 ) {
            break;
        }

        switch ( c ) {
        case 'C':
            appOpts.overwriteCreation = BOOL_FALSE;
            break;
        case 'r':
            appOpts.refFile = std::string(optarg);
            break;
        case 't':
            appOpts.tmStamp = std::string(optarg);
            break;
        }
    }

    appOpts.targetFiles.clear();
    while ( optind < argc ) {
        appOpts.targetFiles.push_back(argv[optind++]);
    }

    std::cerr   <<  "Ref:"  <<  appOpts.refFile <<  std::endl;
    std::cerr   <<  "TS :"  <<  appOpts.tmStamp <<  std::endl;

    TimeStampInfo   timeStamp;

    //  デフォルト値用にで現在時刻を取得しておく。  //
    getCurrentTime(timeStamp);
    if ( ! appOpts.refFile.empty() ) {
        getReferenceFileTime(appOpts.refFile, timeStamp);
        std::cerr   <<  "# INFO : Reference Time :" <<  std::endl;
        showTimeStamp(timeStamp, std::cerr);
    }
    if ( ! appOpts.tmStamp.empty() ) {
        retErr  = getFileTimeFromString(appOpts.tmStamp, timeStamp);
        if ( retErr != ERR_SUCCESS ) {
            std::cerr   <<  "Invalid date format."  <<  std::endl;
            return  ( 1 );
        }
        std::cerr   <<  "# INFO : Specified Time :" <<  std::endl;
        showTimeStamp(timeStamp, std::cerr);
    }

    //  作成日時を最終更新日時に設定する
    if ( appOpts.overwriteCreation ) {
        timeStamp.creationTime  = timeStamp.lastWriteTime;
    } else {
        timeStamp.creationTime.utcFile.dwLowDateTime    = 0;
        timeStamp.creationTime.utcFile.dwHighDateTime   = 0;
        fillTimeInfoFromLocalSystemTime(timeStamp.creationTime);
    }

    //  指定したファイル群のタイムスタンプを設定する。  //
    std::cerr   <<  "Targets:"  <<  std::endl;
    for ( size_t i = 0; i < appOpts.targetFiles.size(); ++ i ) {
        const  std::string  & fnTarget  = appOpts.targetFiles[i];
        std::cout   <<  "\nNow setting time of "
                    <<  fnTarget
                    <<  " to "  <<  std::endl;
        showTimeStamp(timeStamp, std::cout);
        retErr  = setTargetFileTime(fnTarget, timeStamp, appOpts);
        if ( retErr != ERR_SUCCESS ) {
            continue;
        }

        TimeStampInfo   updatedStamp;
        getReferenceFileTime(fnTarget, updatedStamp);
        std::cout   <<  "Checking time of " <<  fnTarget
                    <<  std::endl;
        showTimeStamp(updatedStamp, std::cout);
    }

    return ( 0 );
}
