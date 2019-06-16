//
// Created by daniil on 31.03.19.
//

#include "ESEQCanonizer.h"
#include <cassert>
#include <iostream>
#include <IRTree/IIRExp.h>

IIRStm* ESEQCanonizer::root()
{
    return treeStm().release();
}

std::unique_ptr<IIRStm> ESEQCanonizer::treeStm()
{
    return std::move( curr_stm );
}

std::unique_ptr<IIRExp> ESEQCanonizer::treeExp()
{
    return std::move( curr_exp );
}

std::unique_ptr<IIRExp> ESEQCanonizer::expTreeCanonizer(std::unique_ptr<IIRExp> exp) const
{
    ESEQCanonizer visitor;
    exp->Accept( &visitor );
    return visitor.treeExp();
}

std::unique_ptr<IIRStm> ESEQCanonizer::stmTreeCanonizer(std::unique_ptr<IIRStm> stm) const
{
    ESEQCanonizer visitor;
    stm->Accept( &visitor );
    return visitor.treeStm();
}

bool ESEQCanonizer::canMove(IIRStm *stm, IIRExp *exp)
{
    assert(stm != nullptr && exp != nullptr);

    if (dynamic_cast<ConstExp*>( exp ) != nullptr || dynamic_cast<NameExp*>( exp ) != nullptr) {
        return true;
    }

    ExpStm * expStm = dynamic_cast<ExpStm*>(stm);

    return expStm != nullptr && dynamic_cast<ConstExp*>( expStm->exp.get() ) != nullptr;
}

void ESEQCanonizer::visit( const ConstExp* n )
{
    curr_exp = std::make_unique<ConstExp>( n->value ) ;
}

void ESEQCanonizer::visit( const NameExp* n )
{
    curr_exp = std::make_unique<NameExp>( n->label );
}

void ESEQCanonizer::visit( const TempExp* n )
{
    curr_exp = std::make_unique<TempExp>( n->value );
}

void ESEQCanonizer::visit( const BinaryExp* n )
{
    n->leftExp->Accept( this );
    std::unique_ptr<IIRExp> canonLeft = std::move( curr_exp );
    n->rightExp->Accept( this );
    std::unique_ptr<IIRExp> canonRight = std::move( curr_exp );

    ESeqExp* eseqLeft = dynamic_cast<ESeqExp*>( canonLeft.get() );
    ESeqExp* eseqRight = dynamic_cast<ESeqExp*>( canonRight.get() );

    std::unique_ptr<IIRExp> resultExp;
    if( eseqLeft ) {
        resultExp = std::move( std::make_unique<ESeqExp>(
            eseqLeft->stm->Copy().release(),
            new BinaryExp(
                n->binType,
                eseqLeft->exp->Copy().release(),
                canonRight.release() ) ) );
        if( eseqRight ) {
            resultExp = expTreeCanonizer(std::move(resultExp));
        }
    } else if( eseqRight ) {
        if(canMove(eseqRight->stm.get(), canonLeft.get()) ) {
            resultExp = std::move( std::make_unique<ESeqExp>(
                eseqRight->stm->Copy().release(),
                new BinaryExp(
                    n->binType,
                    canonLeft.release(),
                    eseqRight->exp->Copy().release()
                )
            ));
        } else {
//            counter++;
//            Temp temp( tempLabel + std::to_string( counter ) );
            Temp temp;
            IIRStm* eseqstm = eseqRight->stm->Copy().release();
            IIRExp* eseqexp = eseqRight->exp->Copy().release();
            resultExp = std::move( std::make_unique<ESeqExp>(
                new MoveStm(
                    canonLeft.release(),
                    new TempExp( temp ) ),
                new ESeqExp(
                    eseqstm,
                    new BinaryExp(
                        n->binType,
                        new TempExp( temp ),
                        eseqexp )
                )
                                   )
            );
            resultExp = std::move(expTreeCanonizer(std::move(resultExp)) );
        }
    } else {
        resultExp = std::move( std::make_unique<BinaryExp>(
            n->binType,
            canonLeft.release(),
            canonRight.release() ) );
    }
    curr_exp = std::move( resultExp );
}

void ESEQCanonizer::visit( const MemoryExp* n )
{
    n->exp->Accept( this );
    std::unique_ptr<IIRExp> canonAddr = std::move( curr_exp );

    ESeqExp* eseqAddr = dynamic_cast<ESeqExp*>( canonAddr.get() );
    std::unique_ptr<IIRExp> resultExp = nullptr;
    if( eseqAddr ) {
        resultExp = std::move(std::make_unique<ESeqExp>(
            eseqAddr->stm->Copy().release(),
            new MemoryExp(eseqAddr->exp->Copy().release())
        ));
    } else {
        resultExp = std::move( std::make_unique<MemoryExp>( canonAddr.release() ) );
    }

    curr_exp = std::move( resultExp );
}

