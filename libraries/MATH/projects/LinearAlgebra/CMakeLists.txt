cmake_minimum_required (VERSION 2.6)
project (LinearAlgebra)

set (${CMAKE_PROJECT_NAME}_VERSION_MAJOR 1)
set (${CMAKE_PROJECT_NAME}_VERSION_MINOR 1)

if (WIN32)
set (install_dir "/home/elesd/Documents/programing2/base/")
else (UNIX)
set (install_dir "/home/elesd/Documents/programing2/base/")
endif (WIN32)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

SET (MAIN_PROJ_PATH "MATH/") #importent / if it's not empty!

include_directories ("${PROJECT_SOURCE_DIR}/header")
include_directories ("${install_dir}/include")

configure_file (
		"${PROJECT_SOURCE_DIR}/config.h.in"
		"${PROJECT_SOURCE_DIR}/header/linearalgebraconfig.h")

file (GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")

#add_library (LinearAlgebra ${sources})

file (GLOB headers "${PROJECT_SOURCE_DIR}/header/*.h")
file (GLOB headers_2 "${PROJECT_SOURCE_DIR}/header/*.hpp")

#DOXYGEN extension
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${PROJECT_SOURCE_DIR}/docs/Doxyfile.cmake ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)




install (FILES ${headers} ${headers_2}
		 DESTINATION "${install_dir}/include/${MAIN_PROJ_PATH}${CMAKE_PROJECT_NAME}")

#install (TARGETS LinearAlgebra
#		 DESTINATION "${install_dir}/lib")


