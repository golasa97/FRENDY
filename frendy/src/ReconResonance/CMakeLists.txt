# CMakeLists.txt for ReconResonance

# Create a library with all the specified source files
add_library(ReconResonance
    ResonanceNuclearDataModifier.cpp
    ResonanceXSReconstructorByFrendyInput.cpp
    ResonanceXSReconstructor.cpp
    RmatrixLimited/run/RmatrixLimitedCalculator.cpp
    RmatrixLimited/basics/AlphaNumeric.cpp
    RmatrixLimited/basics/MultiThread.cpp
    RmatrixLimited/numeric/Interp.cpp
    RmatrixLimited/numeric/Function1.cpp
    RmatrixLimited/numeric/Function2.cpp
    RmatrixLimited/numeric/Constant.cpp
    RmatrixLimited/numeric/Doppler.cpp
    RmatrixLimited/numeric/Datum.cpp
    RmatrixLimited/numeric/Coupling.cpp
    RmatrixLimited/numeric/Legendre.cpp
    RmatrixLimited/numeric/Tabular.cpp
    RmatrixLimited/numeric/Approx.cpp
    RmatrixLimited/numeric/Parameter.cpp
    RmatrixLimited/endf/CONT.cpp
    RmatrixLimited/endf/Interp1.cpp
    RmatrixLimited/endf/Interp2.cpp
    RmatrixLimited/endf/TEXT.cpp
    RmatrixLimited/endf/Numeric.cpp
    RmatrixLimited/endf/Functions.cpp
    RmatrixLimited/endf/TAB1.cpp
    RmatrixLimited/endf/TAB2.cpp
    RmatrixLimited/endf/LTT1.cpp
    RmatrixLimited/endf/Document.cpp
    RmatrixLimited/endf/LTT2.cpp
    RmatrixLimited/endf/LIST.cpp
    RmatrixLimited/rml/Nucleus.cpp
    RmatrixLimited/rml/System.cpp
    RmatrixLimited/rml/TwoBody.cpp
    RmatrixLimited/rml/Structure.cpp
    RmatrixLimited/rml/Distant.cpp
    RmatrixLimited/rml/Channel.cpp
    RmatrixLimited/rml/Particle.cpp
    RmatrixLimited/rml/Coulomb.cpp
    RmatrixLimited/rml/Group.cpp
    RmatrixLimited/rml/Boundary.cpp
    ResonanceEnergyGridLinearizer.cpp
    ResonanceXSCalculatorByInterpolation.cpp
    NonResonanceEnergyGridLinearizer.cpp
    ReconstructXSMerger.cpp
    ResonanceXSReconstructorByNjoyInput.cpp
    ResonanceXSCalculator.cpp
)


# Include this directory for public access to headers
target_include_directories(ReconResonance PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(ReconResonance PRIVATE
    CoreLib
    LAPACK::LAPACK
)
