//
// Created by daniil on 31.03.19.
//

#include "ESEQCanonizer.h"
#include <cassert>
#include <iostream>
#include <IRTree/IIRExp.h>

IIRStm* ESEQCanonizer::CanonicalTree()
{
  return CanonicalStmTree().release();
}

std::unique_ptr<IIRStm> ESEQCanonizer::CanonicalStmTree()
{
  return std::move( prevStm );
}

std::unique_ptr<IIRExp> ESEQCanonizer::CanonicalExpTree()
{
  return std::move( prevExp );
}

void ESEQCanonizer::updateLastExp( IIRExp* newLastExp )
{
  prevExp = std::move( std::unique_ptr<IIRExp>( newLastExp ) );
}

void ESEQCanonizer::updateLastExp( std::unique_ptr<IIRExp> newLastExp )
{
  prevExp = std::move( newLastExp );
}

void ESEQCanonizer::updateLastExpList( std::unique_ptr<IRExpList> newLastExpList )
{
  prevExpList = std::move( newLastExpList );
}

void ESEQCanonizer::updateLastStm( std::unique_ptr<IIRStm> newLastStm )
{
  prevStm = std::move( newLastStm );
}

std::unique_ptr<IIRExp> ESEQCanonizer::canonizeExpSubtree( std::unique_ptr<IIRExp> exp ) const
{
  ESEQCanonizer visitor;
  exp->Accept( &visitor );
  return visitor.CanonicalExpTree();
}

std::unique_ptr<IIRStm> ESEQCanonizer::canonizeStmSubtree( std::unique_ptr<IIRStm> stm ) const
{
  ESEQCanonizer visitor;
  stm->Accept( &visitor );
  return visitor.CanonicalStmTree();
}

bool ESEQCanonizer::areCommuting( IIRStm* stm, IIRExp* exp )
{
  assert(stm != nullptr && exp != nullptr);
  auto expStm = dynamic_cast<const ExpStm*>(stm);
  bool isStmEmpty = expStm != nullptr &&
      dynamic_cast<const ConstExp*>( expStm->exp.get() ) != nullptr;
  return isStmEmpty ||
      dynamic_cast<const ConstExp*>( exp ) != nullptr ||
      dynamic_cast<const NameExp*>( exp ) != nullptr;
}

const ESeqExp* ESEQCanonizer::castToESeqExp( IIRExp* exp )
{
  return dynamic_cast<const ESeqExp*>( exp );
}

void ESEQCanonizer::visit( const ConstExp* n )
{
  updateLastExp( std::make_unique<ConstExp>( n->value ) );
}

void ESEQCanonizer::visit( const NameExp* n )
{
  updateLastExp( std::make_unique<NameExp>( n->label ) );
}

void ESEQCanonizer::visit( const TempExp* n )
{
  static int numEntries = 0;
  std::cout << numEntries << std::endl;
  updateLastExp( std::move( std::make_unique<TempExp>( n->value ) ) );
  numEntries++;
}

void ESEQCanonizer::visit( const BinaryExp* n )
{
  n->leftExp->Accept( this );
  std::unique_ptr<IIRExp> canonLeft = std::move( prevExp );
  n->rightExp->Accept( this );
  std::unique_ptr<IIRExp> canonRight = std::move( prevExp );

  const ESeqExp* eseqLeft = castToESeqExp( canonLeft.get() );
  const ESeqExp* eseqRight = castToESeqExp( canonRight.get() );

  std::unique_ptr<IIRExp> resultExp;
  if( eseqLeft ) {
    resultExp = std::move( std::make_unique<ESeqExp>(
        eseqLeft->stm->Copy().release(),
        new BinaryExp(
            n->binType,
            eseqLeft->exp->Copy().release(),
            canonRight.release() ) ) );
    if( eseqRight ) {
      resultExp = canonizeExpSubtree( std::move( resultExp ) );
    }
  } else if( eseqRight ) {
    if( areCommuting( eseqRight->stm.get(), canonLeft.get() ) ) {
      resultExp = std::move( std::make_unique<ESeqExp>(
          eseqRight->stm->Copy().release(),
          new BinaryExp(
              n->binType,
              canonLeft.release(),
              eseqRight->exp->Copy().release()
          )
      ));
    } else {
      Temp temp("T");
      IIRStm* eseqstm = eseqRight->stm->Copy().release();
      IIRExp* eseqexp = eseqRight->exp->Copy().release();
      resultExp = std::move( std::make_unique<ESeqExp>(
          new MoveStm(
              new TempExp( temp ),
              canonLeft.release() ),
          new ESeqExp(
              eseqstm,
              new BinaryExp(
                  n->binType,
                  new TempExp( temp ),
                  eseqexp )
              )
          )
      );
      resultExp = std::move( canonizeExpSubtree( std::move( resultExp ) ) );
    }
  } else {
    resultExp = std::move( std::make_unique<BinaryExp>(
        n->binType,
        canonLeft.release(),
        canonRight.release() ) );
  }

  updateLastExp( resultExp.release() );
}

