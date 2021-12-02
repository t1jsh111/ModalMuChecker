set(SOURCE_FILES
        src/Lts.cpp
        src/Parser.cpp
        src/Tokenizer.cpp)

set(HEADER_FILES
        inc/Formula.h
        inc/Lts.h
        inc/Parser.h
        inc/Tokenizer.h)

add_library(ParsingLibrary ${SOURCE_FILES})
target_include_directories(ParsingLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)