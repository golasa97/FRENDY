add_library(UnresoUtils
    ProbabilityTableCalculator.cpp
    ProbabilityTableCalculatorByFrendyInput.cpp
    ProbabilityTableCalculatorByNjoyInput.cpp
)

target_include_directories(UnresoUtils PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(UnresoUtils PRIVATE
    CoreLib
    ReconResonance
)
