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

FILETIME_NAMESPACE_BEGIN
namespace  Common  {

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
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    ハッシュ値の計算バッファを更新する。
//

ErrCode
ErrorDetectionCode::updateHash(
        const  LpcReadBuf   inBuf,
        const  FileLength   cbBuf)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    ハッシュ値の計算を完了する。
//

ErrorDetectionCode::EDCode
ErrorDetectionCode::finalizeHash()
{
    return ( getHashValue() );
}

//----------------------------------------------------------------
//    計算したハッシュ値を取得する。
//

ErrorDetectionCode::EDCode
ErrorDetectionCode::getHashValue()  const
{
    EDCode  out;
    return ( out );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Common
FILETIME_NAMESPACE_END
