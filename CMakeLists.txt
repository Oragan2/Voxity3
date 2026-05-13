cmake_minimum_required(VERSION 3.23)
project(Voxitry3 LANGUAGES CXX)

# Force C++20 for modern STL features like threading and concepts
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build Type" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG" CACHE STRING "" FORCE)


# Reusable compilation options
add_library(VoxitryOptions INTERFACE)
target_compile_options(VoxitryOptions INTERFACE
    -Wall -Wextra -Wpedantic
)

# 1. Core Physics Library
add_library(VoxitryCore
    src/physics/particule.cpp
)

target_include_directories(VoxitryCore
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 2. Main executable
add_executable(Voxitry src/main.cpp)

target_link_libraries(VoxitryCore PRIVATE VoxitryOptions)
target_link_libraries(Voxitry PRIVATE VoxitryOptions)
target_link_libraries(Voxitry PRIVATE VoxitryCore)
