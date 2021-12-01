cmake_minimum_required(VERSION 3.17)
project(ModalMuChecker)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(parsing)

add_executable(ModalMuChecker main.cpp)

target_link_libraries(ModalMuChecker PUBLIC ParsingLibrary)
target_include_directories(ModalMuChecker PUBLIC parsing/inc)

file(COPY ${ModalMuChecker_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})