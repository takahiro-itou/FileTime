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
**      An Interface of ErrorDetectionCode class.
**
**      @file       Common/ErrorDetectionCode.h
**/

#if !defined( FILETIME_COMMON_INCLUDED_ERROR_DETECTION_CODE_H )
#    define   FILETIME_COMMON_INCLUDED_ERROR_DETECTION_CODE_H

#include    "FileTimeTypes.h"

#include    <iosfwd>
#include    <string>

FILETIME_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //

//========================================================================
//
//    ErrorDetectionCode  class.
//

class  ErrorDetectionCode
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**   ワード型は 32 ビット。    **/
    typedef     uint32_t        EDWordType;

    /**   誤り検出符号を格納する型。    **/
    //typedef     EDWordType      EDCode[4];
    struct  EDCode  {
        EDWordType  words[4];
    };

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    ErrorDetectionCode();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~ErrorDetectionCode();

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
    /**   ハッシュ値の計算バッファを初期化する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    initializeHash();

    //----------------------------------------------------------------
    /**   ハッシュ値の計算バッファを更新する。
    **
    **  @param [in] inBuf   入力データのアドレス。
    **  @param [in] cbBuf   入力データのバイト数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    updateHash(
            const  LpcReadBuf   inBuf,
            const  FileLength   cbBuf);

    //----------------------------------------------------------------
    /**   ハッシュ値の計算を完了する。
    **
    **    計算した値はキャッシュに保存しておく。
    **
    **  @return    計算した値を返す。
    **/
    EDCode
    finalizeHash();

    //----------------------------------------------------------------
    /**   計算したハッシュ値を取得する。
    **
    **  @return   計算した値をキャッシュから返す。
    **/
    EDCode
    getHashValue()  const;

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   ErrorDetectionCodeTest;
};

}   //  End of namespace  Common
FILETIME_NAMESPACE_END

#endif
