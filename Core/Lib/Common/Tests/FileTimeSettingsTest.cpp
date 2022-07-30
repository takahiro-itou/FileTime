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
**      An Implementation of Test Case 'FileTimeSettings'.
**
**      @file       Common/Tests/FileTimeSettingsTest.cpp
**/

#include    "TestDriver.h"
#include    "FileTime/Common/FileTimeSettings.h"

FILETIME_NAMESPACE_BEGIN

//========================================================================
//
//    FileTimeSettingsTest  class.
//
/**
**    クラス FileTimeSettings の単体テスト。
**/

class  FileTimeSettingsTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(FileTimeSettingsTest);
    CPPUNIT_TEST(testNameSpace);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testNameSpace();
};

CPPUNIT_TEST_SUITE_REGISTRATION( FileTimeSettingsTest );

//========================================================================
//
//    Tests.
//

void  FileTimeSettingsTest::testNameSpace()
{
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
