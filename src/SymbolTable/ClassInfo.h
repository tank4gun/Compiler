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
    std::vector<std::unique_ptr<VariableInfo>> fields;
    std::vector<std::unique_ptr<MethodInfo>> methods;
    std::unique_ptr<Symbol> name;
    std::unique_ptr<Symbol> par_name;

  public:
    bool VarInBlock(std::unique_ptr<Symbol>& s) override;

};
