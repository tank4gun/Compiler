cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)

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

FILE(GLOB SRCFILES "src/*.cpp" "src/*.h"
        "src/ST-AST/*.cpp" "src/ST-AST/*.h"
        "src/SymbolTable/*.cpp" "src/SymbolTable/*.h"
        "src/ActivationRecords/*.h" "src/ActivationRecords/*.cpp"
        "src/IRTree/*.h" "src/IRTree/*.cpp")

add_executable(runCompiler  ${SRCFILES} ${FLEX_FlexLexer_OUTPUTS} ${BISON_BisonParser_OUTPUTS} src/ActivationRecords/IAccess.h src/ActivationRecords/CInRegAccess.h src/ActivationRecords/CInFrameAccess.h src/ActivationRecords/IFrame.h src/ActivationRecords/CX86MiniJavaFrame.h)