cmake_minimum_required (VERSION 2.6)
project (Exceptions)

set (Exceptions_VERSION_MAJOR 1)
set (Exceptions_VERSION_MINOR 0)

if (WIN32)
set (install_dir "/home/elesd/Documents/programing2/base/")
else (UNIX)
set (install_dir "/home/elesd/Documents/programing2/base/")
endif (WIN32)

SET (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

include_directories ("${PROJECT_SOURCE_DIR}/header")

configure_file (
		"${PROJECT_SOURCE_DIR}/config.h.in"
		"${PROJECT_SOURCE_DIR}/header/exceptionsconfig.h")


file (GLOB headers "${PROJECT_SOURCE_DIR}/header/*.h")

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

install (FILES ${headers}
		 DESTINATION "${install_dir}/include/${CMAKE_PROJECT_NAME}")


