#pragma once
#include "Symbol.h"
#include <memory>
#include "ST-AST/LocStruct.h"

class VisibilityBlock {
  public:
    explicit VisibilityBlock(LocStruct location): location(location) {}
    virtual bool VarInBlock(Symbol* s) = 0;

    LocStruct location;
};

