# CMakeLists.txt for NjoyUtils

# Create a library with all the specified source files
add_library(NjoyUtils
    MultiGroupWeightFunction.cpp
    GroupStructureGamma.cpp
    UnresrInputReader.cpp
    ReconrInputReader.cpp
    GasprInputReader.cpp
    BroadrInputReader.cpp
    GroupStructureNeutron.cpp
    MatxsrInputReader.cpp
    AcerInputReader.cpp
    NjoyInputReader.cpp
    ModerInputReader.cpp
    GrouprInputReader.cpp
    PurrInputReader.cpp
    ThermrInputReader.cpp
)

# Include this directory for public access to headers
target_include_directories(NjoyUtils PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(NjoyUtils    PUBLIC
    CommmonUtils
    Config
    EndfUtils
    FrendyUtils
    MathUtils
    TabUtils
)
