cmake_minimum_required(VERSION 3.10)

project(WallPaper VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(FILES ConvertUTF.h ConvertUTF.c SimpleIni.h path.h path.cc upenv.h upenv.cc wallpaper.cc)
add_executable(WallPaper ${FILES})
add_executable(MakeProcess createprocess.cc)
add_executable(ExecuteShell path.h path.cc shellexecute.cc)

target_include_directories(WallPaper PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )