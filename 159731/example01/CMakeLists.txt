cmake_minimum_required(VERSION 3.14)
project(opengl_start_03)

set(CMAKE_CXX_STANDARD 14)

set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3/include/)
include_directories(${GLEW_H} ${GLFW_H} )


# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

set(SOURCE_FILES "example01.cpp")
add_executable(OpenGL ${SOURCE_FILES})


# mac下这步很重要
if (APPLE)
    target_link_libraries(OpenGL "-framework OpenGL")
    target_link_libraries(OpenGL "-framework GLUT")

endif()

