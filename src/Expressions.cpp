//
// Created by daniil on 21.10.18.
//
#include <stdio.h>
#include <string.h>
#include "Expressions.h"
//#include "Identifiers.h"


PlusExp::PlusExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

void PlusExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* PlusExp::Name() const {
    char* name = new char[7];
    strcpy(name, "PlusExp");
    return name;
}


MinusExp::MinusExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

void MinusExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* MinusExp::Name() const {
    char* name = new char[8];
    strcpy(name, "MinusExp");
    return name;
}


TimesExp::TimesExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

void TimesExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* TimesExp::Name() const {
    char* name = new char[8];
    strcpy(name, "TimesExp");
    return name;
}


DivideExp::DivideExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

void DivideExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* DivideExp::Name() const {
    char* name = new char[9];
    strcpy(name, "DivideExp");
    return name;
}


AndExp::AndExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

void AndExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* AndExp::Name() const {
    char* name = new char[6];
    strcpy(name, "AndExp");
    return name;
}


LessExp::LessExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

void LessExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* LessExp::Name() const {
    char* name = new char[7];
    strcpy(name, "LessExp");
    return name;
}


IndexExp::IndexExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

void IndexExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* IndexExp::Name() const {
    char* name = new char[8];
    strcpy(name, "IndexExp");
    return name;
}


ExpList::ExpList(): exp_val(nullptr), exp_next(nullptr) {}
ExpList::ExpList(IExp *exp_val): exp_val(exp_val), exp_next(nullptr) {}
ExpList::ExpList(IExp *exp_val, ExpList *exp_next): exp_val(exp_val), exp_next(exp_next) {}

void ExpList::Accept(IVisitor *v) const {
    v->visit(this);
}

char *ExpList::Name() const{
    char *name = new char[7];
    strcpy(name, "ExpList");
    return name;
}

LengthExp::LengthExp(IExp* e1) : e1(e1) {}

void LengthExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* LengthExp::Name() const {
    char* name = new char[9];
    strcpy(name, "LengthExp");
    return name;
}


CallMethodExp::CallMethodExp(IExp* e1, IIdentifier* i1, ExpList* e3) : e1(e1), i1(i1), e3(e3) {}

void CallMethodExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* CallMethodExp::Name() const {
    char* name = new char[13];
    strcpy(name, "CallMethodExp");
    return name;
}

ASTCallMethodExp::ASTCallMethodExp(IExp* e1, IIdentifier* i1, IExp* e2) : e1(e1), i1(i1), e2(e2) {};

void ASTCallMethodExp::Accept(IVisitor *v) const {
  v->visit(this);
}

char* ASTCallMethodExp::Name() const {
  char* name = new char[15];
  strcpy(name, "ASTCallMethodExp");
  return name;
}

IntExp::IntExp(int num) : num(num) {}

void IntExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* IntExp::Name() const {
    char* name = new char[6];
    strcpy(name, "IntExp");
    return name;
}

TrueExp::TrueExp() = default;

void TrueExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* TrueExp::Name() const {
    char* name = new char[7];
    strcpy(name, "TrueExp");
    return name;
}


FalseExp::FalseExp() = default;

void FalseExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* FalseExp::Name() const {
    char* name = new char[8];
    strcpy(name, "FalseExp");
    return name;
}

IdExp::IdExp(IIdentifier *i1) : i1(i1) {}

void IdExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* IdExp::Name() const {
    char* name = new char[5];
    strcpy(name, "IdExp");
    return name;
}

ThisExp::ThisExp() = default;

void ThisExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* ThisExp::Name() const {
    char* name = new char[7];
    strcpy(name, "ThisExp");
    return name;
}

NewIntExp::NewIntExp(IExp *e1) : e1(e1) {}

void NewIntExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* NewIntExp::Name() const {
    char* name = new char[9];
    strcpy(name, "NewIntExp");
    return name;
}

NewIdExp::NewIdExp(IIdentifier *i1) : i1(i1) {}

void NewIdExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* NewIdExp::Name() const {
    char* name = new char[8];
    strcpy(name, "NewIdExp");
    return name;
}

NotExp::NotExp(IExp *e1) : e1(e1) {}

void NotExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* NotExp::Name() const {
    char* name = new char[6];
    strcpy(name, "NotExp");
    return name;
}
ParenExp::ParenExp(IExp *e1): e1(e1) {

}
void ParenExp::Accept(IVisitor *v) const {
    v->visit(this);
}
char *ParenExp::Name() const {
    char* name = new char[8];
    strcpy(name, "ParenExp");
    return name;
}

ASTExpressionDeclarations::ASTExpressionDeclarations(std::vector<IExp *> expressions) : expressions(std::move(expressions)) {}

char* ASTExpressionDeclarations::Name() const {
  char* name = new char[25];
  strcpy(name, "ASTExpressionDeclarations");
  return name;
}

void ASTExpressionDeclarations::Accept(IVisitor *v) const {
  v->visit(this);
}
ReturnExp::ReturnExp(IExp *exp): exp(exp) {

}
void ReturnExp::Accept(IVisitor *v) const {
    v->visit(this);
}
char *ReturnExp::Name() const {
    char *name = new char[9];
    strcpy(name, "ReturnExp");
    return name;
}
NewExp::NewExp(IIdentifier *id): id(id) {

}
void NewExp::Accept(IVisitor *v) const {
    v->visit(this);
}
char *NewExp::Name() const {
    char *name=  new char[6];
    strcpy(name, "NewExp");
    return name;
}

BinOp::BinOp(BinaryOps operation, IExp* e1, IExp* e2) : operation(operation), e1(e1), e2(e2) {}

char* BinOp::Name() const {
    char* name = new char[5];
    strcpy(name, "BinOp");
    return name;
}

void BinOp::Accept(IVisitor *v) const {
    v->visit(this);
}