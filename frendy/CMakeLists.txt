# CMake version
cmake_minimum_required(VERSION 3.12)

# Project name
project(frendy CXX)

# Set flags
set(CMAKE_CXX_FLAGS "-Wall -O2 -MMD -MP -std=c++11")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--as-needed")

# Set default install directory if not specified

# Find packages
include_directories(${CMAKE_SOURCE_DIR}/include)
find_package(LAPACK REQUIRED)
find_package(Threads)
find_package(Boost REQUIRED COMPONENTS system filesystem timer chrono )

add_subdirectory(src/Config)
add_subdirectory(src/CommonUtils)
add_subdirectory(src/MathUtils)
add_subdirectory(src/EndfUtils)
add_subdirectory(src/NuclearDataUtils)
add_subdirectory(src/TabUtils)
add_subdirectory(src/FrendyUtils)
add_subdirectory(src/NjoyUtils)
add_subdirectory(src/ContinuousEnergyXSUtils)

add_library(CoreLib INTERFACE)

target_link_libraries(CoreLib INTERFACE
    CommonUtils
    MathUtils
    NuclearDataUtils
    EndfUtils
    TabUtils
    FrendyUtils
    NjoyUtils
    ContinuousEnergyXSUtils
    Boost::timer
)

add_subdirectory(src/ReconResonance)
add_subdirectory(src/DopplerBroadening)
add_subdirectory(src/ThermalScatter)
add_subdirectory(src/MGXSUtils)
add_subdirectory(src/NuclearDataModifier)
add_subdirectory(src/GasProduction)
add_subdirectory(src/UnresoUtils)
add_subdirectory(src/Plotter)
add_subdirectory(src/NuclearDataProcessor)

add_subdirectory(src/main)
