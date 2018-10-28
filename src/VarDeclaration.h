#pragma once
#include "Types.h"
#include "Identifiers.h"

class IType;

class IVarDeclaration {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class VarDeclaration: public IVarDeclaration {
  public:
    VarDeclaration(IType* type, IIdentifier *id);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    IType* type;
    IIdentifier* id;
};

class VarDeclarationsList: public IVarDeclaration {
  public:
    VarDeclarationsList();
    explicit VarDeclarationsList(IVarDeclaration *var_val);
    VarDeclarationsList(IVarDeclaration *var_val, VarDeclarationsList *var_next);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IVarDeclaration *var_val;
    const VarDeclarationsList *var_next;
};

class ASTVarDeclarations : public IVarDeclaration {
  public:
    ASTVarDeclarations(std::vector<IVarDeclaration*> vars);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::vector<IVarDeclaration*> vars;
};
