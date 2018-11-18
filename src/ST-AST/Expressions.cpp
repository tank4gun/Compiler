//
// Created by daniil on 21.10.18.
//
#include "Expressions.h"
#include <cassert>


IndexExp::IndexExp(IExp* e1, IExp* e2, YYLTYPE location) : IExp(location), e1(e1), e2(e2) {
    assert(e1 != nullptr);
    assert(e2 != nullptr);
}

void IndexExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* IndexExp::Name() const {
    return const_cast<char *>("IndexExp");
}


ExpList::ExpList(YYLTYPE location) : IExp(location), exp_val(nullptr), exp_next(nullptr) {}
ExpList::ExpList(IExp *exp_val, YYLTYPE location) : IExp(location), exp_val(exp_val), exp_next(nullptr) {}
ExpList::ExpList(IExp *exp_val, ExpList *exp_next, YYLTYPE location) : IExp(location), exp_val(exp_val), exp_next(exp_next) {}

void ExpList::Accept(IVisitor *v) const {
    v->visit(this);
}

char *ExpList::Name() const{
    return const_cast<char *>("ExpList");
}

LengthExp::LengthExp(IExp* e1, YYLTYPE location) : IExp(location), e1(e1) {
    assert(e1 != nullptr);
}

void LengthExp::Accept(IVisitor* v) const {
    v->visit(this);
}

char* LengthExp::Name() const {
    return const_cast<char *>("LengthExp");
}


CallMethodExp::CallMethodExp(IExp* e1, IIdentifier* i1, ExpList* e3, YYLTYPE location) : IExp(location), e1(e1), i1(i1), e3(e3) {
    assert(e1 != nullptr);
    assert(i1 != nullptr);
    assert(e3 != nullptr);
}

void CallMethodExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* CallMethodExp::Name() const {
    return const_cast<char *>("CallMethodExp");
}

ASTCallMethodExp::ASTCallMethodExp(IExp* e1, IIdentifier* i1, IListDeclaration* e2, YYLTYPE location) : IExp(location), e1(e1), i1(i1), e2(e2) {
    assert(e1 != nullptr);
    assert(i1 != nullptr);
    assert(e2 != nullptr);
}

void ASTCallMethodExp::Accept(IVisitor *v) const {
  v->visit(this);
}

char* ASTCallMethodExp::Name() const {
  return const_cast<char *>("ASTCallMethodExp");
}

IntExp::IntExp(int num, YYLTYPE location) : IExp(location), num(num) {}

void IntExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* IntExp::Name() const {
    return const_cast<char *>("IntExp");
}

BooleanExp::BooleanExp(bool value, YYLTYPE location) : IExp(location), value(value) {}

void BooleanExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* BooleanExp::Name() const {
    return const_cast<char *>("BooleanExp");
}

IdExp::IdExp(IIdentifier *i1, YYLTYPE location) : IExp(location), i1(i1) {
    assert(i1 != nullptr);
}

void IdExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* IdExp::Name() const {
    return const_cast<char *>("IdExp");
}

ThisExp::ThisExp(YYLTYPE location) : IExp(location) {}

void ThisExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* ThisExp::Name() const {
    return const_cast<char *>("ThisExp");
}

NewIntExp::NewIntExp(IExp *e1, YYLTYPE location) : IExp(location), e1(e1) {
    assert(e1 != nullptr);
}

void NewIntExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* NewIntExp::Name() const {
    return const_cast<char *>("NewIntExp");
}

NewIdExp::NewIdExp(IIdentifier *i1, YYLTYPE location) : IExp(location), i1(i1) {
    assert(i1 != nullptr);
}

void NewIdExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* NewIdExp::Name() const {
    return const_cast<char *>("NewIdExp");
}

NotExp::NotExp(IExp *e1, YYLTYPE location) : IExp(location), e1(e1) {
    assert(e1 != nullptr);
}

void NotExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* NotExp::Name() const {
    return const_cast<char *>("NotExp");
}

ASTExpressionDeclarations::ASTExpressionDeclarations(std::vector<std::unique_ptr<IExp>>* expressions, YYLTYPE location) : IListDeclaration(location), expressions(expressions) {}

char* ASTExpressionDeclarations::Name() const {
  return const_cast<char *>("ASTExpressionDeclarations");
}

void ASTExpressionDeclarations::Accept(IVisitor *v) const {
  v->visit(this);
}
NewExp::NewExp(IIdentifier *id, YYLTYPE location) : IExp(location), id(id) {
    assert(id != nullptr);
}
void NewExp::Accept(IVisitor *v) const {
    v->visit(this);
}
char *NewExp::Name() const {
    return const_cast<char *>("NewExp");
}

BinOp::BinOp(BinaryOps operation, IExp* e1, IExp* e2, YYLTYPE location) : IExp(location), operation(operation), e1(e1), e2(e2) {
    assert(e1 != nullptr);
    assert(e2 != nullptr);
}

char* BinOp::Name() const {
    return const_cast<char *>("BinOp");
}

void BinOp::Accept(IVisitor *v) const {
    v->visit(this);
}