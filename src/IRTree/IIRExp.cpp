#include "IIRExp.h"
#include "IIRVisitor.h"

ConstExp::ConstExp(int value) :
    value(value) {
}

void ConstExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}

NameExp::NameExp(Label label) : label(label) {}

void NameExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}

TempExp::TempExp(Temp value_) : value(value_) {
}

void TempExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}

std::string TempExp::GetValueLabel() {
    return value.String();
}

BinaryExp::BinaryExp(BinaryOps binType, IIRExp *left, IIRExp *right) : binType(binType), leftExp(left), rightExp(right) {}

void BinaryExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}

std::string BinaryExp::getType() {
    switch(binType) {
        case (BinaryOps::PLUSOP): return "+";
        case (BinaryOps::MINUSOP): return "-";
        case (BinaryOps::MULTOP): return "*";
        case (BinaryOps::ANDOP): return "&&";
        default: return "";
    }
}

MemoryExp::MemoryExp(IIRExp *exp) : exp(exp) {}

void MemoryExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}

CallExp::CallExp(IIRExp *funcExp, IRExpList *args) : funcExp(funcExp), args(args) {}

void CallExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}

ESeqExp::ESeqExp(IIRStm *stm, IIRExp *exp) : stm(stm), exp(exp) {}

void ESeqExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}