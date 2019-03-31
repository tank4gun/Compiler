#pragma  once
#include <IRTree/IIRExp.h>
#include "ICTVisitor.h"

class SEQCanonizer: ICTVisitor {
  public:
    SEQCanonizer();

    std::unique_ptr<const IIRStm> CanonicalTree();

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

    void visit(const IRExpList* list) override;
    void visit(const IRStmList* list) override;

  private:
    void updateLastExp(const IIRExp *newLastExp);
    void updateLastExp(std::unique_ptr<const IIRExp> newLastExp);

    void updateLastExpList(const IRExpList *newLastExpList);
    void updateLastExpList(std::unique_ptr<IRExpList> newLastExpList);

    void updateLastStm(const IIRStm *newLastStm);
    void updateLastStm(std::unique_ptr<const IIRStm> newLastStm);

    void updateLastStmList(const IRStmList *newLastStmList);
    void updateLastStmList(std::unique_ptr<const IRStmList> newLastStmList);

    void saveCreatedStm(std::unique_ptr<const IIRStm> result);

    std::vector<std::unique_ptr<std::vector<std::unique_ptr<const IIRStm>>>> stackOfSeqChilds;

    std::vector<int> stackDepthCounter;

    std::unique_ptr<const IRExpList> prevExpList;
    std::unique_ptr<const IIRExp> prevExp;
    std::unique_ptr<const IIRStm> prevStm;
    std::unique_ptr<const IRStmList> prevStmList;
};
