#pragma once
#include "IVisitor.h"
#include "IBase.h"
#include "LocStruct.h"
#include "SymbolTable/Symbol.h"
#include <string>
#include <utility>

class IVisitor;

class IIdentifier : public IBase {
  public:
    explicit IIdentifier(LocStruct location) : IBase(location) {}
    virtual void Accept( IVisitor* v ) const = 0;
    virtual char* Name() const = 0;
};

class Identifier : public IIdentifier {
  public:
    Identifier(Symbol* str, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    Symbol* id;
};