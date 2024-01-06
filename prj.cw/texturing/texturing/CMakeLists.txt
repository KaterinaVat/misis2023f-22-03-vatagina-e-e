add_library(textures texture.cpp include/texture.h)

set_property(TARGET textures PROPERTY CXX_STANDARD 14)
target_include_directories(textures PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(textures        glfw 
                                      ${OPENGL_gl_LIBRARY}  
                                      ${GLEW_LIBRARIES}  
                           
                                      igl::igl_core 
                                      igl_copyleft::igl_copyleft_core 
                                      glad::glad 
                                    
  ) 