void ESEQCanonizer::visit( const CallExp* n )
{
    n->funcExp->Accept( this );
    std::unique_ptr<IIRExp> canonFunc = std::move( curr_exp );

    n->args->Accept( this );
    std::vector<std::unique_ptr<IIRStm>> newStms;

    std::unique_ptr<IRExpList> newArgs = std::make_unique<IRExpList>();
    std::unique_ptr<IRExpList> canonArgList = std::move( curr_expList );
    for( auto& canonArg : canonArgList->expressions ) {
        ESeqExp* eseqArg = dynamic_cast<ESeqExp*>( canonArg.get() );
        if( eseqArg ) {
            newStms.push_back(eseqArg->stm->Copy());
        }

//        counter++;
//        Temp temp( tempLabel + std::to_string( counter ) );
        Temp temp;
        newArgs->expressions.emplace_back( new TempExp( temp ) );

        std::unique_ptr<IIRExp> moveSrcExp;
        if( eseqArg ) {
            moveSrcExp = eseqArg->exp->Copy();
        } else {
            moveSrcExp = canonArg->Copy();
        }
        std::unique_ptr<IIRStm> moveStm = std::move( std::make_unique<MoveStm>(
            moveSrcExp.release(),
            new TempExp( temp )) );
        newStms.push_back( std::move( moveStm ) );
    }

    std::unique_ptr<IIRExp> resultExp;
    if( !newStms.empty() ) {
        std::unique_ptr<IIRStm> suffStm = std::move( newStms.back() );
        newStms.pop_back();
        for( int i = newStms.size() - 1; i >= 0 ; i-- ) {
            suffStm = std::move( std::make_unique<SeqStm>(
                newStms[i].release() ,
                suffStm.release()));
        }

        resultExp = std::move( std::make_unique<ESeqExp>(
            suffStm.release(),
            new CallExp(
                canonFunc.release(),
                newArgs.release() ) ) ) ;
    } else {
        resultExp = std::move( std::make_unique<CallExp>(
            canonFunc.release(),
            canonArgList.release() ) );
    }

    curr_exp = std::move( resultExp );

}

void ESEQCanonizer::visit( const ESeqExp* n )
{
    n->stm->Accept( this );
    std::unique_ptr<IIRStm> canonStm = std::move( curr_stm );
    n->exp->Accept( this );
    std::unique_ptr<IIRExp> canonExp = std::move( curr_exp );

    ESeqExp* eseqExp = dynamic_cast<ESeqExp*>( canonExp.get() );
    std::unique_ptr<IIRExp> resultExp;
    if( eseqExp ) {
        resultExp = std::move( std::make_unique<ESeqExp>(
            new SeqStm(
                canonStm.release(),
                eseqExp->stm->Copy().release() ),
            eseqExp->exp->Copy().release() ) );
    } else {
        resultExp = std::move( std::make_unique<ESeqExp>(
            canonStm.release(),
            canonExp.release() ) );
    }

    curr_exp = std::move( resultExp );

}

void ESEQCanonizer::visit( const ExpStm* n )
{
    n->exp->Accept( this );
    std::unique_ptr<IIRExp> canonExp = std::move( curr_exp );

    ESeqExp* eseqExp = dynamic_cast<ESeqExp*>( canonExp.get() );
    std::unique_ptr<IIRStm> resultStm;
    if( eseqExp ) {
        resultStm = std::move( std::make_unique<SeqStm>(
            eseqExp->stm->Copy().release(),
            new ExpStm(eseqExp->exp->Copy().release()) ) );
    } else {
        resultStm = std::move( std::make_unique<ExpStm>( canonExp.release() ) );
    }

    curr_stm = std::move( resultStm );
}

