cmake_minimum_required(VERSION 3.17)
project(ModalMuChecker)

set(CMAKE_CXX_STANDARD 14)

add_executable(ModalMuChecker main.cpp parsing/Parser.cpp parsing/Parser.h DataRepresentations/Lts.cpp DataRepresentations/Lts.h DataRepresentations/Formula.cpp DataRepresentations/Formula.h parsing/Tokenizer.cpp parsing/Tokenizer.h)
file(COPY ${ModalMuChecker_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})