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
**      Type Definitions.
**
**      @file       Common/FileTimeTypes.h
**/

#if !defined( FILETIME_COMMON_INCLUDED_FILE_TIME_TYPES_H )
#    define   FILETIME_COMMON_INCLUDED_FILE_TIME_TYPES_H

#include    "FileTimeSettings.h"

#include    <cstdint>
#include    <stddef.h>


FILETIME_NAMESPACE_BEGIN

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    エラーコード。
**/

enum  ErrCode
{
    /**   正常終了。    **/
    ERR_SUCCESS             = 0,

    /**   異常終了。エラーの理由は不明または報告なし。  **/
    ERR_FAILURE             = 1,

    /**   ファイルオープンエラー。  **/
    ERR_FILE_OPEN_ERROR     = 2,

    /**   ファイル入出力エラー。    **/
    ERR_FILE_IO_ERROR       = 3,

    /**   パーミッションエラー。    **/
    ERR_PERMISSION_ERROR    = 4
};

//----------------------------------------------------------------
/**
**    型安全なブール型。
**/

enum  Boolean
{
    BOOL_FALSE  = 0,        /**<  偽。  **/
    BOOL_TRUE   = 1         /**<  真。  **/
};

//----------------------------------------------------------------
/**
**    ファイルの長さを表す型。
**/

typedef     size_t              FileLength;

//----------------------------------------------------------------
/**
**    読み取り専用バッファ。
**/

typedef     const  void  *      LpcReadBuf;

//----------------------------------------------------------------
/**
**    読み書き両用バッファ。
**/

typedef     void  *             LpWriteBuf;

//----------------------------------------------------------------
/**
**    バイト型。
**/

typedef     unsigned char       BtByte;

/**
**    バイト型の読み取り専用バッファ。
**/

typedef     const  BtByte  *    LpcByte;

/**
**    バイト型の読み書き両用バッファ。
**/

typedef     BtByte  *           LpByte;

//========================================================================
//
//    安全なポインタ型のキャスト。
//

template  <typename  T>
T  pointer_cast(void  *  p)
{
    return ( static_cast<T>(p) );
}

template  <typename  T>
T  pointer_cast(const  void  *  p)
{
    return ( static_cast<T>(p) );
}

FILETIME_NAMESPACE_END

#endif
