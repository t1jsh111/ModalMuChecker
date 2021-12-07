set(SOURCE_FILES
        src/NestingDepthCalculator.cpp
        src/AlternatingNestingDepthCalculator.cpp
        src/DependentAlternationDepthCalculator.cpp
        )

set(HEADER_FILES
        inc/NestingDepthCalculator.h
        inc/AlternatingNestingDepthCalculator.h
        inc/DependentAlternationDepthCalculator.h
        )

add_library(FormulaAlgorithmsLibrary ${SOURCE_FILES})
target_include_directories(FormulaAlgorithmsLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(FormulaAlgorithmsLibrary PUBLIC ${CMAKE_SOURCE_DIR}/parsing/inc)
