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
**      An Implementation of ErrorDetectionCode class.
**
**      @file       Common/ErrorDetectionCode.cpp
**/

#include    "FileTime/Common/ErrorDetectionCode.h"

#include    <iomanip>
#include    <iostream>
#include    <memory.h>


FILETIME_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

const   BtByte  s_tblPadding[64] = {
    0x80, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,
    0, 0, 0, 0,     0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,
    0, 0, 0, 0,     0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,
    0, 0, 0, 0,     0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0
};

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    ErrorDetectionCode  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

ErrorDetectionCode::ErrorDetectionCode()
    : m_context()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ErrorDetectionCode::~ErrorDetectionCode()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    ハッシュ値の計算バッファを初期化する。
//

ErrCode
ErrorDetectionCode::initializeHash()
{
    this->m_context.regs[0] = 0x67452301;
    this->m_context.regs[1] = 0xEFCDAB89;
    this->m_context.regs[2] = 0x98BADCFE;
    this->m_context.regs[3] = 0x10325476;
    this->m_context.numByte = 0;
    memset(this->m_context.buffer, 0, sizeof(this->m_context.buffer));

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    ハッシュ値の計算バッファを更新する。
//

ErrCode
ErrorDetectionCode::updateHash(
        const   LpcReadBuf  inBuf,
        const   FileLength  cbBuf)
{
    LpcByte         lpInput = static_cast<LpcByte>(inBuf);
    LpByte  const   buffer  = this->m_context.buffer;

    FileLength  bufPos  = ((this->m_context.numByte) & 0x3F);
    this->m_context.numByte += cbBuf;

    size_t  cbCopy  = BLOCK_BYTES - bufPos;
    FileLength  remLen  = cbBuf;

    if ( cbCopy <= cbBuf ) {
        memcpy(buffer + bufPos, lpInput, cbCopy);
        lpInput += cbCopy;
        remLen  -= cbCopy;
        bufPos  = 0;
        processBlock(buffer, this->m_context.regs);
    }

    for ( ; remLen >= BLOCK_BYTES ;
            lpInput += BLOCK_BYTES, remLen -= BLOCK_BYTES )
    {
        processBlock(lpInput, this->m_context.regs);
    }

    memcpy(buffer + bufPos, lpInput, remLen);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    ハッシュ値の計算を完了する。
//

ErrorDetectionCode::EDCode
ErrorDetectionCode::finalizeHash()
{
    BtByte  bits[8];

    const   FileLength  cbByte  = (this->m_context.numByte);
    const   FileLength  cbBits  = (cbByte << 3);

    bits[0] = ((cbBits      ) & 0xFF);
    bits[1] = ((cbBits >>  8) & 0xFF);
    bits[2] = ((cbBits >> 16) & 0xFF);
    bits[3] = ((cbBits >> 24) & 0xFF);
    bits[4] = ((cbBits >> 32) & 0xFF);
    bits[5] = ((cbBits >> 40) & 0xFF);
    bits[6] = ((cbBits >> 48) & 0xFF);
    bits[7] = ((cbBits >> 56) & 0xFF);

    //  パディングを実施。  //
    const   FileLength  padLen  = (120 - cbByte) & 0x3F;
    updateHash(s_tblPadding, padLen);

    //  パディング前のビット数を追加。  //
    updateHash(bits, sizeof(bits));

    return ( getHashValue() );
}

//----------------------------------------------------------------
//    計算したハッシュ値を取得する。
//

ErrorDetectionCode::EDCode
ErrorDetectionCode::getHashValue()  const
{
    EDCode  output;

    output.words[0] = this->m_context.regs[0];
    output.words[1] = this->m_context.regs[1];
    output.words[2] = this->m_context.regs[2];
    output.words[3] = this->m_context.regs[3];

    return ( output );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    指定した 16 ワードブロックを処理する。
//

#define     F(x, y, z)  ( ((x) & (y)) | ((~(x)) & (z)) )
#define     G(x, y, z)  ( ((x) & (z)) | ((y) & (~(z))) )
#define     H(x, y, z)  ( (x) ^ (y) ^ (z) )
#define     I(x, y, z)  ( (y) ^ ((x) | (~(z))) )

#define     ROTATE_LEFT(x, n)   ( ((x) << (n)) | ((x) >> (32 - (n))) )

#define     ROUND_OPERATION(A, B, C, D, OPE, xk, s, sin)    {           \
    (A) += OPE((B), (C), (D)) + (xk) + static_cast<EDWordType>(sin);    \
    (A) = ROTATE_LEFT((A), (s));                                        \
    (A) += (B);                                                         \
}

#define     ROUND1(A, B, C, D, X, k, s, sin)    \
    ROUND_OPERATION(A, B, C, D, F, X[k], s, sin)

#define     ROUND2(A, B, C, D, X, k, s, sin)    \
    ROUND_OPERATION(A, B, C, D, G, X[k], s, sin)

#define     ROUND3(A, B, C, D, X, k, s, sin)    \
    ROUND_OPERATION(A, B, C, D, H, X[k], s, sin)

#define     ROUND4(A, B, C, D, X, k, s, sin)    \
    ROUND_OPERATION(A, B, C, D, I, X[k], s, sin)

inline  void
ErrorDetectionCode::processBlock(
        const   LpcByte     inBuf,
        EDWordType          regs[4])
{
    EDWordType  x[16];
    EDWordType  a   = regs[0];
    EDWordType  b   = regs[1];
    EDWordType  c   = regs[2];
    EDWordType  d   = regs[3];

    for ( int idx = 0, j = 0; idx < 16; ++ idx, j += 4 ) {
        x[idx]  = static_cast<EDWordType>(inBuf[j])
                        | (static_cast<EDWordType>(inBuf[j + 1]) <<  8)
                        | (static_cast<EDWordType>(inBuf[j + 2]) << 16)
                        | (static_cast<EDWordType>(inBuf[j + 3]) << 24);
    }

    //  ROUND1  //
    ROUND1(a, b, c, d, x,  0,  7, 0xD76AA478);
    ROUND1(d, a, b, c, x,  1, 12, 0xE8C7B756);
    ROUND1(c, d, a, b, x,  2, 17, 0x242070DB);
    ROUND1(b, c, d, a, x,  3, 22, 0xC1BDCEEE);

    ROUND1(a, b, c, d, x,  4,  7, 0xF57C0FAF);
    ROUND1(d, a, b, c, x,  5, 12, 0x4787C62A);
    ROUND1(c, d, a, b, x,  6, 17, 0xA8304613);
    ROUND1(b, c, d, a, x,  7, 22, 0xFD469501);

    ROUND1(a, b, c, d, x,  8,  7, 0x698098D8);
    ROUND1(d, a, b, c, x,  9, 12, 0x8B44F7AF);
    ROUND1(c, d, a, b, x, 10, 17, 0xFFFF5BB1);
    ROUND1(b, c, d, a, x, 11, 22, 0x895CD7BE);

    ROUND1(a, b, c, d, x, 12,  7, 0x6B901122);
    ROUND1(d, a, b, c, x, 13, 12, 0xFD987193);
    ROUND1(c, d, a, b, x, 14, 17, 0xA679438E);
    ROUND1(b, c, d, a, x, 15, 22, 0x49B40821);

    //  ROUND2  //
    ROUND2(a, b, c, d, x,  1,  5, 0xF61E2562);
    ROUND2(d, a, b, c, x,  6,  9, 0xC040B340);
    ROUND2(c, d, a, b, x, 11, 14, 0x265E5A51);
    ROUND2(b, c, d, a, x,  0, 20, 0xE9B6C7AA);

    ROUND2(a, b, c, d, x,  5,  5, 0xD62F105D);
    ROUND2(d, a, b, c, x, 10,  9, 0x02441453);
    ROUND2(c, d, a, b, x, 15, 14, 0xD8A1E681);
    ROUND2(b, c, d, a, x,  4, 20, 0xE7D3FBC8);

    ROUND2(a, b, c, d, x,  9,  5, 0x21E1CDE6);
    ROUND2(d, a, b, c, x, 14,  9, 0xC33707D6);
    ROUND2(c, d, a, b, x,  3, 14, 0xF4D50D87);
    ROUND2(b, c, d, a, x,  8, 20, 0x455A14ED);

    ROUND2(a, b, c, d, x, 13,  5, 0xA9E3E905);
    ROUND2(d, a, b, c, x,  2,  9, 0xFCEFA3F8);
    ROUND2(c, d, a, b, x,  7, 14, 0x676F02D9);
    ROUND2(b, c, d, a, x, 12, 20, 0x8D2A4C8A);

    //  ROUND3  //
    ROUND3(a, b, c, d, x,  5,  4, 0xFFFA3942);
    ROUND3(d, a, b, c, x,  8, 11, 0x8771F681);
    ROUND3(c, d, a, b, x, 11, 16, 0x6D9D6122);
    ROUND3(b, c, d, a, x, 14, 23, 0xFDE5380C);

    ROUND3(a, b, c, d, x,  1,  4, 0xA4BEEA44);
    ROUND3(d, a, b, c, x,  4, 11, 0x4BDECFA9);
    ROUND3(c, d, a, b, x,  7, 16, 0xF6BB4B60);
    ROUND3(b, c, d, a, x, 10, 23, 0xBEBFBC70);

    ROUND3(a, b, c, d, x, 13,  4, 0x289B7EC6);
    ROUND3(d, a, b, c, x,  0, 11, 0xEAA127FA);
    ROUND3(c, d, a, b, x,  3, 16, 0xD4EF3085);
    ROUND3(b, c, d, a, x,  6, 23, 0x04881D05);

    ROUND3(a, b, c, d, x,  9,  4, 0xD9D4D039);
    ROUND3(d, a, b, c, x, 12, 11, 0xE6DB99E5);
    ROUND3(c, d, a, b, x, 15, 16, 0x1FA27CF8);
    ROUND3(b, c, d, a, x,  2, 23, 0xC4AC5665);

    //  ROUND4  //
    ROUND4(a, b, c, d, x,  0,  6, 0xF4292244);
    ROUND4(d, a, b, c, x,  7, 10, 0x432AFF97);
    ROUND4(c, d, a, b, x, 14, 15, 0xAB9423A7);
    ROUND4(b, c, d, a, x,  5, 21, 0xFC93A039);

    ROUND4(a, b, c, d, x, 12,  6, 0x655B59C3);
    ROUND4(d, a, b, c, x,  3, 10, 0x8F0CCC92);
    ROUND4(c, d, a, b, x, 10, 15, 0xFFEFF47D);
    ROUND4(b, c, d, a, x,  1, 21, 0x85845DD1);

    ROUND4(a, b, c, d, x,  8,  6, 0x6FA87E4F);
    ROUND4(d, a, b, c, x, 15, 10, 0xFE2CE6E0);
    ROUND4(c, d, a, b, x,  6, 15, 0xA3014314);
    ROUND4(b, c, d, a, x, 13, 21, 0x4E0811A1);

    ROUND4(a, b, c, d, x,  4,  6, 0xF7537E82);
    ROUND4(d, a, b, c, x, 11, 10, 0xBD3AF235);
    ROUND4(c, d, a, b, x,  2, 15, 0x2AD7D2BB);
    ROUND4(b, c, d, a, x,  9, 21, 0xEB86D391);

    regs[0] += a;
    regs[1] += b;
    regs[2] += c;
    regs[3] += d;
}

}   //  End of namespace  Common
FILETIME_NAMESPACE_END
