#pragma once
#include "ST-AST/Types.h"
#include "Symbol.h"
#include <memory>

class VariableInfo {
  public:
    VariableInfo() = default;
    VariableInfo(IType* type, Symbol* symbol): type(type), symbol(symbol) {}
    IType* type;
    Symbol* symbol;

};
