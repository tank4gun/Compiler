cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

project(minijava)

find_package(FLEX)
find_package(BISON)

FLEX_TARGET(FlexLexer src/lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
BISON_TARGET(BisonParser src/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
ADD_FLEX_BISON_DEPENDENCY(FlexLexer BisonParser)

find_package(GTest REQUIRED)
include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${GTEST_INCLUDE_DIRS}
)

add_executable(runTests src/tests/tests.cpp ${FLEX_FlexLexer_OUTPUTS} ${BISON_BisonParser_OUTPUTS})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

add_executable(runCompiler src/main.cpp ${FLEX_FlexLexer_OUTPUTS} ${BISON_BisonParser_OUTPUTS} src/Expressions.h src/Expressions.cpp src/IVisitor.h src/Interpreter.cpp src/Identifiers.h src/Identifiers.cpp src/Statements.cpp src/Statements.h src/Types.cpp src/Types.h src/ASTClassDeclaration.h src/ASTClassDeclaration.cpp)