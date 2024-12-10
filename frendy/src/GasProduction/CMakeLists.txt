add_library(GasProduction
    GasProductionXSCalculator.cpp
    GasProductionXSCalculatorByFrendyInput.cpp
    GasProductionXSCalculatorByNjoyInput.cpp
)

target_include_directories(GasProduction PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(GasProduction PRIVATE
    CoreLib
)
