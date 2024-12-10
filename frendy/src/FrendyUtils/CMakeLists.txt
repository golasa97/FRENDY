# CMakeLists.txt for FrendyUtils

# Create a library with all the specified source files
add_library(FrendyUtils
    Endf6FormatCheckInputReader.cpp
    DopplerBroadeningInputReader.cpp
    MakeNJOYInputReader.cpp
    ReconResonanceInputReader.cpp
    AceDataGeneratorInputReader.cpp
    GasProductionInputReader.cpp
    NuclearDataPlotterInputReader.cpp
    FrendyInputCommonUtils.cpp
    ArgumentVectorReader.cpp
    ThermalScatterInputReader.cpp
    ProbTableInputReader.cpp
    FrendyInputReader.cpp
    StringDataConverter.cpp
    Endf6ModifierInputReader.cpp
    ThermalScatterMatList.cpp
    MultiGroupDataGeneratorInputReader.cpp
)

# Include this directory for public access to headers
target_include_directories(FrendyUtils PUBLIC ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(FrendyUtils PRIVATE
    CommonUtils
    ContinuousEnergyXSUtils
    MathUtils
    NuclearDataUtils
    TabUtils
)

