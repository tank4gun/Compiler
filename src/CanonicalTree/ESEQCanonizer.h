//
// Created by daniil on 31.03.19.
//

#pragma once
#include <memory>
#include "ICTVisitor.h"

class ConstExp;
class NameExp;
class TempExp;
class BinaryExp;
class MemoryExp;
class CallExp;
class ESeqExp;

class MoveStm;
class ExpStm;
class JumpStm;
class CJumpStm;
class SeqStm;
class LabelStm;

class IIRExp;
class IIRStm;
class IRExpList;
class IRStmList;


class ESEQCanonizer : public ICTVisitor
{

  public:
    ESEQCanonizer() = default;

    IIRStm* root();
    std::unique_ptr<IIRStm> treeStm();
    std::unique_ptr<IIRExp> treeExp();

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

    void visit( const IRExpList* expList ) override;
    void visit( const IRStmList* stmList ) override;

  private:
    std::unique_ptr<IIRExp> expTreeCanonizer(std::unique_ptr<IIRExp> exp) const;
    std::unique_ptr<IIRStm> stmTreeCanonizer(std::unique_ptr<IIRStm> stm) const;

    bool canMove(IIRStm *stm, IIRExp *exp);
    std::unique_ptr<IIRExp> curr_exp;
    std::unique_ptr<IIRStm> curr_stm;
    std::unique_ptr<IRExpList> curr_expList;
};
