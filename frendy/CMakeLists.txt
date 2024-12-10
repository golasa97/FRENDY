# CMake version
cmake_minimum_required(VERSION 3.12)

# Project name
project(frendy CXX)

# Set flags
set(CMAKE_CXX_FLAGS "-Wall -O2 -MMD -MP")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set default install directory if not specified

# Find packages
include_directories(${CMAKE_SOURCE_DIR}/include)
find_package(LAPACK REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem timer chrono)

add_subdirectory(src/Config)
add_subdirectory(src/CommonUtils)
add_subdirectory(src/MathUtils)
add_subdirectory(src/TabUtils)
add_subdirectory(src/NuclearDataUtils)
add_subdirectory(src/NjoyUtils)
add_subdirectory(src/ReconResonance)
