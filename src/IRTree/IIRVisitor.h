#pragma once

#include "IIRStm.h"
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

class IRStmList;

class IIRVisitor {
  public:
    virtual void visit(const ConstExp *n) = 0;
    virtual void visit(const NameExp *n) = 0;
    virtual void visit(const TempExp *n) = 0;
    virtual void visit(const BinaryExp *n) = 0;
    virtual void visit(const MemoryExp *n) = 0;
    virtual void visit(const CallExp *n) = 0;
    virtual void visit(const ESeqExp *n) = 0;

    virtual void visit(const MoveStm *n) = 0;
    virtual void visit(const ExpStm *n) = 0;
    virtual void visit(const JumpStm *n) = 0;
    virtual void visit(const CJumpStm *n) = 0;
    virtual void visit(const SeqStm *n) = 0;
    virtual void visit(const LabelStm *n) = 0;

    virtual void visit( const IRStmList* n ) {}
    virtual void visit( const IRExpList* n ) {}
};
