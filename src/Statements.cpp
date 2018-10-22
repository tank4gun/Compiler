#include "Statements.h"

IfStatement::IfStatement(IExp *exp, IStatement *statement1, IStatement *statement2) : exp(exp), statement1(statement1),
                                                                                      statement2(statement2) {}
void IfStatement::Accept(IVisitor *v) const {
    v->visit(this);
}


char *IfStatement::Name() {
    char* name = new char[11];
    strcpy(name, "IfStatement");
    return name;
}


WhileStatement::WhileStatement(IExp *exp, IStatement *statement): exp(exp), statement(statement) {}
void WhileStatement::Accept(IVisitor *v) const {
    v->visit(this);
}


char *WhileStatement::Name() {
    char* name = new char[14];
    strcpy(name, "WhileStatement");
    return name;
}


OutputStatement::OutputStatement(IExp *exp): exp(exp) {}
void OutputStatement::Accept(IVisitor *v) const {
    v->visit(this);
}


char *OutputStatement::Name() {
    char* name = new char[15];
    strcpy(name, "OutputStatement");
    return name;
}


AssignStatement::AssignStatement(IExp *exp, IIdentifier *identifier): exp(exp), identifier(identifier) {}
void AssignStatement::Accept(IVisitor *v) const {
    v->visit(this);
}


char *AssignStatement::Name() {
    char* name = new char[15];
    strcpy(name, "AssignStatement");
    return name;
}


ArrayAssignStatement::ArrayAssignStatement(IIdentifier *identifier, IExp *exp1, IExp *exp2): identifier(identifier),
                                                exp1(exp1), exp2(exp2) {}
void ArrayAssignStatement::Accept(IVisitor *v) const {
    v->visit(this);
}


char *ArrayAssignStatement::Name() {
    char* name = new char[20];
    strcpy(name, "ArrayAssignStatement");
    return name;
}

StatementsList::StatementsList(): statement_val(nullptr), statement_next(nullptr) {}
StatementsList::StatementsList(IStatement *statement_val): statement_val(statement_val), statement_next(nullptr) {}
StatementsList::StatementsList(IStatement *statement_val, StatementsList *statement_next): statement_val(statement_val), statement_next(statement_next) {}

void StatementsList::Accept(IVisitor *v) const {
    v->visit(this);
}

char *StatementsList::Name() {
    char *name = new char[14];
    strcpy(name, "StatementsList");
    return name;
}
