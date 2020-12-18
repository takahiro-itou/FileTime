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
**      An Implementation of Test Case 'ErrorDetectionCode'.
**
**      @file       Common/Tests/ErrorDetectionCodeTest.cpp
**/

#include    "TestDriver.h"
#include    "FileTime/Common/ErrorDetectionCode.h"

FILETIME_NAMESPACE_BEGIN

//========================================================================
//
//    ErrorDetectionCodeTest  class.
//
/**
**    クラス ErrorDetectionCode の単体テスト。
**/

class  ErrorDetectionCodeTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(ErrorDetectionCodeTest);
    CPPUNIT_TEST(testNameSpace);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testNameSpace();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ErrorDetectionCodeTest );

//========================================================================
//
//    Tests.
//

void  ErrorDetectionCodeTest::testNameSpace()
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
