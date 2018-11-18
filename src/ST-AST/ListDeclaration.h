#pragma once
#include "IVisitor.h"

class IVisitor;

class IListDeclaration {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};
