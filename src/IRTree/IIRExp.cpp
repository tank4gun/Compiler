#include "IIRExp.h"

#include <IRTree/IIRStm.h>
#include <CanonicalTree/ICTVisitor.h>

ConstExp::ConstExp(int value) :
    value(value) {
}

void ConstExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::unique_ptr<IIRExp> ConstExp::Copy()
{
    return std::move( std::make_unique<ConstExp>( value) );
}

NameExp::NameExp(Label label) : label(label) {}

void NameExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::unique_ptr<IIRExp> NameExp::Copy()
{
    return std::move( std::make_unique<NameExp>( label) );
}

TempExp::TempExp(Temp value) : value(value) {}

void TempExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::unique_ptr<IIRExp> TempExp::Copy()
{
    return std::move( std::make_unique<TempExp>( value) );
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
std::unique_ptr<IIRExp> BinaryExp::Copy()
{
    return std::move( std::make_unique<BinaryExp>(binType, leftExp->Copy().release(), rightExp->Copy().release()) );
}

MemoryExp::MemoryExp(IIRExp *exp) : exp(exp) {}

void MemoryExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::unique_ptr<IIRExp> MemoryExp::Copy()
{
    return std::move( std::unique_ptr<IIRExp>( new MemoryExp( (exp->Copy()).release() ) ) );
}


CallExp::CallExp(IIRExp *funcExp, IRExpList *args) : funcExp(funcExp), args(args) {}

void CallExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::unique_ptr<IIRExp> CallExp::Copy()
{
    return std::move( std::make_unique<CallExp>( funcExp->Copy().release(), args->Copy().release() ) );
}


ESeqExp::ESeqExp(IIRStm *stm, IIRExp *exp) : stm(stm), exp(exp) {}

void ESeqExp::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::unique_ptr<IIRExp> ESeqExp::Copy()
{
    return std::move( std::make_unique<ESeqExp>( stm->Copy().release(), exp->Copy().release() ) );
}


void IRExpList::Accept(ICTVisitor *v) const {
    v->visit( this );
}
std::unique_ptr<IRExpList> IRExpList::Copy()
{
    std::unique_ptr<IRExpList> list = std::make_unique<IRExpList>();
    for( const auto& expression : expressions ) {
        list->expressions.emplace_back( expression->Copy().release() );
    }
    return list;
}
