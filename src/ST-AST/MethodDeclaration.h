#pragma once
#include "Identifiers.h"
#include "Types.h"
#include "VarDeclaration.h"
#include "Statements.h"
#include "Expressions.h"
#include "IBase.h"
#include "LocStruct.h"
#include <memory>

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

class IArgument : public IBase {
  public:
    explicit IArgument(LocStruct location) : IBase(location) {}
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class Argument: public IArgument {
  public:
    Argument(IType* type, Identifier *id, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IType> type;
    std::unique_ptr<Identifier> id;
};

class ArgumentsList: public IListDeclaration {
  public:
    explicit ArgumentsList(LocStruct location);
    ArgumentsList(IArgument *var_val, LocStruct location);
    ArgumentsList(IArgument *var_val, ArgumentsList *var_next, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IArgument> var_val;
    ArgumentsList* var_next;
};

class IMethodDeclaration : public IBase {
  public:
    explicit IMethodDeclaration(LocStruct location) : IBase(location) {}
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class MethodDeclaration: public IMethodDeclaration {
  public:
    MethodDeclaration(IType* type, Identifier* id, ArgumentsList* args, VarDeclarationsList* vars, StatementsList* statements, ReturnStatement* exp, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;
    std::unique_ptr<IType> type;
    std::unique_ptr<Identifier> id;
    std::unique_ptr<ArgumentsList> args;
    std::unique_ptr<VarDeclarationsList> vars;
    std::unique_ptr<StatementsList> statements;
    std::unique_ptr<ReturnStatement> exp;
};

class MethodDeclarationsList: public IListDeclaration {
  public:
    explicit MethodDeclarationsList(LocStruct location);
    MethodDeclarationsList(IMethodDeclaration *method_val, LocStruct location);
    MethodDeclarationsList(IMethodDeclaration *var_val, MethodDeclarationsList *method_next, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IMethodDeclaration> method_val;
    MethodDeclarationsList* method_next;
};

class ASTMethodsList : public IListDeclaration {
  public:
    ASTMethodsList(std::vector<std::unique_ptr<IMethodDeclaration>>* methods, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<std::vector<std::unique_ptr<IMethodDeclaration>>> methods;
};

class ASTMethodDeclaration : public IMethodDeclaration {
  public:
    ASTMethodDeclaration(IType* type, Identifier* id, ASTArgumentsList* args, ASTVarDeclarations* vars, ASTStatementsList* statements, IStatement* exp, LocStruct location);
    void Accept(IVisitor *v) const override;
    char* Name() const override;

    std::unique_ptr<IType> type;
    std::unique_ptr<Identifier> id;
    std::unique_ptr<ASTArgumentsList> args;
    std::unique_ptr<ASTVarDeclarations> vars;
    std::unique_ptr<ASTStatementsList> statements;
    std::unique_ptr<IStatement> exp;
};

class ASTArgumentsList : public IListDeclaration {
  public:
    explicit ASTArgumentsList(std::vector<std::unique_ptr<IArgument>>* arguments, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<std::vector<std::unique_ptr<IArgument>>> arguments;
};
