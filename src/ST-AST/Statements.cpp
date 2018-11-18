#include <cassert>
#include "Statements.h"
IfStatement::IfStatement(IExp *exp, IStatement *statement1, IStatement *statement2, YYLTYPE location)
    : IStatement(location), exp(exp), statement1(statement1), statement2(statement2) {
    assert(exp != nullptr);
    assert(statement1 != nullptr);
    assert(statement2 != nullptr);
}
void IfStatement::Accept(IVisitor *v) const {
    v->visit(this);
}

char *IfStatement::Name() const {
    return const_cast<char *>("IfStatement");
}

WhileStatement::WhileStatement(IExp *exp, IStatement *statement, YYLTYPE location) : IStatement(location), exp(exp), statement(statement) {
    assert(exp != nullptr);
    assert(statement != nullptr);
}
void WhileStatement::Accept(IVisitor *v) const {
    v->visit(this);
}

char *WhileStatement::Name() const {
    return const_cast<char *>("WhileStatement");
}

OutputStatement::OutputStatement(IExp *exp, YYLTYPE location) : IStatement(location), exp(exp) {
    assert(exp != nullptr);
}
void OutputStatement::Accept(IVisitor *v) const {
    v->visit(this);
}

char *OutputStatement::Name() const {
    return const_cast<char *>("OutputStatement");
}

AssignStatement::AssignStatement(IExp *exp, IIdentifier *identifier, YYLTYPE location) : IStatement(location), exp(exp), identifier(identifier) {
    assert(exp != nullptr);
    assert(identifier != nullptr);
}
void AssignStatement::Accept(IVisitor *v) const {
    v->visit(this);
}

char *AssignStatement::Name() const {
    return const_cast<char *>("AssignStatement");
}

ArrayAssignStatement::ArrayAssignStatement(IIdentifier *identifier, IExp *exp1, IExp *exp2, YYLTYPE location)
    : IStatement(location), identifier(identifier), exp1(exp1), exp2(exp2) {
    assert(identifier != nullptr);
    assert(exp1 != nullptr);
    assert(exp2 != nullptr);
}
void ArrayAssignStatement::Accept(IVisitor *v) const {
    v->visit(this);
}

char *ArrayAssignStatement::Name() const {
    return const_cast<char *>("ArrayAssignStatement");
}

StatementsList::StatementsList(YYLTYPE location) : IListDeclaration(location), statement_val(nullptr), statement_next(nullptr) {}
StatementsList::StatementsList(IStatement *statement_val, YYLTYPE location) : IListDeclaration(location), statement_val(statement_val), statement_next(nullptr) {}
StatementsList::StatementsList(IStatement *statement_val, StatementsList *statement_next, YYLTYPE location)
    : IListDeclaration(location), statement_val(statement_val), statement_next(statement_next) {}

void StatementsList::Accept(IVisitor *v) const {
    v->visit(this);
}

char *StatementsList::Name() const {
    return const_cast<char *>("StatementsList");
}
BraceStatement::BraceStatement(StatementsList *statements, YYLTYPE location) : IStatement(location), statements(statements) {
    assert(statements != nullptr);
}
void BraceStatement::Accept(IVisitor *v) const {
    v->visit(this);
}
char *BraceStatement::Name() const {
    return const_cast<char *>("BraceStatement");
}

ASTStatementsList::ASTStatementsList(std::vector<std::unique_ptr<IStatement>> *statements, YYLTYPE location) : IListDeclaration(location), statements(statements) {}

char *ASTStatementsList::Name() const {
    return const_cast<char *>("ASTStatementsList");
}

void ASTStatementsList::Accept(IVisitor *v) const {
    v->visit(this);
}

ASTBraceStatement::ASTBraceStatement(IListDeclaration *statements, YYLTYPE location) : IStatement(location), statements(statements) {
    assert(statements != nullptr);
}

char *ASTBraceStatement::Name() const {
    return const_cast<char *>("ASTBraceStatement");
}

void ASTBraceStatement::Accept(IVisitor *v) const {
    v->visit(this);
}
ReturnStatement::ReturnStatement(IExp *exp, YYLTYPE location) : IStatement(location), exp(exp) {
    assert(exp != nullptr);
}
void ReturnStatement::Accept(IVisitor *v) const {
    v->visit(this);
}
char *ReturnStatement::Name() const {
    return const_cast<char *>("ReturnStatement");
}