void ESEQCanonizer::visit( const MemoryExp* n )
{
  n->exp->Accept( this );
  std::unique_ptr<IIRExp> canonAddr = std::move( prevExp );

  const ESeqExp* eseqAddr = castToESeqExp( canonAddr.get() );
  std::unique_ptr<IIRExp> resultExp = nullptr;
  if( eseqAddr ) {
    resultExp = std::move(std::make_unique<ESeqExp>(
        eseqAddr->stm->Copy().release(),
         new MemoryExp(eseqAddr->exp->Copy().release())
    ));
  } else {
    resultExp = std::move( std::make_unique<MemoryExp>( canonAddr.release() ) );
  }
  updateLastExp( resultExp.release() );
}

void ESEQCanonizer::visit( const CallExp* n )
{
  n->funcExp->Accept( this );
  std::unique_ptr<IIRExp> canonFunc = std::move( prevExp );

  n->args->Accept( this );
  std::vector<std::unique_ptr<IIRStm>> newStms;

  std::unique_ptr<IRExpList> newArgs = std::make_unique<IRExpList>();
  std::unique_ptr<IRExpList> canonArgList = std::move( prevExpList );
  for( auto& canonArg : canonArgList->expressions ) {
    const ESeqExp* eseqArg = castToESeqExp( canonArg.get() );
    if( eseqArg ) {
      newStms.push_back(eseqArg->stm->Copy());
    }

    Temp temp("T");
    newArgs->expressions.emplace_back( new TempExp( temp ) );

    std::unique_ptr<IIRExp> moveSrcExp;
    if( eseqArg ) {
      moveSrcExp = eseqArg->exp->Copy();
    } else {
      moveSrcExp = canonArg->Copy();
    }
    std::unique_ptr<IIRStm> moveStm = std::move( std::make_unique<MoveStm>(
        new TempExp( temp ) ,
        moveSrcExp.release() ) );
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

  updateLastExp( std::move( resultExp ) );

}

void ESEQCanonizer::visit( const ESeqExp* n )
{
  n->stm->Accept( this );
  std::unique_ptr<IIRStm> canonStm = std::move( prevStm );
  n->exp->Accept( this );
  std::unique_ptr<IIRExp> canonExp = std::move( prevExp );

  const ESeqExp* eseqExp = castToESeqExp( canonExp.get() );
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

  updateLastExp( std::move( resultExp ) );

}

void ESEQCanonizer::visit( const ExpStm* n )
{

  n->exp->Accept( this );
  std::unique_ptr<IIRExp> canonExp = std::move( prevExp );

  const ESeqExp* eseqExp = castToESeqExp( canonExp.get() );
  std::unique_ptr<IIRStm> resultStm;
  if( eseqExp ) {
    resultStm = std::move( std::make_unique<SeqStm>(
        eseqExp->stm->Copy().release(),
        new ExpStm(eseqExp->exp->Copy().release()) ) );
  } else {
    resultStm = std::move( std::make_unique<ExpStm>( canonExp.release() ) );
  }

  updateLastStm( std::move( resultStm ) );

}

void ESEQCanonizer::visit( const CJumpStm* n )
{

  n->exp1->Accept( this );
  std::unique_ptr<IIRExp> canonLeft = std::move( prevExp );
  n->exp2->Accept( this );
  std::unique_ptr<IIRExp> canonRight = std::move( prevExp );

  const ESeqExp* eseqLeft = castToESeqExp( canonLeft.get() );
  const ESeqExp* eseqRight = castToESeqExp( canonRight.get() );

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
      resultStm = std::move( canonizeStmSubtree( std::move( resultStm ) ) );
    }
    resultStm = std::move( std::make_unique<SeqStm>(
        eseqLeft->stm->Copy().release(),
        resultStm.release())
    );
  } else if( eseqRight ) {
    if( areCommuting( eseqRight->stm.get(), canonLeft.get() ) ) {
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
      Temp temp("T");
      resultStm = std::move( std::make_unique<SeqStm>(
          new MoveStm(
              new TempExp( temp ),
              canonLeft.release() ),
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

  updateLastStm( std::move( resultStm ) );

}

void ESEQCanonizer::visit( const JumpStm* n )
{
  updateLastStm(std::move( std::make_unique<JumpStm>(n->target)));
}

void ESEQCanonizer::visit( const LabelStm* n )
{
  updateLastStm(std::move( std::make_unique<LabelStm>(n->label)));
}

void ESEQCanonizer::visit( const MoveStm* n )
{
  n->to->Accept( this );
  std::unique_ptr<IIRExp> canonDest = std::move( prevExp );
  n->from->Accept( this );
  std::unique_ptr<IIRExp> canonSrc = std::move( prevExp );

  const ESeqExp* eseqDest = castToESeqExp( canonDest.get() );
  const ESeqExp* eseqSrc = castToESeqExp( canonSrc.get() );

  std::unique_ptr<IIRStm> resultStm;
  if( eseqDest ) {
    resultStm = std::move( std::make_unique<MoveStm>(
        eseqDest->exp->Copy().release(),
        canonSrc.release() ) );
    if( eseqSrc ) {
      resultStm = std::move( canonizeStmSubtree( std::move( resultStm ) ) );
    }
    resultStm = std::move( std::make_unique<SeqStm>(
        eseqDest->stm->Copy().release(),
        resultStm.release() ) );
  } else if( eseqSrc ) {
    if( areCommuting( eseqSrc->stm.get(), canonDest.get() ) ) {
      resultStm = std::move( std::make_unique<SeqStm>(
          eseqSrc->stm->Copy().release(),
          new MoveStm(
              canonDest.release(),
              eseqSrc->exp->Copy().release()))
      );
    } else {
      Temp temp("T");
      resultStm = std::move( std::make_unique<SeqStm>(
          new SeqStm(
              eseqSrc->stm->Copy().release(),
              new MoveStm(
                  new TempExp( temp ),
                  eseqSrc->exp->Copy().release())
          ),
          new MoveStm(
              canonDest.release(),
              new TempExp( temp ) ) ) );
    }
  } else {
    resultStm = std::move( std::make_unique<MoveStm>(
            canonDest.release(),
            canonSrc.release())
    );
  }

  updateLastStm( std::move( resultStm ) );

}

void ESEQCanonizer::visit( const SeqStm* n )
{
  n->leftStm->Accept( this );
  std::unique_ptr<IIRStm> canonLeft = std::move( prevStm );
  n->rightStm->Accept( this );
  std::unique_ptr<IIRStm> canonRight = std::move( prevStm );

  updateLastStm( std::move( std::make_unique<SeqStm>(
      canonLeft.release(),
      canonRight.release() ) ) );
}

void ESEQCanonizer::visit( const IRExpList* expList )
{
  std::unique_ptr<IRExpList> newExpList( new IRExpList );
  for( auto& expression : expList->expressions) {
    expression->Accept( this );
    newExpList->expressions.emplace_back( prevExp.release() );
  }

  updateLastExpList( std::move( newExpList ) );
}

void ESEQCanonizer::visit( const IRStmList* stmList )
{
  assert( false );
}
