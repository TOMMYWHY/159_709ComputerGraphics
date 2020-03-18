cmake_minimum_required(VERSION 3.14)
project(demo)

set(CMAKE_CXX_STANDARD 14)

#set(GLEW_H /usr/local/Cellar/glew/2.1.0/include)
set(GLFW_H /usr/local/Cellar/glfw/3.3/include)
include_directories(${GLEW_H} ${GLFW_H} )
include_directories(include/
        external/glm)


# 添加目标链接
#set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})


file(GLOB PROJECT_HEADERS include/*.h)
# --- demo1 ---#
set(SHADERS shaders)
#file(GLOB PROJECT_SOURCES src/main.cpp)

# --- demo2 ---#
#set(SHADERS shaders)
#file(GLOB PROJECT_SOURCES src/source.cpp) # 球 未能上色
#file(GLOB PROJECT_SOURCES src/source1.cpp) # 圆柱体
#file(GLOB PROJECT_SOURCES src/source2.cpp) # cylinder to vector
#file(GLOB PROJECT_SOURCES src/source3.cpp) # merge ball and cylinder vetor
#file(GLOB PROJECT_SOURCES src/source4.cpp) #  merge ball and cylinder  display
file(GLOB PROJECT_SOURCES src/source5.cpp) # ....flag
#file(GLOB PROJECT_SOURCES src/source6.cpp) # merge ball  cylinder flag  working
#file(GLOB PROJECT_SOURCES src/source7.cpp) # view not working
#file(GLOB PROJECT_SOURCES src/source8.cpp) # to function


source_group("Sources" FILES ${PROJECT_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} )




set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Debug
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Release)




# mac下这步很重要
if (APPLE)
    target_link_libraries(${PROJECT_NAME}  "-framework OpenGL")
    target_link_libraries(${PROJECT_NAME}  "-framework GLUT")

endif()



add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/${SHADERS} $<TARGET_FILE_DIR:${PROJECT_NAME}>/${SHADERS}
        COMMENT "Creating symlink to shader directory" VERBATIM
)


# error
#[[
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders-02
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders-02)]]
