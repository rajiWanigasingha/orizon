cmake_minimum_required(VERSION 4.1)
project(applicationWatch)

set(CMAKE_CXX_STANDARD 20)

add_executable(applicationWatch
        main.cpp
        pacman/Pacman.cpp
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(MyTests
        test/pacmanTest.cpp
        pacman/Pacman.cpp
)

target_include_directories(MyTests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/pacman
)

target_link_libraries(MyTests
        PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MyTests)
