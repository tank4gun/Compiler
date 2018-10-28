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
class IVarDeclaration;
class IType;
class VarDeclarationsList;
class ASTMethodDeclaration;
class ASTMethodDeclarations;
class ASTArgumentDeclarations;
class ASTVarDeclarations;
class ASTStatementDeclarations;

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
    ArgumentsList();
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

    char *Name() const override;
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

class ASTMethodDeclarations : public IMethodDeclaration {
  public:
    ASTMethodDeclarations(std::vector<IMethodDeclaration*> methods);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::vector<IMethodDeclaration*> methods;
};

class ASTMethodDeclaration : public IMethodDeclaration {
  public:
    ASTMethodDeclaration(IType* type, IIdentifier* id, IArgument* args, IVarDeclaration* vars, IStatement* statements, IExp* exp);
    void Accept(IVisitor *v) const;
    char* Name() const;

    IType *type;
    IIdentifier *id;
    IArgument*args;
    IVarDeclaration *vars;
    IStatement* statements;
    IExp *exp;
};

class ASTArgumentDeclarations : public IArgument {
  public:
    ASTArgumentDeclarations(std::vector<IArgument*> arguments);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::vector<IArgument*> arguments;
};
