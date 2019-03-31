#include <memory>

#include "CallCanonizer.h"

#include <memory>

void CallCanonizer::visit(const ConstExp *n) {
    curr_exp = std::make_unique<ConstExp>( n->value );
}

void CallCanonizer::visit(const NameExp *n) {
    curr_exp = std::make_unique<NameExp>( n->label );
}

void CallCanonizer::visit(const TempExp *n) {
    curr_exp = std::make_unique<TempExp>( n->value );
}

void CallCanonizer::visit(const BinaryExp *n) {
    n->leftExp->Accept( this );
    std::unique_ptr<IIRExp> left = std::move( curr_exp );

    n->rightExp->Accept( this );
    std::unique_ptr<IIRExp> right = std::move( curr_exp );

    curr_exp = std::make_unique<BinaryExp>( n->binType, left.release(), right.release() );

}

void CallCanonizer::visit(const MemoryExp *n) {
    n->exp->Accept( this ); //this might not be enough; check then
}

void CallCanonizer::visit(const CallExp *n) {
    n->funcExp->Accept( this );
    std::unique_ptr<IIRExp> func = std::move( curr_exp );

}

void CallCanonizer::visit(const ESeqExp *n) {

}

void CallCanonizer::visit(const MoveStm *n) {

}

void CallCanonizer::visit(const ExpStm *n) {

}

void CallCanonizer::visit(const JumpStm *n) {

}

void CallCanonizer::visit(const CJumpStm *n) {

}

void CallCanonizer::visit(const SeqStm *n) {

}

void CallCanonizer::visit(const LabelStm *n) {

}

void CallCanonizer::visit(const IRExpList *n) {

}

void CallCanonizer::visit(const IRStmList *n) {

}
