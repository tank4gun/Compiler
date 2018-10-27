#pragma once
#include "Identifiers.h"
#include "Types.h"
#include "VarDeclaration.h"
#include "Statements.h"
#include "Expressions.h"
#include "ASTClasses.h"

class StatementsList;
class IExp;
class IStatement;
class IType;
class VarDeclarationsList;
class ASTMethodDeclaration;

class IArgument {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class Argument: public IArgument {
  public:
    Argument(IType* type, IIdentifier *id);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    IType* type;
    IIdentifier* id;
};

class ArgumentsList: public IArgument {
  public:
    explicit ArgumentsList(IArgument *var_val);
    ArgumentsList(IArgument *var_val, ArgumentsList *var_next);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IArgument *var_val;
    const ArgumentsList *var_next;
};

class IMethodDeclaration {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class MethodDeclaration: public IMethodDeclaration {
  public:
    MethodDeclaration(IType* type, IIdentifier* id, ArgumentsList* args, VarDeclarationsList* vars, StatementsList* statements, IExp* exp);

    void Accept(IVisitor *v) const override;

    IType *type;
    IIdentifier *id;
    ArgumentsList *args;
    VarDeclarationsList *vars;
    StatementsList *statements;
    IExp *exp;
};

class MethodDeclarationsList: public IMethodDeclaration {
  public:
    MethodDeclarationsList();
    explicit MethodDeclarationsList(IMethodDeclaration *method_val);
    MethodDeclarationsList(IMethodDeclaration *var_val, MethodDeclarationsList *method_next);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IMethodDeclaration *method_val;
    const MethodDeclarationsList *method_next;
};