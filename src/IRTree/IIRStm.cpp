#include "IIRStm.h"

#include <CanonicalTree/ICTVisitor.h>

MoveStm::MoveStm(IIRExp *from, IIRExp *to): from(from), to(to) {}
void MoveStm::Accept(IIRVisitor *v) const {
    v->visit(this);
}
ExpStm::ExpStm(IIRExp *exp): exp(exp) {}
void ExpStm::Accept(IIRVisitor *v) const {
    v->visit(this);
}
JumpStm::JumpStm(Label target): target(target) {}
void JumpStm::Accept(IIRVisitor *v) const {
    v->visit(this);
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
SeqStm::SeqStm(IIRStm *stm1, IIRStm *stm2): leftStm(stm1), rightStm(stm2) {}
void SeqStm::Accept(IIRVisitor *v) const {
    v->visit(this);
}
LabelStm::LabelStm(Label label): label(label) {}
void LabelStm::Accept(IIRVisitor *v) const {
    v->visit(this);
}

void IRStmList::Accept(ICTVisitor *v) const {
    v->visit( this );
}
