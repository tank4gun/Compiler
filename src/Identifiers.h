#pragma once
#include "IVisitor.h"

class IVisitor;

class IIdentifier {
  public:
    virtual void Accept( IVisitor* v ) const = 0;
    virtual char* Name() const = 0;
};

class Identifier : IIdentifier {
  public:
    Identifier(char* id);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    const char* id;
};