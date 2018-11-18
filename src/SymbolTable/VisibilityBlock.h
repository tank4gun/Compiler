#pragma once
#include "Symbol.h"
#include <memory>

class VisibilityBlock {
  public:
    virtual bool VarInBlock(Symbol* s) = 0;
};

