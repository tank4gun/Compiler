#pragma once
#include "Types.h"
#include "Identifiers.h"
#include "ListDeclaration.h"
#include "IBase.h"
#include "LocStruct.h"
#include <memory>

class IType;

class IVarDeclaration : public IBase {
  public:
    explicit IVarDeclaration(LocStruct location) : IBase(location) {}
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class VarDeclaration: public IVarDeclaration {
  public:
    VarDeclaration(IType* type, IIdentifier *id, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IType> type;
    std::unique_ptr<IIdentifier> id;
};

class VarDeclarationsList: public IListDeclaration {
  public:
    explicit VarDeclarationsList(LocStruct location);
    VarDeclarationsList(IVarDeclaration *var_val, LocStruct location);
    VarDeclarationsList(IVarDeclaration *var_val, VarDeclarationsList *var_next, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IVarDeclaration> var_val;
    VarDeclarationsList *var_next;
};

class ASTVarDeclarations : public IListDeclaration {
  public:
    explicit ASTVarDeclarations(std::vector<std::unique_ptr<IVarDeclaration>>* vars, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<std::vector<std::unique_ptr<IVarDeclaration>>> vars;
};
