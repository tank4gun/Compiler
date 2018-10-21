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


AddExp::AddExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

void AddExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* AddExp::Name() const {
    char* name = new char[6];
    strcpy(name, "AddExp");
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


LengthExp::LengthExp(IExp* e1) : e1(e1) {}

void LengthExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* LengthExp::Name() const {
    char* name = new char[9];
    strcpy(name, "LengthExp");
    return name;
}


CallMethodExp::CallMethodExp(IExp* e1, IIdentifier* i1, IExp* e2, IExp* e3) : e1(e1), e2(e2) {}

void CallMethodExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* CallMethodExp::Name() const {
    char* name = new char[13];
    strcpy(name, "CallMethodExp");
    return name;
}

TrueExp::TrueExp() {}

void TrueExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* TrueExp::Name() const {
    char* name = new char[7];
    strcpy(name, "TrueExp");
    return name;
}


FalseExp::FalseExp() {}

void FalseExp::Accept( IVisitor* v) const {
    v->visit(this);
}

char* FalseExp::Name() const {
    char* name = new char[8];
    strcpy(name, "FalseExp");
    return name;
}
