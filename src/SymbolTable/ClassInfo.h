//
// Created by daniil on 18.11.18.
//
#pragma once
#include <vector>
#include "VisibilityBlock.h"
#include "MethodInfo.h"
#include "VariableInfo.h"

class ClassInfo : VisibilityBlock {
  private:
    std::vector<VariableInfo*> fields;
    std::vector<MethodInfo*> methods;
    Symbol* name;
    Symbol* par_name;

  public:
    bool VarInBlock(Symbol* s) = 0;

};
