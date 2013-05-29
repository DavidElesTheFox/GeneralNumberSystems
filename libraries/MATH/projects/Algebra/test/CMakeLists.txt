cmake_minimum_required (VERSION 2.6)
project (AlgebraTest)

INCLUDE( ${CMAKE_ROOT}/Modules/TargetDistclean.cmake OPTIONAL)

set (AlgebraTest_VERSION_MAJOR 1)
set (AlgebraTest_VERSION_MINOR 0)

if (WIN32)
set (install_dir "/home/elesd/Documents/programing2/base/")
else (UNIX)
set (install_dir "/home/elesd/Documents/programing2/base/")
endif (WIN32)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)

include_directories ("${PROJECT_SOURCE_DIR}/header")
include_directories ("${install_dir}/include")
add_definitions(-ansi -Wall)
add_library(Tester STATIC IMPORTED)
set_property (TARGET Tester PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libTester.a)


#add_library(Algebra STATIC IMPORTED)
#set_property (TARGET Algebra PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libAlgebra.a)

configure_file (
		"${PROJECT_SOURCE_DIR}/config.h.in"
		"${PROJECT_SOURCE_DIR}/header/algebratestconfig.h")

file (GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")
file (GLOB headers "${PROJECT_SOURCE_DIR}/header/*.h")

add_executable (AlgebraTest ${sources})
target_link_libraries (AlgebraTest Tester )

