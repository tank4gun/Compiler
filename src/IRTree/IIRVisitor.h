#pragma once

class IIRVisitor {
  virtual void visit(const CConstExp* n)  = 0;
  virtual void visit(const CNameExp* n)  = 0;
  virtual void visit(const CTempExp* n)  = 0;
  virtual void visit(const CBinaryExp* n)  = 0;
  virtual void visit(const CMemoryExp* n)  = 0;
  virtual void visit(const CCallExp* n)  = 0;

  virtual void visit(const CESeqExp* n)  = 0;

  virtual void visit(const CMoveStm* n)  = 0;
  virtual void visit(const CExpStm* n)  = 0;
  virtual void visit(const CJumpStm* n)  = 0;
  virtual void visit(const CCJumpStm* n)  = 0;
  virtual void visit(const CSeqStm* n)  = 0;
  virtual void visit(const CLabelStm* n)  = 0;
};
