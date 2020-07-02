cmake_minimum_required(VERSION 3.10)

project(WallPaper VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(FILES ConvertUTF.h ConvertUTF.c SimpleIni.h wallpaper.cc)
add_executable(WallPaper ${FILES})

target_include_directories(WallPaper PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )