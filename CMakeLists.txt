cmake_minimum_required(VERSION 3.23)
project(Voxitry3 LANGUAGES CXX)

# Force C++20 for modern STL features like threading and concepts
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Core Physics Library
add_library(VoxitryCore)

target_sources(VoxitryCore
    PRIVATE
        src/particule.cpp
    PUBLIC 
        FILE_SET voxitryHeader
        TYPE HEADERS
        BASE_DIRS src
        FILES src/particule.hpp
)

# Add warnings to catch physics bugs early (e.g., uninitialized floats)
target_compile_options(VoxitryCore PRIVATE -Wall -Wextra -Wpedantic)

# 2. Main Executable
add_executable(Voxitry src/main.cpp)

# 3. Linking
target_link_libraries(Voxitry PRIVATE VoxitryCore)
