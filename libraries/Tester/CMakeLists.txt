cmake_minimum_required (VERSION 2.6)
project (Tester)

set (Tester_VERSION_MAJOR 1)
set (Tester_VERSION_MINOR 1)

if (WIN32)
set (install_dir "/home/elesd/Documents/programing2/base/")
else (UNIX)
set (install_dir "/home/elesd/Documents/programing2/base/")
endif (WIN32)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

include_directories ("${PROJECT_SOURCE_DIR}/header")

configure_file (
		"${PROJECT_SOURCE_DIR}/config.h.in"
		"${PROJECT_SOURCE_DIR}/header/testerconfig.h")


add_library (Tester source/testcase.cpp)

file (GLOB headers "${PROJECT_SOURCE_DIR}/header/*.h")

install (FILES ${headers}
		 DESTINATION "${install_dir}/include/Tester")

install (TARGETS Tester
		 DESTINATION "${install_dir}/lib")


