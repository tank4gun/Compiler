#pragma once
#include <string>
#include "IIRVisitor.h"
#include "IIRStm.h"

class BasicBlockMarker : public IIRVisitor {
  public:
    explicit BasicBlockMarker();
    BasicBlockMarker(const BasicBlockMarker &other) = delete;
    const BasicBlockMarker &operator=(const BasicBlockMarker &) = delete;
    ~BasicBlockMarker();

    std::string BlockLabel() const;
    std::shared_ptr<std::string> BlockJumpLabel() const;

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

    void visit(const IRExpList *n) override;
    void visit(const IRStmList *n) override;

  private:
    std::string blockLabel;
    std::shared_ptr<std::string> blockJumpLabel;
};