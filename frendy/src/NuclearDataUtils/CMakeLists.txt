

# NuclearDataContainer library
add_library(NuclearDataUtils
    NuclearDataContainer/CrossSectionDataContainer.cpp
    NuclearDataContainer/GeneralDataContainer.cpp
    NuclearDataContainer/RadioactiveProductDataContainer.cpp
    NuclearDataContainer/OtherNuclearDataContainer.cpp
    NuclearDataContainer/ScatteringLawDataContainer.cpp
    NuclearDataContainer/ResonanceData/BreitWignerDataContainer.cpp
    NuclearDataContainer/ResonanceData/UnresolvedResonanceDataContainer.cpp
    NuclearDataContainer/ResonanceData/UnresolvedCrossSectionDataContainer.cpp
    NuclearDataContainer/ResonanceData/ReichMooreDataContainer.cpp
    NuclearDataContainer/ResonanceData/UnresolvedProbabilityDataContainer.cpp
    NuclearDataContainer/ResonanceData/RMatrixLimitedDataContainer.cpp
    NuclearDataContainer/ResonanceData/AdlerAdlerDataContainer.cpp
    NuclearDataContainer/PhotonDataContainer.cpp
    NuclearDataContainer/ResonanceDataContainer.cpp
    NuclearDataContainer/ThermalScatterDataContainer.cpp
    NuclearDataContainer/FissionDataContainer.cpp
    NuclearDataContainer/EnergyAngularDataContainer.cpp
    NuclearDataContainer/ProductDistributionDataContainer.cpp
    NuclearDataContainer/NuclearReactionDataContainer.cpp

    ProbabilityDataContainer/ProbabilityTableDataContainer.cpp
    ProbabilityDataContainer/ProbabilityDataContainer.cpp

    NuclearDataCalculator/NuBarCalculator.cpp

    CovarianceDataContainer/CovarianceCrossSectionDataContainer.cpp
    CovarianceDataContainer/CovarianceResonanceData/ReichMooreCovarianceDataContainer.cpp
    CovarianceDataContainer/CovarianceResonanceData/UnresolvedResonanceCovarianceDataContainer.cpp
    CovarianceDataContainer/CovarianceResonanceData/RMatrixLimitedCompactCovarianceDataContainer.cpp
    CovarianceDataContainer/CovarianceResonanceData/BreitWignerCovarianceDataContainer.cpp
    CovarianceDataContainer/CovarianceResonanceData/CompatibleResolvedResonanceDataContainer.cpp
    CovarianceDataContainer/CovarianceResonanceData/BreitWignerCompactCovarianceDataContainer.cpp
    CovarianceDataContainer/CovarianceResonanceData/RMatrixLimitedCovarianceDataContainer.cpp
    CovarianceDataContainer/CovarianceResonanceData/AdlerAdlerCovarianceDataContainer.cpp
    CovarianceDataContainer/CovarianceResonanceData/ReichMooreCompactCovarianceDataContainer.cpp
    CovarianceDataContainer/CovarianceEnergyAngularDataContainer.cpp
    CovarianceDataContainer/CovarianceGeneralDataContainer.cpp
    CovarianceDataContainer/CovarianceFissionDataContainer.cpp
    CovarianceDataContainer/CovarianceResonanceDataContainer.cpp
    CovarianceDataContainer/CovarianceRadioactiveProductDataContainer.cpp
    CovarianceDataContainer/CovarianceReactionDataContainer.cpp

    NuclearDataObject.cpp
    OtherUtils/NuclearDataObjectUtils.cpp
    OtherUtils/CrossSectionCalculator.cpp
    OtherUtils/ProbDataConverter.cpp
    OtherUtils/Endf6FileStore.cpp
)

target_include_directories(NuclearDataUtils PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(NuclearDataUtils PRIVATE
    CommonUtils
    MathUtils
    TabUtils
    EndfUtils
)
