IF(NOT EXISTS "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/external/assimp/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/external/assimp/install_manifest.txt\"")
ENDIF(NOT EXISTS "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/external/assimp/install_manifest.txt")

FILE(READ "/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/external/assimp/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
FOREACH(file ${files})
  MESSAGE(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  EXEC_PROGRAM(
    "/Users/Tommy/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/CLion.app/Contents/bin/cmake/mac/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
    OUTPUT_VARIABLE rm_out
    RETURN_VALUE rm_retval
    )
  IF(NOT "${rm_retval}" STREQUAL 0)
    MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
  ENDIF(NOT "${rm_retval}" STREQUAL 0)
ENDFOREACH(file)
