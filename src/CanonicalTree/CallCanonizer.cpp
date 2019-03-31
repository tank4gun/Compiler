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
    n->exp->Accept( this );
    std::unique_ptr<IIRExp> tmp = std::move( curr_exp );
    curr_exp = std::make_unique<MemoryExp>( tmp.release() );
}

void CallCanonizer::visit(const CallExp *n) {
    n->funcExp->Accept( this );
    std::unique_ptr<IIRExp> func = std::move( curr_exp );

    n->args->Accept( this );
    std::unique_ptr<IRExpList> args = std::move( curr_expList );

    static int counter = 0;
    static const std::string tempLabel = "temp";
    counter++;
    Temp temp( tempLabel + std::to_string( counter ) );
    curr_exp = std::make_unique<ESeqExp>( new MoveStm( new TempExp( temp ), new CallExp( func.release(), args.release() ) ), new TempExp( temp ) );
}

void CallCanonizer::visit(const ESeqExp *n) {
    n->stm->Accept( this );
    n->exp->Accept( this );

    curr_exp = std::make_unique<ESeqExp>( curr_stm.release(), curr_exp.release() );
}

void CallCanonizer::visit(const MoveStm *n) {
    n->from->Accept( this );
    std::unique_ptr<IIRExp> from = std::move( curr_exp );

    n->to->Accept( this );
    std::unique_ptr<IIRExp> to = std::move( curr_exp );

    curr_stm = std::make_unique<MoveStm>( from.release(), to.release() );
}

void CallCanonizer::visit(const ExpStm *n) {
    n->exp->Accept( this );
    std::unique_ptr<IIRExp> tmp = std::move( curr_exp );
    curr_stm = std::make_unique<ExpStm>( tmp.release() );
}

void CallCanonizer::visit(const JumpStm *n) {
    curr_stm = std::make_unique<JumpStm>( n->target );
}

void CallCanonizer::visit(const CJumpStm *n) {
    n->exp1->Accept( this );
    std::unique_ptr<IIRExp> exp1 = std::move( curr_exp );

    n->exp2->Accept( this );
    std::unique_ptr<IIRExp> exp2 = std::move( curr_exp );

    curr_stm = std::make_unique<CJumpStm>( n->relType, exp1.release(), exp2.release(), n->labelTrue, n->labelFalse );
}

void CallCanonizer::visit(const SeqStm *n) {
    n->leftStm->Accept( this );
    std::unique_ptr<IIRStm> left = std::move( curr_stm );

    n->rightStm->Accept( this );
    std::unique_ptr<IIRStm> right = std::move( curr_stm );

    curr_stm = std::make_unique<SeqStm>( left.release(), right.release() );
}

void CallCanonizer::visit(const LabelStm *n) {
    curr_stm = std::make_unique<LabelStm>( n->label );
}

void CallCanonizer::visit(const IRExpList *n) {
    auto tmpList = new IRExpList();
    for( const auto& arg : n->expressions ) {
        arg->Accept( this );
        tmpList->expressions.emplace_back( std::move( curr_exp ) );
    }

    curr_expList = std::unique_ptr<IRExpList>( tmpList );
}

void CallCanonizer::visit(const IRStmList *n) {
    auto tmpList = new IRStmList();
    for( const auto& arg : n->statements ) {
        arg->Accept( this );
        tmpList->statements.emplace_back( std::move( curr_stm ) );
    }

    curr_stmList = std::unique_ptr<IRStmList>( tmpList );

}
