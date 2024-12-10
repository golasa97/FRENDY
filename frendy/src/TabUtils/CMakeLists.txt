# CMakeLists.txt for TabUtils

# Create a library with all the specified source files
add_library(TabUtils OBJECT
    IntegrateTabData.cpp
    LinearizeTabData.cpp
    TwoDInterpolator.cpp
)

# Include this directory for public access to headers
target_include_directories(TabUtils PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(TabUtils PRIVATE
    CommonUtils
    MathUtils
)
