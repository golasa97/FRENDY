add_library(DopplerBroadening
    BroadenedXSCalculator.cpp
    BroadenedXSCalculatorWithNjoyFormula.cpp
    DopplerCalculator.cpp
    DopplerCalculatorByFrendyInput.cpp
    DopplerCalculatorByNjoyInput.cpp
    ThermalQuantityCalculator.cpp
)

target_include_directories(DopplerBroadening PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(DopplerBroadening PRIVATE
    CoreLib
)
