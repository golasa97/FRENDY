# CMakeLists.txt for MathUtils

# Create a library with all the specified source files
add_library(MathUtils OBJECT
    Bootstrap.cpp
    ComplexErrorFunctionCalculatorWithNjoyPurrFormula.cpp
    RandomNumberGenerator.cpp
    RandomNumberGeneratorWithNjoyFormula.cpp
    MathUtils.cpp
    ComplexErrorFunctionCalculatorWithPadeApproximation.cpp
    ErrorFunctionCalculatorWithPolynomialExpansion.cpp
    ComplexErrorFunctionCalculatorWithNjoyReconrFormula.cpp
    ComplexErrorFunctionCalculator.cpp
)

# Include this directory for public access to headers
target_include_directories(MathUtils PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(MathUtils PRIVATE CommonUtils)
