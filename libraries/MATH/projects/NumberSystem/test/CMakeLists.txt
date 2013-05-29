cmake_minimum_required (VERSION 2.6)
project (NumberSystemTest)

set (NumberSystemTest_VERSION_MAJOR 1)
set (NumberSystemTest_VERSION_MINOR 0)

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
add_library(MATH STATIC IMPORTED)
add_library(Logger STATIC IMPORTED)
add_library(StringUtil STATIC IMPORTED)
set_property (TARGET Tester PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libTester.a)
set_property (TARGET MATH PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libMATH.a)
set_property (TARGET Logger PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libLogger.a)
set_property (TARGET StringUtil PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libStringUtil.a)


configure_file (
		"${PROJECT_SOURCE_DIR}/config.h.in"
		"${PROJECT_SOURCE_DIR}/header/numbersystemtestconfig.h")

file (GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")
file (GLOB headers "${PROJECT_SOURCE_DIR}/header/*.h")

add_executable (NumberSystemTest ${sources})
target_link_libraries (NumberSystemTest Tester MATH Logger)


add_custom_target(rebuild
		               make clean
									 COMMAND make)
