#include <limits>
#include <assert.h>
#include "SEQCanonizer.h"

SEQCanonizer::SEQCanonizer() :
    stackDepthCounter(1, std::numeric_limits<int>::max() - 1) {
}

IIRStm* SEQCanonizer::CanonicalTree() {
    return prevStm.release();
}

void SEQCanonizer::visit(const ConstExp *n) {
    ++stackDepthCounter.back();
    prevExp = std::make_unique<ConstExp>(n->value);
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const NameExp *n) {
    ++stackDepthCounter.back();
    prevExp = std::make_unique<NameExp>(n->label);
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const TempExp *n) {
    ++stackDepthCounter.back();
    prevExp = std::make_unique<TempExp>(n->value);
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const BinaryExp *n) {
    ++stackDepthCounter.back();
    n->leftExp->Accept(this);
    std::unique_ptr<IIRExp> nLeft = std::move(prevExp);

    n->rightExp->Accept(this);
    std::unique_ptr<IIRExp> nRight = std::move(prevExp);

    prevExp = std::make_unique<BinaryExp>( n->binType, nLeft.release(), nRight.release() );
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const MemoryExp *n) {
    ++stackDepthCounter.back();
    n->exp->Accept(this);
    std::unique_ptr<IIRExp> addressExp = std::move(prevExp);

    prevExp = std::make_unique<MemoryExp>(addressExp.release());
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const CallExp *n) {
    ++stackDepthCounter.back();
    n->funcExp->Accept(this);
    std::unique_ptr<IIRExp> functionExp = std::move(prevExp);

    n->args->Accept(this);
    std::unique_ptr<IRExpList> argumentsList = std::move(prevExpList);

    prevExp = std::make_unique<CallExp>(functionExp.release(), argumentsList.release());
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const ESeqExp *n) {
    assert(false);
}

void SEQCanonizer::visit(const ExpStm *n) {
    ++stackDepthCounter.back();
    n->exp->Accept(this);
    std::unique_ptr<IIRExp> exp = std::move(prevExp);

    std::unique_ptr<IIRStm> result(std::move(std::make_unique<ExpStm>(exp.release())));

    saveCreatedStm(std::move(result));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const CJumpStm *n) {
    ++stackDepthCounter.back();
    n->exp1->Accept(this);
    std::unique_ptr<IIRExp> nLeft = std::move(prevExp);

    n->exp2->Accept(this);
    std::unique_ptr<IIRExp> nRight = std::move(prevExp);

    std::unique_ptr<IIRStm> result(std::move(
        std::make_unique<CJumpStm>(
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
    std::unique_ptr<IIRStm> result(std::move(
        std::make_unique<JumpStm>(n->target)
    ));
    saveCreatedStm(std::move(result));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const LabelStm *n) {
    ++stackDepthCounter.back();
    std::unique_ptr<IIRStm> result(
        std::move(std::make_unique<LabelStm>(n->label))
    );
    saveCreatedStm(std::move(result));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const MoveStm *n) {
    ++stackDepthCounter.back();
    n->to->Accept(this);
    std::unique_ptr<IIRExp> destination = std::move(prevExp);

    n->from->Accept(this);
    std::unique_ptr<IIRExp> source = std::move(prevExp);

    std::unique_ptr<IIRStm> result(std::move(
        std::make_unique<MoveStm>(
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
        stackOfSeqChilds.push_back(std::move(std::make_unique<std::vector<std::unique_ptr<IIRStm>>>(std::vector<
            std::unique_ptr<IIRStm>>())));
    }
    stackDepthCounter.push_back(0);

    n->leftStm->Accept(this);
    n->rightStm->Accept(this);

    stackDepthCounter.pop_back();
    if (stackDepthCounter.back() > 1) {
        IRStmList *statementList = new IRStmList();
        for (auto &it : *stackOfSeqChilds.back()) {
            statementList->statements.emplace_back(std::move(it));
        }
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
        newList->expressions.emplace_back(std::move(prevExp));
    }

    prevExpList = std::move(std::unique_ptr<IRExpList>(newList));
}

void SEQCanonizer::visit(const IRStmList *) {
    assert(false);
}

void SEQCanonizer::saveCreatedStm(std::unique_ptr<IIRStm> result) {
    if (stackDepthCounter.back() == 1) {
        stackOfSeqChilds.back()->push_back(std::move(result));
    } else {
        prevStm = std::move(result);
    }
}