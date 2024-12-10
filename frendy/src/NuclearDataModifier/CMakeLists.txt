add_library(NuclearDataModifier
    Endf6Modifier.cpp
    Endf6ModifierByFrendyInput.cpp
    GendfModifier.cpp
    NuclearDataModifier.cpp
)

target_include_directories(NuclearDataModifier PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(NuclearDataModifier PUBLIC
    CommonUtils
    NuclearDataUtils
    EndfUtils
    FrendyUtils
)
