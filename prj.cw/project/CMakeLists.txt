
cmake_minimum_required (VERSION 3.8)

project ("bgfx_pr")

SET(CMAKE_CXX_STANDATR 14)
SET(CMAKE_TOOLCHAIN_FILE "D:/proga_pr/vcpkg/scripts/buildsystems/vcpkg.cmake")
include(D:/proga_pr/vcpkg/scripts/buildsystems/vcpkg.cmake)

SET(CMAKE_VERBOSE_MAKEFILE TRUE)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

find_package(OpenGL REQUIRED)
 find_package(glfw3 REQUIRED)
 find_package(glew REQUIRED)
 find_package(libigl REQUIRED)
 find_package(glad REQUIRED)
 find_package(Stb REQUIRED)
 


 include_directories(
        ${OPENGL_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLAD_INCLUDE_DIR}
        ${Stb_INCLUDE_DIR}
)


add_executable (bgfx_pr "bgfx_pr.cpp" "bgfx_pr.h")
target_link_libraries(bgfx_pr         glfw 
                                      ${OPENGL_gl_LIBRARY}  
                                      ${GLEW_LIBRARIES}  
                                      ${Stb_INCLUDE_DIR}
                                      igl::igl_core 
                                      igl_copyleft::igl_copyleft_core 
                                      glad::glad 
                                    
  ) 





