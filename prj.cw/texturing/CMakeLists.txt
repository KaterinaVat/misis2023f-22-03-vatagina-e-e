
cmake_minimum_required (VERSION 3.8)

project ("texturing")

SET(CMAKE_CXX_STANDATR 14)

SET(CMAKE_VERBOSE_MAKEFILE TRUE)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file" -G Ninja)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

find_package(OpenGL REQUIRED)
 find_package(glfw3 REQUIRED)
 find_package(glew REQUIRED)
 find_package(libigl REQUIRED)
 find_package(glad REQUIRED)
 find_package(stb REQUIRED)
 
 OPTION(TEXTURE_BUILD_WITH_DOCS "Include documentation in the build process" OFF)

 #################################
# Generate Docs
#################################


option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)
if (DOXYGEN_FOUND)
   set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../texturing/docs/Doxyfile)
   set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

   configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
   message("Doxygen build started")

   add_custom_target(doc_doxygen ALL
       COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
       WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
       COMMENT "Generating API documentation with Doxygen"
       VERBATIM )
else (DOXYGEN_FOUND)
 message("Doxygen needs to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


  add_subdirectory(texturing)
  add_subdirectory(examples)

