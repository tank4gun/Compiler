#pragma once
#include <vector>
#include "Expressions.h"
#include "ListDeclaration.h"
#include "IBase.h"
#include "LocStruct.h"
#include <memory>

class IVisitor;
class IExp;

class IStatement : public IBase {
  public:
    explicit IStatement(LocStruct location) : IBase(location) {}
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class IfStatement : public IStatement {
  public:
    IfStatement(IExp *exp, IStatement *statement1, IStatement *statement2, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IExp> exp;
    std::unique_ptr<IStatement> statement1;
    std::unique_ptr<IStatement> statement2;
};

class WhileStatement : public IStatement {
  public:
    WhileStatement(IExp *exp, IStatement *statement, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IExp> exp;
    std::unique_ptr<IStatement> statement;
};

class OutputStatement : public IStatement {
  public:
    OutputStatement(IExp *exp, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IExp> exp;
};

class AssignStatement : public IStatement {
  public:
    AssignStatement(IExp *exp, Identifier *identifier, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<Identifier> identifier;
    std::unique_ptr<IExp> exp;
};

class ArrayAssignStatement : public IStatement {
  public:
    ArrayAssignStatement(Identifier *identifier, IExp *exp1, IExp *exp2, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<Identifier> identifier;
    std::unique_ptr<IExp> exp1;
    std::unique_ptr<IExp> exp2;
};

class StatementsList : public IListDeclaration {
  public:
    explicit StatementsList(LocStruct location);
    StatementsList(IStatement *statement_val, LocStruct location);
    StatementsList(IStatement *statement_val, StatementsList *statement_next, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IStatement> statement_val;
    StatementsList *statement_next;
};

class BraceStatement : public IStatement {
  public:
    BraceStatement(StatementsList* statements, LocStruct location);
    void Accept(IVisitor *v) const override;
    char *Name() const override;

    std::unique_ptr<StatementsList> statements;
};


class ASTStatementsList : public IListDeclaration {
  public:
    ASTStatementsList(std::vector<std::unique_ptr<IStatement>>* statements, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<std::vector<std::unique_ptr<IStatement>>> statements;
};

class ASTBraceStatement : public IStatement {
  public:
    ASTBraceStatement(IListDeclaration *statements, LocStruct location);
    void Accept(IVisitor *v) const override;
    char *Name() const override;

    std::unique_ptr<IListDeclaration> statements;
};

class ReturnStatement: public IStatement {
  public:
    ReturnStatement(IExp* exp, LocStruct location);
    void Accept(IVisitor* v) const override;
    char *Name() const override;

    std::unique_ptr<IExp> exp;
};