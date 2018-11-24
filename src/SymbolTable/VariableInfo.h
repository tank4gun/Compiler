#pragma once
#include "ST-AST/Types.h"
#include "Symbol.h"
#include "VisibilityBlock.h"
#include <memory>

class VariableInfo: public VisibilityBlock {
  public:
    VariableInfo(LocStruct location): VisibilityBlock(location) {}
    bool VarInBlock(Symbol* s) override {}
    IType* type;
    Symbol* symbol;

};
