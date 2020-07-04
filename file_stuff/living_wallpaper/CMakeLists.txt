cmake_minimum_required(VERSION 3.10)

project(WallPaper VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CurCompileFlags "")

if(MSVC)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
set(CurCompileFlags "${CurCompileFlags} /wd4819")
endif()

add_executable(MakeProcess createprocess.cc)
add_executable(ExecuteShell path.h path.cc hideconsole.h hideconsole.cc shellexecute.cc)
add_executable(WallPaper ConvertUTF.h ConvertUTF.c SimpleIni.h path.h path.cc upenv.h upenv.cc hideconsole.h hideconsole.cc wallpaper.cc)

if (NOT ${CurCompileFlags} STREQUAL "")
set_target_properties(MakeProcess PROPERTIES COMPILE_FLAGS ${CurCompileFlags})
set_target_properties(ExecuteShell PROPERTIES COMPILE_FLAGS ${CurCompileFlags})
set_target_properties(WallPaper PROPERTIES COMPILE_FLAGS ${CurCompileFlags})
endif()

add_custom_command(TARGET WallPaper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/config/*.*"
        $<TARGET_FILE_DIR:WallPaper>)