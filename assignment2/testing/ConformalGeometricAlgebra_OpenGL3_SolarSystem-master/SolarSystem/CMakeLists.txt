cmake_minimum_required(VERSION 2.8)

PROJECT(SolarSystemApplication)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake)

#set(GLEW_H /usr/local/Cellar/glew/2.1.0/include)
set(GLFW_H /usr/local/Cellar/glfw/3.3/include)
include_directories(${GLEW_H} ${GLFW_H} )

#set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})




find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(C3GA REQUIRED)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
set(LIBS_INCLUDE_DIR libs/include)
include_directories(
	${SDL_INCLUDE_DIR} 
	${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR} 
    ${LIBS_INCLUDE_DIR} 
    ${INCLUDE_DIR}
    ${EIGEN3_INCLUDE_DIR}
    ${C3GA_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O2 -std=c++14")

set(ALL_LIBRARIES ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${C3GA_LIBRARIES})

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE SHADER_FILES ${CMAKE_SOURCE_DIR}/shaders/*.glsl)

file(GLOB SRC_DIRECTORIES "assets*")

foreach(assets ${SRC_DIRECTORIES})
    add_subdirectory(${assets})
endforeach()

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(TARGET_NAME LunchSolarSystemApplication)
ADD_EXECUTABLE(${TARGET_NAME} 
                ${SOURCE_FILES} 
                ${HEADER_FILES} 
                ${SHADER_FILES})
TARGET_LINK_LIBRARIES(${TARGET_NAME} ${ALL_LIBRARIES})
