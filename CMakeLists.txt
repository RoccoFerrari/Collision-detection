cmake_minimum_required(VERSION 3.10) # Minimun CMake's version

project(Collision_detection) # Project's name

set(CMAKE_CXX_STANDARD 17) # C++ Standard (es. C++17)

# Find's all sorgent files in src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Test01 ${SOURCES}) # Create file.exe

# Adds include/ for header files
include_directories(include)