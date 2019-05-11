#include "BasicBlockBuilder.h"

BasicBlockBuilder::BasicBlockBuilder() :
    cur(VISITED::INIT),
    prev(VISITED::INIT),
    blocks(std::move(std::make_unique<std::vector<std::unique_ptr<const IRStmList>>>())) {
}

BasicBlockBuilder::~BasicBlockBuilder() {
}

std::string BasicBlockBuilder::EndName() {
    return "epilogue";
}

std::unique_ptr<std::vector<std::unique_ptr<const IRStmList>>> BasicBlockBuilder::Blocks() {
    return std::move(blocks);
}

std::unique_ptr<IRStmList> BasicBlockBuilder::makeBlock() const {
    std::unique_ptr<IRStmList> block(new IRStmList());
    if (cur != VISITED::LABEL) {
        block->Add(new LabelStm(Label()));
    }
    return std::move(block);
}

void BasicBlockBuilder::storeBlock(std::unique_ptr<IRStmList> block, bool endBlock) {
    if (prev != VISITED::JUMP) {
        Label jumpLabel = endBlock ? Label(EndName()) : *prevLabel;
        block->Add(new JumpStm(jumpLabel));
    }
    prevLabel = nullptr;
    auto x = block.release();
    blocks->push_back(std::move(std::unique_ptr<const IRStmList>(x)));
}

void BasicBlockBuilder::visit(const ConstExp *n) {
}

void BasicBlockBuilder::visit(const NameExp *n) {
}

void BasicBlockBuilder::visit(const TempExp *n) {
}

void BasicBlockBuilder::visit(const BinaryExp *n) {
}

void BasicBlockBuilder::visit(const MemoryExp *n) {
}

void BasicBlockBuilder::visit(const CallExp *n) {
}

void BasicBlockBuilder::visit(const ESeqExp *n) {
    assert(false);
}

void BasicBlockBuilder::visit(const MoveStm *n) {
    cur = VISITED::OTHER;
}

void BasicBlockBuilder::visit(const ExpStm *n) {
    cur = VISITED::OTHER;
}

void BasicBlockBuilder::visit(const JumpStm *n) {
    cur = VISITED::JUMP;
}

void BasicBlockBuilder::visit(const CJumpStm *n) {
    cur = VISITED::JUMP;
}

void BasicBlockBuilder::visit(const SeqStm *n) {
    assert(false);
}

void BasicBlockBuilder::visit(const LabelStm *n) {
    cur = VISITED::LABEL;
    prevLabel = std::make_shared<Label>(n->label);
}

void BasicBlockBuilder::visit(const IRExpList *n) {
}

bool BasicBlockBuilder::newBlockStarts() const {
    return cur == VISITED::LABEL || prev == VISITED::JUMP;
}

bool BasicBlockBuilder::blockFormed() const {
    return curBlock != nullptr;
}

void BasicBlockBuilder::visit(const IRStmList *n) {
    prev = VISITED::JUMP;
    const auto &statements = n->statements;
    for (const auto &stm: statements) {
        stm->Accept(this);
        if (newBlockStarts()) {
            if (blockFormed()) {
                storeBlock(std::move(curBlock), false);
            }
            curBlock = std::move(makeBlock());
        }
        curBlock->Add(std::move(stm->GetCopy()));
        prev = cur;
    }
    if (blockFormed()) {
        storeBlock(std::move(curBlock), true);
    }

    assert(curBlock == nullptr);
}