#pragma once
#include "IVisitor.h"
#include "Identifiers.h"
#include "IBase.h"
#include "LocStruct.h"
#include <memory>

class IVisitor;
class Identifier;

class IType : public IBase {
  public:
    explicit IType(LocStruct location) : IBase(location) {}
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class IntArrayType : public IType {
  public:
    explicit IntArrayType(LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;
};

class BooleanType: public IType {
  public:
    explicit BooleanType(LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;
};

class IntType: public IType {
  public:
    explicit IntType(LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;
};

class IdentifierType: public IType {
  public:
    IdentifierType(Identifier* id, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<Identifier> id;
};