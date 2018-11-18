#pragma once
#include "IVisitor.h"
#include "IBase.h"
#include "YYLTYPE_struct.h"

class IVisitor;

class IListDeclaration : public IBase {
  public:
    explicit IListDeclaration(YYLTYPE location) : IBase(location) {}
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};
