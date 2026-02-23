cmake_minimum_required(VERSION 4.1)
project(applicationWatch)

set(CMAKE_CXX_STANDARD 20)

# --- Step 1: Create a library for your code ---
add_library(PacmanLib
        pacman/Pacman.cpp
        pacman/Pacman.h
        cacheApplication/buildCacheFolder.cpp
        cacheApplication/buildCacheFolder.h
        flatpak/Flatpak.cpp
        flatpak/Flatpak.h
)

target_include_directories(PacmanLib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pacman
)

# --- Step 2: Main executable ---
add_executable(applicationWatch
        main.cpp
)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(PacmanLib
        PUBLIC nlohmann_json::nlohmann_json
)

target_link_libraries(applicationWatch
        PRIVATE PacmanLib
)

# --- Step 3: Fetch GoogleTest ---
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# --- Step 4: Test executable ---
add_executable(MyTests
        test/pacmanTest.cpp
)

target_link_libraries(MyTests
        PRIVATE
        PacmanLib       # Link your code
        GTest::gtest_main
)

# --- Step 5: Discover tests ---
include(GoogleTest)
gtest_discover_tests(MyTests)
