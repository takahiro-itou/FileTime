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

inline  void
ErrorDetectionCode::processBlock(
        const   LpcReadBuf  inBuf,
        EDWordType          regs[4])
{
}

}   //  End of namespace  Common
FILETIME_NAMESPACE_END
