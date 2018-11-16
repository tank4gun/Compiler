#pragma once
#include "Identifiers.h"
#include "Types.h"
#include "VarDeclaration.h"
#include "Statements.h"
#include "Expressions.h"

class StatementsList;
class IExp;
class IStatement;
class IVarDeclaration;
class IType;
class VarDeclarationsList;
class ASTMethodDeclaration;
class ASTMethodsList;
class ASTArgumentsList;
class ASTVarDeclarations;
class ASTStatementsList;
class ReturnStatement;

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

class ArgumentsList: public IListDeclaration {
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
    MethodDeclaration(IType* type, IIdentifier* id, ArgumentsList* args, VarDeclarationsList* vars, StatementsList* statements, ReturnStatement* exp);

    void Accept(IVisitor *v) const override;

    char *Name() const override;
    IType *type;
    IIdentifier *id;
    ArgumentsList *args;
    VarDeclarationsList *vars;
    StatementsList *statements;
    ReturnStatement *exp;
};

class MethodDeclarationsList: public IListDeclaration {
  public:
    MethodDeclarationsList();
    explicit MethodDeclarationsList(IMethodDeclaration *method_val);
    MethodDeclarationsList(IMethodDeclaration *var_val, MethodDeclarationsList *method_next);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IMethodDeclaration *method_val;
    const MethodDeclarationsList *method_next;
};

class ASTMethodsList : public IListDeclaration {
  public:
    explicit ASTMethodsList(std::vector<IMethodDeclaration*>& methods);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::vector<IMethodDeclaration*> methods;
};

class ASTMethodDeclaration : public IMethodDeclaration {
  public:
    ASTMethodDeclaration(IType* type, IIdentifier* id, IListDeclaration* args, IListDeclaration* vars, IListDeclaration* statements, IStatement* exp);
    void Accept(IVisitor *v) const override;
    char* Name() const override;

    IType *type;
    IIdentifier *id;
    IListDeclaration*args;
    IListDeclaration *vars;
    IListDeclaration* statements;
    IStatement *exp;
};

class ASTArgumentsList : public IListDeclaration {
  public:
    explicit ASTArgumentsList(std::vector<IArgument*>& arguments);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::vector<IArgument*> arguments;
};
