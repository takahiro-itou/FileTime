
##
##    List of Tests.
##

EXTRATESTS              =
TESTS                   =  \
        FileTimeSettingsTest    \
        FileTimeTypesTest       \
        ${EXTRATESTS}
##
##    Test Configurations.
##

TARGET_TESTEE_LIBRARY       +=

DIST_NOINST_DATA_FILES      +=
DIST_NOINST_HEADER_FILES    +=
EXTRA_TEST_DRIVERS          +=
LIBRARY_TEST_DRIVERS        +=
SOURCE_TEST_DRIVERS         +=

##
##    Compile and Link Options.
##

TEST_CPPFLAGS_COMMON        +=
TEST_LDFLAGS_COMMON         +=

##
##    Test Programs.
##

FileTimeSettingsTest_SOURCES    =  FileTimeSettingsTest.cpp
FileTimeTypesTest_SOURCES       =  FileTimeTypesTest.cpp

