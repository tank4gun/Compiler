#include "IIRStm.h"

#include <CanonicalTree/ICTVisitor.h>

MoveStm::MoveStm(IIRExp *from, IIRExp *to): from(from), to(to) {}
void MoveStm::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::unique_ptr<IIRStm> MoveStm::Copy()
{
    return std::move( std::make_unique<MoveStm>( to->Copy().release(), from->Copy().release() ) );
}

ExpStm::ExpStm(IIRExp *exp): exp(exp) {}
void ExpStm::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::unique_ptr<IIRStm> ExpStm::Copy()
{
    return std::move( std::make_unique<ExpStm>( exp->Copy().release()) );
}

JumpStm::JumpStm(Label target): target(target) {}
void JumpStm::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::unique_ptr<IIRStm> JumpStm::Copy()
{
    return std::move( std::make_unique<JumpStm>( target) );
}

CJumpStm::CJumpStm(RelType relType, IIRExp *exp1, IIRExp *exp2, Label labelTrue, Label labelFalse):
relType(relType), exp1(exp1), exp2(exp2), labelTrue(labelTrue), labelFalse(labelFalse) {}
void CJumpStm::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::string CJumpStm::getType() const {
    switch (relType) {
    case (RelType::EQ): return "EQ";
    case (RelType::NE): return "NE";
    case (RelType::LT): return "LT";
    }
}
std::unique_ptr<IIRStm> CJumpStm::Copy()
{
    return std::move( std::make_unique<CJumpStm>( relType, exp1->Copy().release(), exp2->Copy().release(), labelTrue, labelFalse) );
}

SeqStm::SeqStm(IIRStm *stm1, IIRStm *stm2): leftStm(stm1), rightStm(stm2) {}
void SeqStm::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::unique_ptr<IIRStm> SeqStm::Copy()
{
    return std::move( std::make_unique<SeqStm>( leftStm->Copy().release(), rightStm->Copy().release()) );
}

LabelStm::LabelStm(Label label): label(label) {}
void LabelStm::Accept(IIRVisitor *v) const {
    v->visit(this);
}
std::unique_ptr<IIRStm> LabelStm::Copy()
{
    return std::move( std::make_unique<LabelStm>( label) );
}

void IRStmList::Accept(IIRVisitor *v) const {
    v->visit( this );
}
