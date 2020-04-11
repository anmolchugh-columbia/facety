cmake_minimum_required(VERSION 3.15)
project(facety)

include(FetchContent)
FetchContent_Declare(dlib
        GIT_REPOSITORY https://github.com/davisking/dlib.git
        GIT_TAG        v19.18
        )
FetchContent_MakeAvailable(dlib)

set(CMAKE_CXX_STANDARD 17)

add_executable(facety main.cpp src/FileExplorer/source/ImageIterator.cpp src/FileExplorer/header/ImageIterator.h tests/has_filesystem.cc src/Utilities/source/ImageUtilities.cpp src/Utilities/header/ImageUtilities.h)
target_link_libraries(facety stdc++fs)

target_link_libraries(facety dlib::dlib)

#make a cmake file inside another cmake file
