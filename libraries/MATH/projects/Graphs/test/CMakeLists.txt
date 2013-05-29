cmake_minimum_required (VERSION 2.6)
project (GraphsTest)

set (GraphsTest_VERSION_MAJOR 1)
set (GraphsTest_VERSION_MINOR 0)

if (WIN32)
set (install_dir "/home/elesd/Documents/programing2/base/")
else (UNIX)
set (install_dir "/home/elesd/Documents/programing2/base/")
endif (WIN32)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)

include_directories ("${PROJECT_SOURCE_DIR}/header")
include_directories ("${install_dir}/include")

add_library(Tester STATIC IMPORTED)
add_library(Logger STATIC IMPORTED)
set_property (TARGET Tester PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libTester.a)
set_property (TARGET Logger PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libLogger.a)


configure_file (
		"${PROJECT_SOURCE_DIR}/config.h.in"
		"${PROJECT_SOURCE_DIR}/header/graphstestconfig.h")

file (GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")
file (GLOB headers "${PROJECT_SOURCE_DIR}/header/*.h")

add_executable (GraphsTest ${sources})
target_link_libraries (GraphsTest Tester Logger)

