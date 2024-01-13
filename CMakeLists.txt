cmake_minimum_required(VERSION 3.18)   

project(misis2023f-22-03-vatagina-e-e)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

add_subdirectory(prj.cw)
option(BUILD_WITH_CODEFORCES "Build prj.codeforces targets" off)

if (BUILD_WITH_CODEFORCES)
  add_subdirectory(prj.codeforces)
endif()



