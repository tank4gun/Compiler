#pragma once
#include "ST-AST/Types.h"
#include "Symbol.h"
#include <memory>

class VariableInfo {
  VariableInfo() = default;
  VariableInfo(IType* type, Symbol* symbol): type(type), symbol(symbol) {}
  std::unique_ptr<IType> type;
  std::unique_ptr<Symbol> symbol;

};