void ESEQCanonizer::visit( const CJumpStm* n )
{
    n->exp1->Accept( this );
    std::unique_ptr<IIRExp> canonLeft = std::move( curr_exp );
    n->exp2->Accept( this );
    std::unique_ptr<IIRExp> canonRight = std::move( curr_exp );

    ESeqExp* eseqLeft = dynamic_cast<ESeqExp*>(canonLeft.get() );
    ESeqExp* eseqRight = dynamic_cast<ESeqExp*>(canonRight.get() );

    std::unique_ptr<IIRStm> resultStm;

    if( eseqLeft ) {
        resultStm = std::move( std::make_unique<CJumpStm>(
            n->relType,
            eseqLeft->exp->Copy().release(),
            canonRight.release(),
            n->labelTrue,
            n->labelFalse)
        );
        if( eseqRight ) {
            resultStm = std::move(stmTreeCanonizer(std::move(resultStm)) );
        }
        resultStm = std::move( std::make_unique<SeqStm>(
            eseqLeft->stm->Copy().release(),
            resultStm.release())
        );
    } else if( eseqRight ) {
        if(canMove(eseqRight->stm.get(), canonLeft.get()) ) {
            resultStm = std::move( std::make_unique<SeqStm>(
                eseqRight->stm->Copy().release(),
                new CJumpStm(
                    n->relType,
                    canonLeft.release(),
                    eseqRight->exp->Copy().release(),
                    n->labelTrue,
                    n->labelFalse
                )
            ));
        } else {
//            counter++;p
//            Temp temp( tempLabel + std::to_string( counter ) );
            Temp temp;
            resultStm = std::move( std::make_unique<SeqStm>(
                new MoveStm( //!!!
                    canonLeft.release(),
                    new TempExp( temp ) ),
                new SeqStm(
                    eseqRight->stm->Copy().release(),
                    new CJumpStm(
                        n->relType,
                        new TempExp( temp ),
                        eseqRight->exp->Copy().release(),
                        n->labelTrue,
                        n->labelFalse)
                )
                                   )
            );
        }
    } else {
        resultStm = std::move( std::make_unique<CJumpStm>(
            n->relType,
            canonLeft.release(),
            canonRight.release(),
            n->labelTrue,
            n->labelFalse
        ));
    }

    curr_stm = std::move( resultStm );

}

void ESEQCanonizer::visit( const JumpStm* n )
{
    curr_stm = std::make_unique<JumpStm>(n->target);
}

void ESEQCanonizer::visit( const LabelStm* n )
{
    curr_stm = std::make_unique<LabelStm>(n->label);
}

void ESEQCanonizer::visit( const MoveStm* n )
{
    n->to->Accept( this );
    std::unique_ptr<IIRExp> canonDest = std::move( curr_exp );
    n->from->Accept( this );
    std::unique_ptr<IIRExp> canonSrc = std::move( curr_exp );

    ESeqExp* eseqDest = dynamic_cast<ESeqExp*>( canonDest.get() );
    ESeqExp* eseqSrc = dynamic_cast<ESeqExp*>( canonSrc.get() );

    std::unique_ptr<IIRStm> resultStm;
    if( eseqDest ) {
        resultStm = std::move( std::make_unique<MoveStm>(
            canonSrc.release(),
            eseqDest->exp->Copy().release()
            ) );
        if( eseqSrc ) {
            resultStm = std::move(stmTreeCanonizer(std::move(resultStm)) );
        }
        resultStm = std::move( std::make_unique<SeqStm>(
            eseqDest->stm->Copy().release(),
            resultStm.release() ) );
    } else if( eseqSrc ) {
        if(canMove(eseqSrc->stm.get(), canonDest.get()) ) {
            resultStm = std::move( std::make_unique<SeqStm>(
                eseqSrc->stm->Copy().release(),
                new MoveStm(
                    eseqSrc->exp->Copy().release(),
                    canonDest.release()))
            );
        } else {
            Temp temp;
            resultStm = std::move( std::make_unique<SeqStm>(
                new SeqStm(
                    eseqSrc->stm->Copy().release(),
                    new MoveStm(
                        eseqSrc->exp->Copy().release(),
                        new TempExp( temp ))
                ),
                new MoveStm(
                    new TempExp( temp ),
                    canonDest.release()) ) );
        }
    } else {
        resultStm = std::move( std::make_unique<MoveStm>(
            canonSrc.release(),
            canonDest.release())
        );
    }

    curr_stm = std::move( resultStm );

}

void ESEQCanonizer::visit( const SeqStm* n )
{
    n->leftStm->Accept( this );
    std::unique_ptr<IIRStm> canonLeft = std::move( curr_stm );
    n->rightStm->Accept( this );
    std::unique_ptr<IIRStm> canonRight = std::move( curr_stm );

    curr_stm = std::make_unique<SeqStm>(canonLeft.release(), canonRight.release());
}

void ESEQCanonizer::visit( const IRExpList* expList )
{
    std::unique_ptr<IRExpList> newExpList( new IRExpList );
    for( auto& expression : expList->expressions) {
        expression->Accept( this );
        newExpList->expressions.emplace_back( curr_exp.release() );
    }

    curr_expList = std::move( newExpList );
}

void ESEQCanonizer::visit( const IRStmList* stmList )
{
}
