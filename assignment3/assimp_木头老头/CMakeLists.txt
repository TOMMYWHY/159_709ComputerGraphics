cmake_minimum_required(VERSION 3.14)
project(opengl_demo)

set(CMAKE_CXX_STANDARD 14)

#set(GLEW_H /usr/local/Cellar/glew/2.1.0/include)
set(GLFW_H /usr/local/Cellar/glfw/3.3/include)
set(GLM_H /usr/local/Cellar/glm/0.9.9.5/include)
#set(ASSIMP_H /usr/local/Cellar/assimp/5.0.1/include)
include_directories(${GLEW_H} ${GLFW_H} ${GLM_H} ${ASSIMP_H})

# 添加目标链接
#set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib)
#set(ASSIMP_LINK /usr/local/Cellar/assimp/5.0.1/lib)

link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${ASSIMP_LINK})

#assimp
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(external/assimp)



include_directories(include/ external/assimp/include/)


# --- exmaple5 ---#
set(SHADERS shader)
#set(IMAGES image)
file(GLOB PROJECT_SOURCES src/*.cpp)
file(GLOB PROJECT_HEADERS include/*.h)


source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_SHADERS}${EXTERNAL_SOURCES}
        src/Shade.cpp include/Shade.h src/Camera.cpp include/Camera.h src/LightDirectional.cpp include/LightDirectional.h src/LightPoint.cpp include/LightPoint.h src/LightSpot.cpp include/LightSpot.h src/Mesh.cpp include/Mesh.h src/Model.cpp include/Model.h)



set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Debug
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Release)


target_link_libraries(${PROJECT_NAME} assimp
        ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})



# mac下这步很重要
if (APPLE)
    target_link_libraries(${PROJECT_NAME}  "-framework OpenGL")
    target_link_libraries(${PROJECT_NAME}  "-framework GLUT")
    target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES})


endif()


# 读取files

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/${SHADERS} $<TARGET_FILE_DIR:${PROJECT_NAME}>/${SHADERS}
        COMMENT "Creating symlink to shader directory" VERBATIM
)


add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/images
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/images)

# todo 读取 obj