#pragma once
#include "IVisitor.h"
#include "IBase.h"
#include "LocStruct.h"
#include "SymbolTable/Symbol.h"
#include <string>
#include <utility>

class IVisitor;

class Identifier : public IBase {
  public:
    Identifier(Symbol* str, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    Symbol* id;
};