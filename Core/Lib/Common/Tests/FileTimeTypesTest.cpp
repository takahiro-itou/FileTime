//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                      ---  File Time Tools.  ---                      **
**                                                                      **
**          Copyright (C), 2020-2020, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU General Public License (GPL) version 3,                 **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of Test Case 'FileTimeTypes'.
**
**      @file       Common/Tests/FileTimeTypesTest.cpp
**/

#include    "TestDriver.h"
#include    "FileTime/Common/FileTimeTypes.h"

FILETIME_NAMESPACE_BEGIN

//========================================================================
//
//    FileTimeTypesTest  class.
//
/**
**    クラス FileTimeTypes  の単体テスト。
**/

class  FileTimeTypesTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(FileTimeTypesTest);
    CPPUNIT_TEST(testTypes);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testTypes();
};

CPPUNIT_TEST_SUITE_REGISTRATION( FileTimeTypesTest );

#define     FILETIME_HELP_UNUSED_VARIABLE(v)    (void)(v)

//========================================================================
//
//    Tests.
//

void  FileTimeTypesTest::testTypes()
{
    ErrCode     retErr  = ERR_SUCCESS;
    Boolean     bFlags  = BOOL_TRUE;
    FileLength  cbSize  = 0;
    LpcReadBuf  lpRead  = nullptr;
    LpWriteBuf  lpWrite = nullptr;

    FILETIME_HELP_UNUSED_VARIABLE(retErr);
    FILETIME_HELP_UNUSED_VARIABLE(bFlags);
    FILETIME_HELP_UNUSED_VARIABLE(cbSize);
    FILETIME_HELP_UNUSED_VARIABLE(lpRead);
    FILETIME_HELP_UNUSED_VARIABLE(lpWrite);

    return;
}

FILETIME_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
