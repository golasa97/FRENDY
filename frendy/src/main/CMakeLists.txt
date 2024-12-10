add_executable(frendy
    main_frendy.cpp
)

set_target_properties(frendy PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_include_directories(frendy PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(frendy PRIVATE
    NuclearDataProcessor
)
