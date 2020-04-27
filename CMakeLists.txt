cmake_minimum_required(VERSION 3.15)
project(facety)

include(FetchContent)
FetchContent_Declare(dlib
        GIT_REPOSITORY https://github.com/davisking/dlib.git
        GIT_TAG        v19.18
        )
FetchContent_MakeAvailable(dlib)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/Users/bhavyagupta/Qt/5.14.2/clang_64/")
find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(facety
        main.cpp
        src/FileExplorer/source/ImageIterator.cpp
        src/FileExplorer/header/ImageIterator.h
        tests/has_filesystem.cc
        src/Utilities/source/ImageUtilities.cpp
        src/Utilities/header/ImageUtilities.h
        src/FileExplorer/source/ImageOrganizer.cpp
        src/FileExplorer/header/ImageOrganizer.h
        src/FileExplorer/header/directoryIterator.h
        src/FileExplorer/source/directoryIterator.cpp
        src/FileExplorer/header/makeClusterDirectories.h
        src/FileExplorer/source/makeClusterDirectories.cpp
        src/QT/mainwindow.cpp
        src/QT/mainwindow.h
        src/QT/mainwindow.ui
        src/FaceRec/header/Clustering.h
        src/FaceRec/source/Clustering.cpp)

target_link_libraries(facety stdc++fs)

target_link_libraries(facety dlib::dlib)
target_link_libraries(facety Qt5::Widgets)
#add_subdirectory(tests)

#make a cmake file inside another cmake file
