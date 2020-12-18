
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  FileTimeSettingsTest
    COMMAND  $<TARGET_FILE:FileTimeSettingsTest>
)

Add_Test (NAME  FileTimeTypesTest
    COMMAND  $<TARGET_FILE:FileTimeTypesTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (FileTimeSettingsTest    FileTimeSettingsTest.cpp)
Add_Executable (FileTimeTypesTest       FileTimeTypesTest.cpp)

