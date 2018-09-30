cmake_minimum_required(VERSION 2.8)

find_package(FLEX)

FLEX_TARGET(MyScanner lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

add_executable(example ${FLEX_MyScanner_OUTPUTS})