cmake_minimum_required(VERSION 3.14)
project(opengl_start_03)

set(CMAKE_CXX_STANDARD 14)

#set(GLEW_H /usr/local/Cellar/glew/2.1.0/include)
set(GLFW_H /usr/local/Cellar/glfw/3.3/include)
include_directories(${GLEW_H} ${GLFW_H} )

# 添加目标链接
#set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})



file(GLOB PROJECT_SOURCES example02.cpp)
file(GLOB PROJECT_SOURCES example03.cpp)
file(GLOB PROJECT_SHADERS shader/*.glsl)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("shaders-02" FILES ${PROJECT_SHADERS})

add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_SHADERS} )

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Debug
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Release)


#set(SOURCE_FILES  ${PROJECT_SHADERS} "example02.cpp")
set(SOURCE_FILES  ${PROJECT_SHADERS} "example03.cpp")
#set(SOURCE_FILES "demo.cpp")
add_executable(OpenGL ${SOURCE_FILES})


# mac下这步很重要
if (APPLE)
    target_link_libraries(OpenGL "-framework OpenGL")
    target_link_libraries(OpenGL "-framework GLUT")

endif()