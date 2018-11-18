#pragma once
#include "Identifiers.h"
#include "Types.h"
#include "VarDeclaration.h"
#include "Statements.h"
#include "Expressions.h"
#include "IBase.h"
#include "YYLTYPE_struct.h"
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
    explicit IArgument(YYLTYPE location) : IBase(location) {}
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class Argument: public IArgument {
  public:
    Argument(IType* type, IIdentifier *id, YYLTYPE location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IType> type;
    std::unique_ptr<IIdentifier> id;
};

class ArgumentsList: public IListDeclaration {
  public:
    explicit ArgumentsList(YYLTYPE location);
    ArgumentsList(IArgument *var_val, YYLTYPE location);
    ArgumentsList(IArgument *var_val, ArgumentsList *var_next, YYLTYPE location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IArgument> var_val;
    ArgumentsList* var_next;
};

class IMethodDeclaration : public IBase {
  public:
    explicit IMethodDeclaration(YYLTYPE location) : IBase(location) {}
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class MethodDeclaration: public IMethodDeclaration {
  public:
    MethodDeclaration(IType* type, IIdentifier* id, ArgumentsList* args, VarDeclarationsList* vars, StatementsList* statements, ReturnStatement* exp, YYLTYPE location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;
    std::unique_ptr<IType> type;
    std::unique_ptr<IIdentifier> id;
    std::unique_ptr<ArgumentsList> args;
    std::unique_ptr<VarDeclarationsList> vars;
    std::unique_ptr<StatementsList> statements;
    std::unique_ptr<ReturnStatement> exp;
};

class MethodDeclarationsList: public IListDeclaration {
  public:
    explicit MethodDeclarationsList(YYLTYPE location);
    MethodDeclarationsList(IMethodDeclaration *method_val, YYLTYPE location);
    MethodDeclarationsList(IMethodDeclaration *var_val, MethodDeclarationsList *method_next, YYLTYPE location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IMethodDeclaration> method_val;
    MethodDeclarationsList* method_next;
};

class ASTMethodsList : public IListDeclaration {
  public:
    ASTMethodsList(std::vector<std::unique_ptr<IMethodDeclaration>>* methods, YYLTYPE location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<std::vector<std::unique_ptr<IMethodDeclaration>>> methods;
};

class ASTMethodDeclaration : public IMethodDeclaration {
  public:
    ASTMethodDeclaration(IType* type, IIdentifier* id, IListDeclaration* args, IListDeclaration* vars, IListDeclaration* statements, IStatement* exp, YYLTYPE location);
    void Accept(IVisitor *v) const override;
    char* Name() const override;

    std::unique_ptr<IType> type;
    std::unique_ptr<IIdentifier> id;
    std::unique_ptr<IListDeclaration> args;
    std::unique_ptr<IListDeclaration> vars;
    std::unique_ptr<IListDeclaration> statements;
    std::unique_ptr<IStatement> exp;
};

class ASTArgumentsList : public IListDeclaration {
  public:
    explicit ASTArgumentsList(std::vector<std::unique_ptr<IArgument>>* arguments, YYLTYPE location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<std::vector<std::unique_ptr<IArgument>>> arguments;
};
