//
// Created by daniil on 18.11.18.
//
#pragma once
#include "Symbol.h"

class VisibilityBlock {
  public:
    virtual bool VarInBlock(Symbol* s) = 0;
};

