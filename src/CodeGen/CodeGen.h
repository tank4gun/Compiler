#pragma once
#include <list>
#include <IRTree/Translator.h>
#include "Instruction.h"

class CodeGen {
  public:
    CodeGen() = delete;

    explicit CodeGen(const CodeFragment *_fragment) :
        fragment(_fragment), instructList(nullptr), last(nullptr) {
    }

    std::list<const Instruction *> GenerateCode();
  private:
    const CodeFragment *fragment;
    InstructionList *instructList;
    InstructionList *last;

    void emit(Instruction *instruct);

    void munchStm(const SeqStm *stm);
    void munchStm(const MoveStm *stm);
    void munchStm(const LabelStm *stm);
    void munchStm(const ExpStm *stm);
    void munchStm(const JumpStm *stm);
    void munchStm(const CJumpStm *stm);
    void munchStm(const IRStmList *stm);
    void munchStm(const IIRStm *stm);

    std::shared_ptr<const Temp> munchExp(const MemoryExp *expr);
    std::shared_ptr<const Temp> munchExpJump(const BinaryExp *binOp);
    std::shared_ptr<const Temp> munchExp(const BinaryExp *binOp);
    std::shared_ptr<const Temp> munchExp(const ConstExp *constantExpr);
    std::shared_ptr<const Temp> munchExp(const TempExp *expr);
    std::shared_ptr<const Temp> munchExp(const NameExp *expr);
    std::shared_ptr<const Temp> munchExp(const CallExp *expr);
    std::shared_ptr<const Temp> munchExp(const IIRExp *expr);

    std::list<std::shared_ptr<const Temp>> munchArgs(const IRExpList *args);

    std::list<const Instruction *> getList(InstructionList *list);
};