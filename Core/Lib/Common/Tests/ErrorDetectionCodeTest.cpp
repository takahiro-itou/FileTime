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
namespace  Common  {

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
    CPPUNIT_TEST(testFinalizeHash);
    CPPUNIT_TEST(testInitializeHash);
    CPPUNIT_TEST(testUpdateHash);

    CPPUNIT_TEST(testHashValue1);
    CPPUNIT_TEST(testHashValue2);
    CPPUNIT_TEST(testHashValue3);
    CPPUNIT_TEST(testHashValue4);
    CPPUNIT_TEST(testHashValue5);
    CPPUNIT_TEST(testHashValue6);
    CPPUNIT_TEST(testHashValue7);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testFinalizeHash();
    void  testGetHashValue();
    void  testInitializeHash();
    void  testUpdateHash();

    void  testHashValue1();
    void  testHashValue2();
    void  testHashValue3();
    void  testHashValue4();
    void  testHashValue5();
    void  testHashValue6();
    void  testHashValue7();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ErrorDetectionCodeTest );

//========================================================================
//
//    Tests.
//

void  ErrorDetectionCodeTest::testFinalizeHash()
{
    ErrorDetectionCode  testee;
    ErrorDetectionCode::EDCode  out;

    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.initializeHash());
    out = testee.finalizeHash();

    CPPUNIT_ASSERT_EQUAL(0xD98C1DD4U, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0x04B2008FU, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0x980980E9U, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0x7E42F8ECU, out.words[3]);

    return;
}

void  ErrorDetectionCodeTest::testGetHashValue()
{
    ErrorDetectionCode  testee;
    ErrorDetectionCode::EDCode  out;

    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.initializeHash());
    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.updateHash("a", 1));
    testee.finalizeHash();
    out = testee.getHashValue();

    CPPUNIT_ASSERT_EQUAL(0xB975C10CU, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0xA8B6F1C0U, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0xE299C331U, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0x61267769U, out.words[3]);

    return;
}

void  ErrorDetectionCodeTest::testInitializeHash()
{
    ErrorDetectionCode  testee;

    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.initializeHash());
    return;
}

void  ErrorDetectionCodeTest::testUpdateHash()
{
    ErrorDetectionCode  testee;
    ErrorDetectionCode::EDCode  out;

    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.initializeHash());
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS, testee.updateHash("message ", 8));
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS, testee.updateHash("digest", 6));

    out = testee.finalizeHash();

    CPPUNIT_ASSERT_EQUAL(0x7D696BF9U, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0x8D93B77CU, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0x312F5A52U, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0xD061F1AAU, out.words[3]);

    return;
}

void  ErrorDetectionCodeTest::testHashValue1()
{
    ErrorDetectionCode  testee;
    ErrorDetectionCode::EDCode  out;

    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.initializeHash());
    out = testee.finalizeHash();

    CPPUNIT_ASSERT_EQUAL(0xD98C1DD4U, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0x04B2008FU, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0x980980E9U, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0x7E42F8ECU, out.words[3]);

    return;
}

void  ErrorDetectionCodeTest::testHashValue2()
{
    ErrorDetectionCode  testee;
    ErrorDetectionCode::EDCode  out;

    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.initializeHash());
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS, testee.updateHash("a", 1));
    out = testee.finalizeHash();

    CPPUNIT_ASSERT_EQUAL(0xB975C10CU, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0xA8B6F1C0U, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0xE299C331U, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0x61267769U, out.words[3]);

    return;
}

void  ErrorDetectionCodeTest::testHashValue3()
{
    ErrorDetectionCode  testee;
    ErrorDetectionCode::EDCode  out;

    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.initializeHash());
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS, testee.updateHash("abc", 3));
    out = testee.finalizeHash();

    CPPUNIT_ASSERT_EQUAL(0x98500190U, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0xB04FD23CU, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0x7D3F96D6U, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0x727FE128U, out.words[3]);

    return;
}

void  ErrorDetectionCodeTest::testHashValue4()
{
    ErrorDetectionCode  testee;
    ErrorDetectionCode::EDCode  out;

    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.initializeHash());
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS, testee.updateHash("message digest", 14));
    out = testee.finalizeHash();

    CPPUNIT_ASSERT_EQUAL(0x7D696BF9U, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0x8D93B77CU, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0x312F5A52U, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0xD061F1AAU, out.words[3]);

    return;
}

void  ErrorDetectionCodeTest::testHashValue5()
{
    ErrorDetectionCode  testee;
    ErrorDetectionCode::EDCode  out;
    const  char  MSG[]  = "abcdefghijklmnopqrstuvwxyz";

    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.initializeHash());
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS, testee.updateHash(MSG, sizeof(MSG) - 1));
    out = testee.finalizeHash();

    CPPUNIT_ASSERT_EQUAL(0xD7D3FCC3U, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0x00E49261U, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0x6C49FB7DU, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0x3BE167CAU, out.words[3]);

    return;
}

void  ErrorDetectionCodeTest::testHashValue6()
{
    ErrorDetectionCode  testee;
    ErrorDetectionCode::EDCode  out;
    const  char  MSG1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcde";
    const  char  MSG2[] = "fghijklmnopqrstuvwxyz0123456789";

    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.initializeHash());
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS, testee.updateHash(MSG1, sizeof(MSG1) - 1));
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS, testee.updateHash(MSG2, sizeof(MSG2) - 1));
    out = testee.finalizeHash();

    CPPUNIT_ASSERT_EQUAL(0x98AB74D1U, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0xF5D977D2U, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0x2C1C61A5U, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0x9F9D419FU, out.words[3]);

    return;
}

void  ErrorDetectionCodeTest::testHashValue7()
{
    ErrorDetectionCode  testee;
    ErrorDetectionCode::EDCode  out;
    const  char  MSG1[] = "1234567890123456789012345678901";
    const  char  MSG2[] = "23456789012345678901234567890123456";
    const  char  MSG3[] = "78901234567890";

    CPPUNIT_ASSERT_EQUAL(ERR_SUCCESS, testee.initializeHash());
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS, testee.updateHash(MSG1, sizeof(MSG1) - 1));
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS, testee.updateHash(MSG2, sizeof(MSG2) - 1));
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS, testee.updateHash(MSG3, sizeof(MSG3) - 1));
    out = testee.finalizeHash();

    CPPUNIT_ASSERT_EQUAL(0xA2F4ED57U, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0x55C9E32BU, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0x2EDA49ACU, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0x7AB60721U, out.words[3]);

    return;
}

}   //  End of namespace  Common
FILETIME_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
