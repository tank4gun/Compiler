#pragma once
#include "IVisitor.h"
#include <string>
#include <SymbolTable/Symbol.h>

class IVisitor;

class IIdentifier {
  public:
    virtual void Accept( IVisitor* v ) const = 0;
    virtual char* Name() const = 0;
};

class Identifier : public IIdentifier {
  public:
    explicit Identifier(Symbol* smb): id(smb) {}
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    Symbol* id;
};