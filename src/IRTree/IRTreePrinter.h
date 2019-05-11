#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include "IIRExp.h"
#include <IRTree/IIRVisitor.h>

class IRTreePrinter : public IIRVisitor {
  private:
    FILE *f;
    int nodeNumber;

  public:
    explicit IRTreePrinter(const std::string &path);
    ~IRTreePrinter();

    void visit(const ConstExp *n) override;
    void visit(const NameExp *n) override;
    void visit(const TempExp *n) override;
    void visit(const BinaryExp *n) override;
    void visit(const MemoryExp *n) override;
    void visit(const CallExp *n) override;
    void visit(const ESeqExp *n) override;

    void visit(const MoveStm *n) override;
    void visit(const ExpStm *n) override;
    void visit(const JumpStm *n) override;
    void visit(const CJumpStm *n) override;
    void visit(const SeqStm *n) override;
    void visit(const LabelStm *n) override;

    void visit(const IRStmList *n) override;
};