#include <assert.h>
#include "BasicBlockMarker.h"

BasicBlockMarker::BasicBlockMarker() {
}

BasicBlockMarker::~BasicBlockMarker() {
}

void BasicBlockMarker::visit(const ConstExp *n) {
    assert(false);
}

void BasicBlockMarker::visit(const NameExp *n) {
    assert(false);
}

void BasicBlockMarker::visit(const TempExp *n) {
    assert(false);
}

void BasicBlockMarker::visit(const BinaryExp *n) {
    assert(false);
}

void BasicBlockMarker::visit(const MemoryExp *n) {
    assert(false);
}

void BasicBlockMarker::visit(const CallExp *n) {
    assert(false);
}

void BasicBlockMarker::visit(const ESeqExp *n) {
    assert(false);
}

void BasicBlockMarker::visit(const MoveStm *n) {
}

void BasicBlockMarker::visit(const ExpStm *n) {
}

void BasicBlockMarker::visit(const JumpStm *n) {
    blockJumpLabel = std::make_shared<std::string>(n->target.label);
}

void BasicBlockMarker::visit(const CJumpStm *n) {
    blockJumpLabel = std::make_shared<std::string>(n->labelFalse.label);
}

void BasicBlockMarker::visit(const SeqStm *n) {
    assert(false);
}

void BasicBlockMarker::visit(const LabelStm *n) {
    blockLabel = n->label.label;
}

void BasicBlockMarker::visit(const IRExpList *n) {
    assert(false);
}

void BasicBlockMarker::visit(const IRStmList *n) {
    n->statements.front()->Accept(this);
    n->statements.back()->Accept(this);
}

std::string BasicBlockMarker::BlockLabel() const {
    return blockLabel;
}

std::shared_ptr<std::string> BasicBlockMarker::BlockJumpLabel() const {
    return blockJumpLabel;
}