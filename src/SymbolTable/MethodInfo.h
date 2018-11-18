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
    bool VarInBlock(std::unique_ptr<Symbol>& s) override {
        if (args.find(s) != args.end()) {
            return true;
        }
        return vars.find(s) != vars.end();
    }

    std::unique_ptr<Symbol> name;
    std::unique_ptr<IType> returnType;
    std::map<std::unique_ptr<Symbol>, std::unique_ptr<VariableInfo>> args;
    std::map<std::unique_ptr<Symbol>, std::unique_ptr<VariableInfo>> vars;
};
