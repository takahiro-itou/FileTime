
dnl----------------------------------------------------------------
dnl
dnl   Package Configurations.
dnl   パッケージ設定。
dnl

dnl
dnl   要求する autoconf のバージョンを指定する。
dnl

AC_PREREQ([2.68])

dnl
dnl   パッケージの情報を指定する。
dnl

AC_INIT(
    [FileTime],
    [0.0.0],
    [BUG-REPORT-ADDRESS],
    [FileTime])

dnl
dnl   ツールの出力ディレクトリを指定する。
dnl

AC_CONFIG_AUX_DIR([.Config])

dnl
dnl   適当なバージョンの automake を設定
dnl

m4_include([.M4/InitAutoMake.m4])

dnl----------------------------------------------------------------
dnl
dnl   プロジェクトの基本設定。
dnl

AC_CONFIG_SRCDIR([Makefile.am])
AC_LANG([C++])

dnl
dnl   デフォルトのコンパイルオプション
dnl

myac_build_type=${AUTOMAKE_BUILD_TYPE:-'Debug'}

myac_cxx_warning_flags='-Wall -Weffc++'
myac_c_warning_flags='-Wall'

myac_cxxflags_debug='-O0 -g -D_DEBUG'
myac_cflags_debug='-O0 -g -D_DEBUG'

myac_saved_CXXFLAGS=${CXXFLAGS:-''}
myac_saved_CFLAGS=${CFLAGS:-''}

myac_cxxflags="${myac_cxxflags_debug}   ${myac_saved_CXXFLAGS}"
myac_cflags="${myac_cflags_debug}   ${myac_saved_CFLAGS}"

CXXFLAGS="${myac_cxxflags} ${myac_cxx_warning_flags}"
CFLAGS="${myac_cflags} ${myac_c_warning_flags}"

dnl
dnl   Project Name Space.
dnl

FILETIME_CNF_NAMESPACE=FileTime
AC_SUBST(FILETIME_CNF_NAMESPACE)

dnl----------------------------------------------------------------
dnl
dnl   ディレクトリ名。
dnl

m4_include([.M4/ConfigDirectory.m4])

MYAC_CUSTOMIZE_LIBRARY_DIR([Lib])
MYAC_CUSTOMIZE_BINARY_DIR([Bin])
MYAC_CUSTOMIZE_INCLUDE_DIR(
    [Include], [FileTime], [.Config], [Config.h])

dnl----------------------------------------------------------------
dnl
dnl   ビルド環境の検査。
dnl

dnl
dnl   Check Programs.
dnl

AC_PROG_CC
AC_PROG_CXX
AM_PROG_AS
AC_PROG_RANLIB

dnl
dnl   Check Header Files.
dnl

dnl
dnl   Check Libraries.
dnl

dnl
dnl   Check Types.
dnl

dnl
dnl   Check Extra Compiler/Linker Options.
dnl

m4_include([.M4/CheckExtraFlags.m4])

m4_include([.M4/EnableCxx11.m4])

dnl----------------------------------------------------------------
dnl
dnl   Additional Packages.
dnl   外部パッケージの追加
dnl

m4_include([.M4/WithExtPkgs.m4])

m4_include([.M4/Packages/CppUnit.m4])

dnl----------------------------------------------------------------
dnl
dnl   Linker Scripts.
dnl   リンカスクリプトを生成する。
dnl

m4_include([Lib/.LinkerScript/LinkerScripts.m4])

dnl----------------------------------------------------------------
dnl
dnl   Outputs.
dnl   出力ファイルを設定する。
dnl

dnl
dnl   Basic Features.
dnl

AC_CONFIG_FILES([
    .CMake/Makefile
    .M4/Makefile
    Makefile
    Bin/Makefile
    Lib/Makefile
    Lib/.Config/Makefile
    Lib/Common/Makefile
])

AC_CONFIG_FILES([
    Include/FileTime/.Config/ConfiguredFileTime.h
])

dnl
dnl   Test Festures.
dnl

AC_CONFIG_FILES([
    Lib/Common/Tests/Makefile
    Lib/Tests/Makefile
])

dnl
dnl   指定したファイルを生成する。
dnl

AC_OUTPUT

