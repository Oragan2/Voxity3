cmake_minimum_required(VERSION 3.23)
project(Voxitry3 LANGUAGES CXX)

# Force C++20 for modern STL features like threading and concepts
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build Type" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG" CACHE STRING "" FORCE)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Reusable compilation options
add_library(VoxitryOptions INTERFACE)
target_compile_options(VoxitryOptions INTERFACE
    -Wall -Wextra -Wpedantic
)

# Core Physics Library
add_library(VoxitryCore
    src/physics/particule.cpp
)

# Core Rendering Library
add_library(GladObject OBJECT src/glad.cpp)
target_include_directories(GladObject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_library(VoxitryRender
   src/graphics/render.cpp
   $<TARGET_OBJECTS:GladObject>
)

target_include_directories(VoxitryCore
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_include_directories(VoxitryRender
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Main executable
add_executable(Voxitry src/main.cpp)

target_include_directories(Voxitry 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(VoxitryCore PRIVATE VoxitryOptions)
target_link_libraries(Voxitry PRIVATE VoxitryOptions)
target_link_libraries(VoxitryRender PRIVATE 
	VoxitryOptions
	glfw
	OpenGL::GL
	${CMAKE_DL_LIBS}	
)

target_link_libraries(Voxitry PRIVATE 
	VoxitryCore 
	VoxitryRender
)
