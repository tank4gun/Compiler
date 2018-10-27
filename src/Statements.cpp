#include "Statements.h"

IfStatement::IfStatement(IExp *exp, IStatement *statement1, IStatement *statement2) : exp(exp), statement1(statement1),
                                                                                      statement2(statement2) {}
void IfStatement::Accept(IVisitor *v) const {
    v->visit(this);
}


char *IfStatement::Name() const{
    char* name = new char[11];
    strcpy(name, "IfStatement");
    return name;
}


WhileStatement::WhileStatement(IExp *exp, IStatement *statement): exp(exp), statement(statement) {}
void WhileStatement::Accept(IVisitor *v) const {
    v->visit(this);
}


char *WhileStatement::Name() const{
    char* name = new char[14];
    strcpy(name, "WhileStatement");
    return name;
}


OutputStatement::OutputStatement(IExp *exp): exp(exp) {}
void OutputStatement::Accept(IVisitor *v) const {
    v->visit(this);
}


char *OutputStatement::Name() const{
    char* name = new char[15];
    strcpy(name, "OutputStatement");
    return name;
}


AssignStatement::AssignStatement(IExp *exp, IIdentifier *identifier): exp(exp), identifier(identifier) {}
void AssignStatement::Accept(IVisitor *v) const {
    v->visit(this);
}


char *AssignStatement::Name() const{
    char* name = new char[15];
    strcpy(name, "AssignStatement");
    return name;
}


ArrayAssignStatement::ArrayAssignStatement(IIdentifier *identifier, IExp *exp1, IExp *exp2): identifier(identifier),
                                                exp1(exp1), exp2(exp2) {}
void ArrayAssignStatement::Accept(IVisitor *v) const {
    v->visit(this);
}


char *ArrayAssignStatement::Name() const{
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

char *StatementsList::Name() const{
    char *name = new char[14];
    strcpy(name, "StatementsList");
    return name;
}
BraceStatement::BraceStatement(StatementsList *statements): statements(statements) {}
void BraceStatement::Accept(IVisitor *v) const {
    v->visit(this);
}
char *BraceStatement::Name() const {
    char *name = new char[14];
    strcpy(name, "BraceStatement");
    return name;
}
