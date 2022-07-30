//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                      ---  File Time Tools.  ---                      **
**                                                                      **
**          Copyright (C), 2020-2022, Takahiro Itou                     **
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
    StringArray     targetFiles;
};

struct TimeStampInfo {
    FILETIME    ftCreationTime;
    FILETIME    ftLastAccessTime;
    FILETIME    ftLastWriteTime;
};


//----------------------------------------------------------------
/**   現在時刻を取得する。
**
**/

ErrCode
getCurrentTime(
        TimeStampInfo   & timeStamp)
{
    SYSTEMTIME  localTime;

    ::GetLocalTime(&localTime);

    ::SystemTimeToFileTime(&localTime, &(timeStamp.ftCreationTime));
    ::SystemTimeToFileTime(&localTime, &(timeStamp.ftLastAccessTime));
    ::SystemTimeToFileTime(&localTime, &(timeStamp.ftLastWriteTime));

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
    HANDLE  hFile;

    hFile = ::CreateFile(
                fileName.c_str(), GENERIC_READ, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if ( hFile == INVALID_HANDLE_VALUE ) {
        std::cerr   <<  "Cannot access to " <<  fileName
                    <<  ": No such file or directory"   <<  std::endl;
        return ( ERR_FILE_OPEN_ERROR );
    }

    if ( ! ::GetFileTime(
                    hFile,
                    &(timeStamp.ftCreationTime),
                    &(timeStamp.ftLastAccessTime),
                    &(timeStamp.ftLastWriteTime))
    ) {
        return ( ERR_FILE_IO_ERROR );
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
/**   指定したファイルのタイムスタンプを設定する。
**
**/

ErrCode
setTargetFileTime(
        const  std::string    & fileName,
        const  TimeStampInfo  & timeStamp)
{
    HANDLE  hFile;

    hFile = ::CreateFile(
                fileName.c_str(), GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if ( hFile == INVALID_HANDLE_VALUE ) {
        std::cerr   <<  "Cannot access to " <<  fileName
                    <<  std::endl;
        return ( ERR_FILE_OPEN_ERROR );
    }

    if ( ! ::SetFileTime(
                    hFile,
                    &(timeStamp.ftCreationTime),
                    &(timeStamp.ftLastAccessTime),
                    &(timeStamp.ftLastWriteTime))
    ) {
        return ( ERR_FILE_IO_ERROR );
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
/**   エントリポイント。
**
**/

int  main(int argc, char * argv[])
{
    AppOpts appOpts;
    int c;
    int option_index = 0;

    static struct option long_options[] = {
        { "reference", required_argument, 0, 'r' },
        { 0, 0, 0, 0 }
    };

    for (;;) {
        c = getopt_long(
                argc, argv, "t:r:",
                long_options, &option_index);
        if ( c == -1 ) {
            break;
        }

        switch ( c ) {
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
    }

    //  指定したファイル群のタイムスタンプを設定する。  //
    std::cerr   <<  "Targets:"  <<  std::endl;
    for ( size_t i = 0; i < appOpts.targetFiles.size(); ++ i ) {
        const  std::string  & fnTarget  = appOpts.targetFiles[i];
        std::cerr   <<  fnTarget    <<  std::endl;
        setTargetFileTime(fnTarget, timeStamp);
    }

    return ( 0 );
}
