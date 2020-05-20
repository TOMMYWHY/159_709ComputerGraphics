# Install script for directory: /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/external/assimp/code/libassimpd.4.1.0.dylib"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/external/assimp/code/libassimpd.4.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.4.1.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.4.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "/usr/local/lib/libassimpd.4.dylib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/external/assimp/code/libassimpd.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "/usr/local/lib/libassimpd.4.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/anim.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/ai_assert.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/camera.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/color4.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/color4.inl"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/external/assimp/code/../include/assimp/config.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/defs.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Defines.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/cfileio.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/light.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/material.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/material.inl"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/matrix3x3.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/matrix3x3.inl"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/matrix4x4.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/matrix4x4.inl"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/mesh.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/pbrmaterial.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/postprocess.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/quaternion.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/quaternion.inl"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/scene.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/metadata.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/texture.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/types.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/vector2.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/vector2.inl"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/vector3.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/vector3.inl"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/version.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/cimport.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/importerdesc.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Importer.hpp"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/IOStream.hpp"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/IOSystem.hpp"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Logger.hpp"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/LogStream.hpp"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/NullLogger.hpp"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/cexport.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Exporter.hpp"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/DefaultIOStream.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/DefaultIOSystem.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/SceneCombiner.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/fast_atof.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/qnan.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/BaseImporter.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Hash.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/ParsingUtils.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/StreamReader.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/StreamWriter.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/StringComparison.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/StringUtils.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/SGSpatialSort.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/GenericProperty.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/SpatialSort.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/SmoothingGroups.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/SmoothingGroups.inl"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/StandardShapes.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/RemoveComments.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Subdivision.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Vertex.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/LineSplitter.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/TinyFormatter.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Profiler.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/LogAux.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Bitmap.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/XMLTools.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/IOStreamBuffer.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/CreateAnimMesh.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/irrXMLWrapper.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/BlobIOSystem.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/MathFunctions.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Macros.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Exceptional.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/external/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

