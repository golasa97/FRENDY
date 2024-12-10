add_library(Plotter
    PlotAceData.cpp
    PlotDataByFrendyInput.cpp
    PlotEndfData.cpp
    PlotGendfData.cpp
)

target_include_directories(Plotter PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Plotter PUBLIC
    CommonUtils
    NuclearDataUtils
    ContinuousEnergyXSUtils
    TabUtils
    DopplerBroadening
    EndfUtils
    ReconResonance
    FrendyUtils
)
