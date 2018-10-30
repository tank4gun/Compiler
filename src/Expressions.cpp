//
// Created by daniil on 21.10.18.
//
#include "Expressions.h"

PlusExp::PlusExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}
void PlusExp::Accept( IVisitor* v) const {
    v->visit(this);
}
char* PlusExp::Name() const {
    return const_cast<char *>("PlusExp");
}


MinusExp::MinusExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}
void MinusExp::Accept( IVisitor* v) const {
    v->visit(this);
}
char* MinusExp::Name() const {
    return const_cast<char *>("MinusExp");
}


TimesExp::TimesExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}
void TimesExp::Accept( IVisitor* v) const {
    v->visit(this);
}
char* TimesExp::Name() const {
    return const_cast<char *>("TimesExp");
}


DivideExp::DivideExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}
void DivideExp::Accept( IVisitor* v) const {
    v->visit(this);
}
char* DivideExp::Name() const {
    return const_cast<char *>("DivideExp");
}


AndExp::AndExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}
void AndExp::Accept( IVisitor* v) const {
    v->visit(this);
}
char* AndExp::Name() const {
    return const_cast<char *>("AndExp");
}


LessExp::LessExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}
void LessExp::Accept( IVisitor* v) const {
    v->visit(this);
}
char* LessExp::Name() const {
    return const_cast<char *>("LessExp");
}


IndexExp::IndexExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}
void IndexExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* IndexExp::Name() const {
    return const_cast<char *>("IndexExp");
}


ExpList::ExpList(): exp_val(nullptr), exp_next(nullptr) {}
ExpList::ExpList(IExp *exp_val): exp_val(exp_val), exp_next(nullptr) {}
ExpList::ExpList(IExp *exp_val, ExpList *exp_next): exp_val(exp_val), exp_next(exp_next) {}

void ExpList::Accept(IVisitor *v) const {
    v->visit(this);
}

char *ExpList::Name() const{
    return const_cast<char *>("ExpList");
}

LengthExp::LengthExp(IExp* e1) : e1(e1) {}

void LengthExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* LengthExp::Name() const {
    return const_cast<char *>("LengthExp");
}


CallMethodExp::CallMethodExp(IExp* e1, IIdentifier* i1, ExpList* e3) : e1(e1), i1(i1), e3(e3) {}

void CallMethodExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* CallMethodExp::Name() const {
    return const_cast<char *>("CallMethodExp");
}

ASTCallMethodExp::ASTCallMethodExp(IExp* e1, IIdentifier* i1, IExp* e2) : e1(e1), i1(i1), e2(e2) {};

void ASTCallMethodExp::Accept(IVisitor *v) const {
  v->visit(this);
}

char* ASTCallMethodExp::Name() const {
  return const_cast<char *>("ASTCallMethodExp");
}

IntExp::IntExp(int num) : num(num) {}

void IntExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* IntExp::Name() const {
    return const_cast<char *>("IntExp");
}

TrueExp::TrueExp() = default;

void TrueExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* TrueExp::Name() const {
    return const_cast<char *>("TrueExp");
}


FalseExp::FalseExp() = default;

void FalseExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* FalseExp::Name() const {
    return const_cast<char *>("FalseExp");
}

IdExp::IdExp(IIdentifier *i1) : i1(i1) {}

void IdExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* IdExp::Name() const {
    return const_cast<char *>("IdExp");
}

ThisExp::ThisExp() = default;

void ThisExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* ThisExp::Name() const {
    return const_cast<char *>("ThisExp");
}

NewIntExp::NewIntExp(IExp *e1) : e1(e1) {}

void NewIntExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* NewIntExp::Name() const {
    return const_cast<char *>("NewIntExp");
}

NewIdExp::NewIdExp(IIdentifier *i1) : i1(i1) {}

void NewIdExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* NewIdExp::Name() const {
    return const_cast<char *>("NewIdExp");
}

NotExp::NotExp(IExp *e1) : e1(e1) {}

void NotExp::Accept(IVisitor *v) const {
    v->visit(this);
}

char* NotExp::Name() const {
    return const_cast<char *>("NotExp");
}
ParenExp::ParenExp(IExp *e1): e1(e1) {

}
void ParenExp::Accept(IVisitor *v) const {
    v->visit(this);
}
char *ParenExp::Name() const {
    return const_cast<char *>("ParenExp");
}

ASTExpressionDeclarations::ASTExpressionDeclarations(std::vector<IExp *>& expressions) : expressions(expressions) {}

char* ASTExpressionDeclarations::Name() const {
  return const_cast<char *>("ASTExpressionDeclarations");
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
    return const_cast<char *>("ReturnExp");
}
NewExp::NewExp(IIdentifier *id): id(id) {

}
void NewExp::Accept(IVisitor *v) const {
    v->visit(this);
}
char *NewExp::Name() const {
    return const_cast<char *>("NewExp");
}

BinOp::BinOp(BinaryOps operation, IExp* e1, IExp* e2) : operation(operation), e1(e1), e2(e2) {}

char* BinOp::Name() const {
    return const_cast<char *>("BinOp");
}

void BinOp::Accept(IVisitor *v) const {
    v->visit(this);
}