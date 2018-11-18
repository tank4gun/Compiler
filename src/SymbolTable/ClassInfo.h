//
// Created by daniil on 18.11.18.
//
#pragma once
#include <vector>
#include <map>
#include "VisibilityBlock.h"
#include "MethodInfo.h"
#include "VariableInfo.h"

class ClassInfo : VisibilityBlock {
  public:
    std::map<Symbol*, VariableInfo*> fields;
    std::map<Symbol*, MethodInfo*> methods;
    Symbol* name;
    Symbol* par_name;
    bool VarInBlock(Symbol* s) override {
        return true;
    }

};
