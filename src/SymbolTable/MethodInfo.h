#pragma once
#include <map>
#include "Symbol.h"
#include "ST-AST/Types.h"
#include "VariableInfo.h"
#include "VisibilityBlock.h"
#include <memory>

class MethodInfo : public VisibilityBlock {
  public:
    MethodInfo() = default;
    MethodInfo(Symbol* name, IType* returnType) : name(name), returnType(returnType) {}
    bool VarInBlock(Symbol* s) override {
        if (args.find(s) != args.end()) {
            return true;
        }
        return vars.find(s) != vars.end();
    }

    Symbol* name;
    IType* returnType;
    std::map<Symbol*, VariableInfo*> args;
    std::map<Symbol*, VariableInfo*> vars;
};
