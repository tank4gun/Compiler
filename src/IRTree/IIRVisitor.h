#pragma once

class MoveStm;
class ExpStm;
class JumpStm;
class CJumpStm;
class SeqStm;
class LabelStm;

class IIRVisitor {
  virtual void visit(const CConstExp* n)  = 0;
  virtual void visit(const CNameExp* n)  = 0;
  virtual void visit(const CTempExp* n)  = 0;
  virtual void visit(const CBinaryExp* n)  = 0;
  virtual void visit(const CMemoryExp* n)  = 0;
  virtual void visit(const CCallExp* n)  = 0;

  virtual void visit(const CESeqExp* n)  = 0;

  virtual void visit(const MoveStm* n)  = 0;
  virtual void visit(const ExpStm* n)  = 0;
  virtual void visit(const JumpStm* n)  = 0;
  virtual void visit(const CJumpStm* n)  = 0;
  virtual void visit(const SeqStm* n)  = 0;
  virtual void visit(const LabelStm* n)  = 0;
};
