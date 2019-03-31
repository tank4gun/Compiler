#pragma once

#include <CanonicalTree/ICTVisitor.h>
#include <ST-AST/Expressions.h>
#include <IRTree/IIRStm.h>

class CallCanonizer : public ICTVisitor {
  public:    
    std::unique_ptr<const IIRStm> CanonicalTree();

    void visit( const ConstExp* n ) override;
    void visit( const NameExp* n ) override;
    void visit( const TempExp* n ) override;
    void visit( const BinaryExp* n ) override;
    void visit( const MemoryExp* n ) override;
    void visit( const CallExp* n ) override;

    void visit( const ESeqExp* n ) override;

    void visit( const MoveStm* n ) override;
    void visit( const ExpStm* n ) override;
    void visit( const JumpStm* n ) override;
    void visit( const CJumpStm* n ) override;
    void visit( const SeqStm* n ) override;
    void visit( const LabelStm* n ) override;

    void visit( const IRExpList* n ) override;
    void visit( const IRStmList* n ) override;

  private:

    std::unique_ptr<const IRExpList> prevExpList;
    std::unique_ptr<const IIRExp> prevExp;
    std::unique_ptr<const IIRStm> prevStm;
    std::unique_ptr<const IRStmList> prevStmList;
};


