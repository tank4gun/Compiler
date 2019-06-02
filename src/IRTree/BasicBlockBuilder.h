#pragma once
#include <string>
#include "IIRVisitor.h"
#include "IIRStm.h"

class BasicBlockBuilder : public IIRVisitor {
    enum class VISITED {
        LABEL, JUMP, OTHER, INIT
    };

  public:
    explicit BasicBlockBuilder();
    BasicBlockBuilder(const BasicBlockBuilder &other) = delete;
    const BasicBlockBuilder &operator=(const BasicBlockBuilder &) = delete;
    ~BasicBlockBuilder();

    static std::string EndName();
    std::unique_ptr<std::vector<std::unique_ptr<IRStmList>>> Blocks();

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
    std::unique_ptr<IRStmList> makeBlock() const;
    void storeBlock(std::unique_ptr<IRStmList> block, bool endBlock);
    bool newBlockStarts() const;
    bool blockFormed() const;

    // Указатели на stm-ы из IRStmList
    VISITED cur;
    VISITED prev;
    std::shared_ptr<Label> prevLabel;
    std::unique_ptr<std::vector<std::unique_ptr<IRStmList>>> blocks;
    // Создаваемый блок
    std::unique_ptr<IRStmList> curBlock;
};
