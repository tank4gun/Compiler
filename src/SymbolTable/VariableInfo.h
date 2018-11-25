#pragma once
#include "ST-AST/Types.h"
#include "Symbol.h"
#include "VisibilityBlock.h"
#include <memory>

class VariableInfo: public VisibilityBlock {
  public:
    VariableInfo(LocStruct location): VisibilityBlock(location) {}
    bool VarInBlock(Symbol* s) override {}
    //IType* type;
//    VariableInfo() = default;
//    VariableInfo(std::string* type, Symbol* symbol): type(type), symbol(symbol) {}
    std::string type;
    Symbol* symbol;

};
