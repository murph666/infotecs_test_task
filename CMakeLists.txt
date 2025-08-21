cmake_minimum_required(VERSION 3.24)
project(infotecs VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_subdirectory(libs)
add_subdirectory(src)

add_executable(infotecs main.cpp)
target_link_libraries(infotecs PRIVATE Infotecs::main_lib)