cmake_minimum_required(VERSION 3.15)
project(facety)

set(CMAKE_CXX_STANDARD 17)

add_executable(facety main.cpp src/FileExplorer/source/ImageIterator.cpp src/FileExplorer/header/ImageIterator.h tests/has_filesystem.cc src/Utilities/source/ImageUtilities.cpp src/Utilities/header/ImageUtilities.h)
target_link_libraries(facety stdc++fs)