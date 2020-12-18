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
