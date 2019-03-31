#include "SEQCanonizer.h"

SEQCanonizer::SEQCanonizer() :
    stackDepthCounter(1, std::numeric_limits<int>::max() - 1) {
}

std::unique_ptr<const IIRStm> SEQCanonizer::CanonicalTree() {
    return std::move(prevStm);
}

void SEQCanonizer::updateLastExp(const IIRExp *newLastExp) {
    prevExp = std::move(std::unique_ptr<const IIRExp>(newLastExp));
}

void SEQCanonizer::updateLastExp(std::unique_ptr<const IIRExp> newLastExp) {
    prevExp = std::move(newLastExp);
}

void SEQCanonizer::updateLastExpList(const IRExpList *newLastExpList) {
    prevExpList = std::move(std::unique_ptr<const IRExpList>(newLastExpList));
}

void SEQCanonizer::updateLastExpList(std::unique_ptr<IRExpList> newLastExpList) {
    prevExpList = std::move(newLastExpList);
}

void SEQCanonizer::updateLastStm(IIRStm *newLastStm) {
    prevStm = std::move(std::unique_ptr< IIRStm>(newLastStm));
}

void SEQCanonizer::updateLastStm(std::unique_ptr<const IIRStm> newLastStm) {
    prevStm = std::move(newLastStm);
}

void SEQCanonizer::updateLastStmList(const IRStmList *newLastStmList) {
    prevStmList = std::move(std::unique_ptr<const IRStmList>(newLastStmList));
}

void SEQCanonizer::updateLastStmList(std::unique_ptr<const IRStmList> newLastStmList) {
    prevStmList = std::move(newLastStmList);
}

void SEQCanonizer::visit(const ConstExp *n) {
    ++stackDepthCounter.back();
    updateLastExp(std::make_unique<const ConstExp>(n->value));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const NameExp *n) {
    ++stackDepthCounter.back();
    updateLastExp(std::make_unique<const NameExp>(n->label));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const TempExp *n) {
    ++stackDepthCounter.back();
    updateLastExp(std::make_unique<const TempExp>(n->value));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const BinaryExp *n) {
    ++stackDepthCounter.back();
    n->leftExp.get()->Accept(this);
    std::unique_ptr<const IIRExp> nLeft = std::move(prevExp);

    n->rightExp.get()->Accept(this);
    std::unique_ptr<const IIRExp> nRight = std::move(prevExp);

    updateLastExp(
        std::make_unique<const BinaryExp>(
            n->binType,
            std::move(nLeft),
            std::move(nRight)
        )
    );
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const MemoryExp *n) {
    ++stackDepthCounter.back();
    n->exp.get()->Accept(this);
    std::unique_ptr<const IIRExp> addressExp = std::move(prevExp);

    updateLastExp(
        std::make_unique<const MemoryExp>(addressExp.release())
    );
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const CallExp *n) {
    ++stackDepthCounter.back();
    n->funcExp.get()->Accept(this);
    std::unique_ptr<const IIRExp> functionExp = std::move(prevExp);

    n->args.get()->Accept(this);
    std::unique_ptr<const IRExpList> argumentsList = std::move(prevExpList);

    updateLastExp(
        std::make_unique<const CallExp>(
            std::move(functionExp),
            std::move(argumentsList)
        ));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const ESeqExp *n) {
    assert(false);
}

void SEQCanonizer::visit(const ExpStm *n) {
    ++stackDepthCounter.back();
    n->exp.get()->Accept(this);
    std::unique_ptr<const IIRExp> exp = std::move(prevExp);

    std::unique_ptr<const IIRStm> result(std::move(std::make_unique<const ExpStm>(std::move(exp))));
    saveCreatedStm(std::move(result));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const CJumpStm *n) {
    ++stackDepthCounter.back();
    n->exp1.get()->Accept(this);
    std::unique_ptr<const IIRExp> nLeft = std::move(prevExp);

    n->exp2.get()->Accept(this);
    std::unique_ptr<const IIRExp> nRight = std::move(prevExp);

    std::unique_ptr<const IIRStm> result(std::move(
        std::make_unique<const CJumpStm>(
            n->relType,
            nLeft.release(),
            nRight.release(),
            n->labelTrue,
            n->labelFalse
        )
    ));
    saveCreatedStm(std::move(result));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const JumpStm *n) {
    ++stackDepthCounter.back();
    std::unique_ptr<const IIRStm> result(std::move(
        std::make_unique<const JumpStm>(n->target)
    ));
    saveCreatedStm(std::move(result));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const LabelStm *n) {
    ++stackDepthCounter.back();
    std::unique_ptr<const IIRStm> result(
        std::move(std::make_unique<const LabelStm>(n->label))
    );
    saveCreatedStm(std::move(result));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const MoveStm *n) {
    ++stackDepthCounter.back();
    n->to.get()->Accept(this);
    std::unique_ptr<const IIRExp> destination = std::move(prevExp);

    n->from.get()->Accept(this);
    std::unique_ptr<const IIRExp> source = std::move(prevExp);

    std::unique_ptr<const IIRStm> result(std::move(
        std::make_unique<const MoveStm>(
            destination.release(),
            source.release()
        ))
    );
    saveCreatedStm(std::move(result));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const SeqStm *n) {
    ++stackDepthCounter.back();
    if (stackDepthCounter.back() > 1) {
        stackOfSeqChilds.push_back(std::move(std::make_unique<std::vector<std::unique_ptr<const IIRStm>>>(std::vector<
            std::unique_ptr<const IIRStm>>())));
    }
    stackDepthCounter.push_back(0);

    n->leftStm.get()->Accept(this);
    n->rightStm.get()->Accept(this);

    stackDepthCounter.pop_back();
    if (stackDepthCounter.back() > 1) {
        IRStmList *statementList = new IRStmList();
        for (auto &it : *stackOfSeqChilds.back()) {
            statementList->statements.emplace_back(std::move(it));
        }
//        updateLastStm(statementList);
        prevStm = std::unique_ptr<IRStmList>(statementList);
        stackOfSeqChilds.pop_back();
    }
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const IRExpList *list) {
    IRExpList *newList = new IRExpList();
    const auto &arguments = list->expressions;
    for (const auto &arg : arguments) {
        arg->Accept(this);
//        newList->Add(std::move(prevExp));
        newList->expressions.emplace_back(prevExp);
    }

//    updateLastExpList(std::move(newList));
    prevExpList = std::move(std::unique_ptr<IRExpList>(newList));
}

void SEQCanonizer::visit(const IRStmList *list) {
    assert(false);
}

void SEQCanonizer::saveCreatedStm(std::unique_ptr<const IIRStm> result) {
    if (stackDepthCounter.back() == 1) {
        stackOfSeqChilds.back()->push_back(std::move(result));
    } else {
        updateLastStm(std::move(result));
    }
}