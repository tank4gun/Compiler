cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

project(minijava)

find_package(FLEX)

FLEX_TARGET(FlexLexer src/lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

find_package(GTest REQUIRED)
include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${GTEST_INCLUDE_DIRS}
)

add_executable(runTests src/tests/tests.cpp ${FLEX_FlexLexer_OUTPUTS})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

add_executable(runCompiler src/main.cpp ${FLEX_FlexLexer_OUTPUTS})