set(CMAKE_CXX_STANDARD 17)
set(BOOST_ROOT "/Users/bhavyagupta/boost_1_71_0")
set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})
include_directories (src)
include_directories (resources)

# 'Boost_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
include(FetchContent)
FetchContent_Declare(dlib
        GIT_REPOSITORY https://github.com/davisking/dlib.git
        GIT_TAG        v19.18
        )
FetchContent_MakeAvailable(dlib)
enable_testing()
add_executable (Boost_Tests_run testing.cpp)

target_link_libraries (Boost_Tests_run ${Boost_LIBRARIES})
target_link_libraries(Boost_Tests_run dlib::dlib)
target_link_libraries(Boost_Tests_run stdc++fs)
target_link_libraries(Boost_Tests_run Qt5::Widgets)
