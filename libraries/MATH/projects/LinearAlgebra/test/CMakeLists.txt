cmake_minimum_required (VERSION 2.6)
project (LinearAlgebraTest)

set (LinearAlgebraTest_VERSION_MAJOR 1)
set (LinearAlgebraTest_VERSION_MINOR 0)


if (WIN32)
set (install_dir "/home/elesd/Documents/programing2/base/")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else (UNIX)
set (install_dir "/home/elesd/Documents/programing2/base/")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif (WIN32)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)

include_directories ("${PROJECT_SOURCE_DIR}/header")
include_directories ("${install_dir}/include")

add_library(Tester STATIC IMPORTED)
#add_library(MATH STATIC IMPORTED)
#add_library(LinearAlgebra STATIC IMPORTED)
#add_library(Algebra STATIC IMPORTED)
set_property (TARGET Tester PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libTester.a)
#set_property (TARGET LinearAlgebra PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libLinearAlgebra.a)
#set_property (TARGET MATH PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libMATH.a)
#set_property (TARGET Algebra PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libAlgebra.a)


configure_file (
		"${PROJECT_SOURCE_DIR}/config.h.in"
		"${PROJECT_SOURCE_DIR}/header/linearalgebratestconfig.h")

file (GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")
file (GLOB headers "${PROJECT_SOURCE_DIR}/header/*.h")

add_executable (LinearAlgebraTest ${sources})
target_link_libraries (LinearAlgebraTest Tester)

