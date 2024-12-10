add_library(MGXSUtils
    FMGenerator/FMACECrossSectionProcessor.cpp
    FMGenerator/FMACEThermalCrossSectionProcessor.cpp
    FMGenerator/FMDataContainer.cpp
    FMGenerator/FMFreeGasSabIntegrator.cpp
    FMGenerator/FMGENDFOutput.cpp
    FMGenerator/FMGenerator.cpp
    FMGenerator/FMMatxsOutput-1.cpp
    FMGenerator/FMMatxsOutput.cpp
    FMGenerator/FMSpectrumCalculator.cpp
    FMGenerator/main.cpp
    InputUtils/MultiGroupDataGeneratorInputConverter.cpp
    KramUtils/KramCompare.cpp
    KramUtils/KramMerger.cpp
    KramUtils/KramObject.cpp
    KramUtils/KramParser.cpp
    KramUtils/KramWriter.cpp
    MGUtils/MGPhotonProduction.cpp
    MGUtils/MultiGroupDataGeneratorByFrendyInput.cpp
    MGUtils/MultiGroupDataGeneratorByNjoyInput.cpp
    MatxsUtils/MatxsCompare.cpp
    MatxsUtils/MatxsMerger.cpp
    MatxsUtils/MatxsObject.cpp
    MatxsUtils/MatxsParser.cpp
    MatxsUtils/MatxsWriter.cpp
    OtherUtils/MGUtils.cpp
)

target_include_directories(MGXSUtils PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(MGXSUtils PRIVATE
    CoreLib
    NuclearDataModifier
)
