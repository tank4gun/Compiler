#pragma once
#include "IVisitor.h"
#include "Identifiers.h"

class IType {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class IntArrayType : public IType {
  public:
    IntArrayType();

    void Accept(IVisitor *v) const override;

    char *Name() const override;
};

class BooleanType: public IType {
  public:
    BooleanType();

    void Accept(IVisitor *v) const override;

    char *Name() const override;
};

class IntType: public IType {
  public:
    IntType();

    void Accept(IVisitor *v) const override;

    char *Name() const override;
};

class IdentifierType: public IType {
  public:
    explicit IdentifierType(IIdentifier* id);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    IIdentifier *id;
};