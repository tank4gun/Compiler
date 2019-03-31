#include "IIRExp.h"

#include <IRTree/IIRStm.h>
#include <CanonicalTree/ICTVisitor.h>

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

TempExp::TempExp(Temp value) : value(value) {}

void TempExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}

BinaryExp::BinaryExp(BinaryOps binType, IIRExp *left, IIRExp *right) : binType(binType), leftExp(left), rightExp(right) {}

void BinaryExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}

std::string BinaryExp::getType() const {
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

void IRExpList::Accept(ICTVisitor *v) const {
    v->visit( this );
}
