add_library(ContinuousEnergyXSUtils
AceDataCompare/AceDataCompare.cpp
AceDataCompare/DosimetryAceDataCompare.cpp
AceDataCompare/FastAceDataCompare.cpp
AceDataCompare/ThermalScatterAceDataCompare.cpp
AceDataGenerator/AceDataGenerator.cpp
AceDataGenerator/AceDataGeneratorByFrendyInput.cpp
AceDataGenerator/AceDataGeneratorByNjoyInput.cpp
AceDataGenerator/DosimetryAceDataGenerator.cpp
AceDataGenerator/FastAceDataGenerator.cpp
AceDataGenerator/ThermalScatterAceDataGenerator.cpp
AceDataObject/AceDataObject.cpp
AceDataObject/DosimetryAceDataObject.cpp
AceDataObject/FastAceDataObject.cpp
AceDataObject/ThermalScatterAceDataObject.cpp
AceDataParser/DosimetryAceDataParser.cpp
AceDataParser/FastAceDataParser.cpp
AceDataParser/ThermalScatterAceDataParser.cpp
AceDataWriter/DosimetryAceDataWriter.cpp
AceDataWriter/FastAceDataWriter.cpp
AceDataWriter/ThermalScatterAceDataWriter.cpp
OtherUtils/AceDataCollector.cpp
OtherUtils/AceFileReader.cpp
OtherUtils/AceFileWriter.cpp
PerturbUtils/PerturbNuclearData.cpp
)

target_include_directories(ContinuousEnergyXSUtils PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(ContinuousEnergyXSUtils PUBLIC
    Config
    CommonUtils
    TabUtils
    Boost::timer
    FrendyUtils
    NjoyUtils
    EndfUtils
    NuclearDataUtils
)
