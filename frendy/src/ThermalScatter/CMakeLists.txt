add_library(ThermalScatter
    CoherentElasticScatterCalculator.cpp
    IncoherentElasticScatterCalculator.cpp
    IncoherentInelasticScatterCalculatorByInterpolation.cpp
    IncoherentInelasticScatterCalculator.cpp
    ThermalScatterCalculatorByFrendyInput.cpp
    ThermalScatterCalculatorByNjoyInput.cpp
    ThermalScatterCalculator.cpp
    ThermalScatterDataConverter.cpp
)

target_include_directories(ThermalScatter PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(ThermalScatter PRIVATE
    CoreLib
)
