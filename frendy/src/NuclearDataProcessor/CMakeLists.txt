add_library(NuclearDataProcessor
    MakeInputFromFRENDYtoNJOY.cpp
    NuclearDataProcessorByFrendyInput.cpp
    NuclearDataProcessorByNjoyInput.cpp
    NuclearDataProcessorCommonUtils.cpp
)

target_include_directories(NuclearDataProcessor PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(NuclearDataProcessor PRIVATE
    CoreLib
    ReconResonance
    DopplerBroadening
    ThermalScatter
    UnresoUtils
    GasProduction
    NuclearDataModifier
    Plotter
    MGXSUtils
)
