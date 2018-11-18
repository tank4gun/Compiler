#pragma once
#include <vector>
#include "Expressions.h"
#include "ListDeclaration.h"
#include <memory>

class IVisitor;
class IExp;

class IStatement {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class IfStatement : public IStatement {
  public:
    IfStatement(IExp *exp, IStatement *statement1, IStatement *statement2);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IExp> exp;
    std::unique_ptr<IStatement> statement1;
    std::unique_ptr<IStatement> statement2;
};

class WhileStatement : public IStatement {
  public:
    WhileStatement(IExp *exp, IStatement *statement);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IExp> exp;
    std::unique_ptr<IStatement> statement;
};

class OutputStatement : public IStatement {
  public:
    explicit OutputStatement(IExp *exp);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IExp> exp;
};

class AssignStatement : public IStatement {
  public:
    AssignStatement(IExp *exp, IIdentifier *identifier);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IIdentifier> identifier;
    std::unique_ptr<IExp> exp;
};

class ArrayAssignStatement : public IStatement {
  public:
    ArrayAssignStatement(IIdentifier *identifier, IExp *exp1, IExp *exp2);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IIdentifier> identifier;
    std::unique_ptr<IExp> exp1;
    std::unique_ptr<IExp> exp2;
};

class StatementsList : public IListDeclaration {
  public:
    StatementsList();
    explicit StatementsList(IStatement *statement_val);
    StatementsList(IStatement *statement_val, StatementsList *statement_next);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IStatement> statement_val;
    StatementsList *statement_next;
};

class BraceStatement : public IStatement {
  public:
    explicit BraceStatement(StatementsList* statements);
    void Accept(IVisitor *v) const override;
    char *Name() const override;

    std::unique_ptr<StatementsList> statements;
};


class ASTStatementsList : public IListDeclaration {
  public:
    explicit ASTStatementsList(std::vector<std::unique_ptr<IStatement>>* statements);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<std::vector<std::unique_ptr<IStatement>>> statements;
};

class ASTBraceStatement : public IStatement {
  public:
    explicit ASTBraceStatement(IListDeclaration *statements);
    void Accept(IVisitor *v) const override;
    char *Name() const override;

    std::unique_ptr<IListDeclaration> statements;
};

class ReturnStatement: public IStatement {
  public:
    explicit ReturnStatement(IExp* exp);
    void Accept(IVisitor* v) const override;
    char *Name() const override;

    std::unique_ptr<IExp> exp;
};