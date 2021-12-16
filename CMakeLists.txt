cmake_minimum_required(VERSION 3.17)
project(ModalMuChecker)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(parsing)
add_subdirectory(formulaAlgorithms)

add_executable(ModalMuChecker main.cpp DataPrinter.cpp NaturalSort.h)

target_link_libraries(ModalMuChecker PUBLIC ParsingLibrary)
target_include_directories(ModalMuChecker PUBLIC parsing/inc)

target_link_libraries(ModalMuChecker PUBLIC FormulaAlgorithmsLibrary)
target_include_directories(ModalMuChecker PUBLIC formulaAlgorithms/inc)

file(COPY ${ModalMuChecker_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(unit_testing)