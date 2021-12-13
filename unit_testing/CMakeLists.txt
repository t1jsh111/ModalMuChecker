project(Tests)
add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../parsing/inc ../formulaAlgorithms/inc)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

#set(PROJECT_SOURCE_FILES
#        ../parsing/src/)
set(TESTING_SOURCE_FILES
        FormulaChecking.cpp
        )
file(GLOB_RECURSE PROJ_HEADER_FILES CONFIGURE_DEPENDS ../parsing/inc/*.h ../formulaAlgorithms/inc/*.h)
file(GLOB_RECURSE PROJ_SOURCE_FILES CONFIGURE_DEPENDS ../parsing/src/*.cpp ../formulaAlgorithms/src/*.cpp)



# adding the Google_Tests_run target
add_executable(Google_Tests_run ${TESTING_SOURCE_FILES} ${PROJ_SOURCE_FILES})

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(Google_Tests_run)

target_link_libraries(Google_Tests_run gtest gtest_main)
