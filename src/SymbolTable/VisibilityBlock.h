#pragma once
#include "Symbol.h"
#include <memory>

class VisibilityBlock {
  public:
    virtual bool VarInBlock(std::unique_ptr<Symbol>& s) = 0;
};

