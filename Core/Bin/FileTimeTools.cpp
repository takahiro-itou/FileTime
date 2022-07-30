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

#include    "FileTime/Common/FileTimeSettings.h"

#include    <iostream>
#include    <getopt.h>

#include    <string>
#include    <vector>

using   namespace   FILETIME_NAMESPACE;

typedef     std::vector<std::string>    StringArray;
struct AppOpts {
    std::string     refFile;
    std::string     tmStamp;
    StringArray     targetFiles;
};

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
    std::cerr   <<  "Targets:";
    for ( size_t i = 0; i < appOpts.targetFiles.size(); ++ i ) {
        std::cerr   <<  appOpts.targetFiles[i]  <<  ",";
    }
    std::cerr   <<  std::endl;

    return ( 0 );
}
