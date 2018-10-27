#pragma once
#include <cstring>
#include "Expressions.h"
#include "Identifiers.h"
#include "IVisitor.h"

class IVisitor;
class IExp;

class IStatement {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class IfStatement : IStatement {
  public:
    IfStatement(IExp *exp, IStatement *statement1, IStatement *statement2);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IExp *exp;
    const IStatement *statement1;
    const IStatement *statement2;
};

class WhileStatement : IStatement {
  public:
    WhileStatement(IExp *exp, IStatement *statement);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IExp *exp;
    const IStatement *statement;
};

class OutputStatement : IStatement {
  public:
    explicit OutputStatement(IExp *exp);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IExp *exp;
};

class AssignStatement : IStatement {
  public:
    AssignStatement(IExp *exp, IIdentifier *identifier);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IIdentifier *identifier;
    const IExp *exp;
};

class ArrayAssignStatement : IStatement {
  public:
    ArrayAssignStatement(IIdentifier *identifier, IExp *exp1, IExp *exp2);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IIdentifier *identifier;
    const IExp *exp1;
    const IExp *exp2;
};

class StatementsList : IStatement {
  public:
    StatementsList();
    explicit StatementsList(IStatement *statement_val);
    StatementsList(IStatement *statement_val, StatementsList *statement_next);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IStatement *statement_val;
    const StatementsList *statement_next;
};