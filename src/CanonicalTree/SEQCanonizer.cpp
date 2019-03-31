#include "SEQCanonizer.h"

SEQCanonizer::SEQCanonizer() :
    stackDepthCounter(1, std::numeric_limits<int>::max() - 1) {
}

std::unique_ptr<const IIRStm> SEQCanonizer::CanonicalTree() {
    return std::move(prevStm);
}

//void SEQCanonizer::updateLastExp(const IIRExp *newLastExp) {
//    prevExp = std::move(std::unique_ptr<const IIRExp>(newLastExp));
//}
//
//void SEQCanonizer::updateLastExp(std::unique_ptr<const IIRExp> newLastExp) {
//    prevExp = std::move(newLastExp);
//}
//
//void SEQCanonizer::updateLastExpList(const IRExpList *newLastExpList) {
//    prevExpList = std::move(std::unique_ptr<const IRExpList>(newLastExpList));
//}
//
//void SEQCanonizer::updateLastExpList(std::unique_ptr<IRExpList> newLastExpList) {
//    prevExpList = std::move(newLastExpList);
//}
//
//void SEQCanonizer::updateLastStm(const IIRStm *newLastStm) {
//    prevStm = std::move(std::unique_ptr< IIRStm>(newLastStm));
//}
//
//void SEQCanonizer::updateLastStm(std::unique_ptr<const IIRStm> newLastStm) {
//    prevStm = std::move(newLastStm);
//}
//
//void SEQCanonizer::updateLastStmList(const IRStmList *newLastStmList) {
//    prevStmList = std::move(std::unique_ptr<const IRStmList>(newLastStmList));
//}
//
//void SEQCanonizer::updateLastStmList(std::unique_ptr<const IRStmList> newLastStmList) {
//    prevStmList = std::move(newLastStmList);
//}

void SEQCanonizer::visit(const ConstExp *n) {
    ++stackDepthCounter.back();
//    updateLastExp(std::make_unique<const ConstExp>(n->value));
    prevExp = std::make_unique<ConstExp>(n->value);
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const NameExp *n) {
    ++stackDepthCounter.back();
//    updateLastExp(std::make_unique<const NameExp>(n->label));
    prevExp = std::make_unique<NameExp>(n->label);
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const TempExp *n) {
    ++stackDepthCounter.back();
//    updateLastExp(std::make_unique<const TempExp>(n->value));
    prevExp = std::make_unique<TempExp>(n->value);
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const BinaryExp *n) {
    ++stackDepthCounter.back();
    n->leftExp.get()->Accept(this);
    std::unique_ptr<IIRExp> nLeft = std::move(prevExp);

    n->rightExp.get()->Accept(this);
    std::unique_ptr<IIRExp> nRight = std::move(prevExp);

//    updateLastExp(
//        std::make_unique<const BinaryExp>(
//            n->binType,
//            std::move(nLeft),
//            std::move(nRight)
//        )
//    );

//    prevExp = std::move(std::make_unique<BinaryExp>(
//        n->binType,
//        std::move(nLeft),
//        std::move(nRight)
//    ));
    prevExp = std::make_unique<BinaryExp>( n->binType, nLeft.release(), nLeft.release() );
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const MemoryExp *n) {
    ++stackDepthCounter.back();
    n->exp.get()->Accept(this);
    std::unique_ptr<IIRExp> addressExp = std::move(prevExp);

//    updateLastExp(
//        std::make_unique<const MemoryExp>(addressExp.release())
//    );
    prevExp = std::make_unique<MemoryExp>(addressExp.release());
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const CallExp *n) {
    ++stackDepthCounter.back();
    n->funcExp.get()->Accept(this);
    std::unique_ptr<IIRExp> functionExp = std::move(prevExp);

    n->args.get()->Accept(this);
    std::unique_ptr<IRExpList> argumentsList = std::move(prevExpList);

//    updateLastExp(
//        std::make_unique<const CallExp>(
//            std::move(functionExp),
//            std::move(argumentsList)
//        ));

//    prevExp = std::make_unique<CallExp>(
//        std::move(functionExp),
//        std::move(argumentsList)
//    );
    prevExp = std::make_unique<CallExp>(functionExp.release(), argumentsList.release());
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const ESeqExp *n) {
    assert(false);
}

void SEQCanonizer::visit(const ExpStm *n) {
    ++stackDepthCounter.back();
    n->exp.get()->Accept(this);
    std::unique_ptr<IIRExp> exp = std::move(prevExp);

//    std::unique_ptr<IIRStm> result(std::move(std::make_unique<ExpStm>(std::move(exp))));

    std::unique_ptr<IIRStm> result(std::move(std::make_unique<ExpStm>(exp.release())));

    saveCreatedStm(std::move(result));
    --stackDepthCounter.back();
}

void SEQCanonizer::visit(const CJumpStm *n) {
    ++stackDepthCounter.back();
    n->exp1.get()->Accept(this);
    std::unique_ptr<IIRExp> nLeft = std::move(prevExp);

    n->exp2.get()->Accept(this);
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
    n->to.get()->Accept(this);
    std::unique_ptr<IIRExp> destination = std::move(prevExp);

    n->from.get()->Accept(this);
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

    n->leftStm.get()->Accept(this);
    n->rightStm.get()->Accept(this);

    stackDepthCounter.pop_back();
    if (stackDepthCounter.back() > 1) {
        IRStmList *statementList = new IRStmList();
        for (auto &it : *stackOfSeqChilds.back()) {
            statementList->statements.emplace_back(std::move(it));
        }
//        updateLastStm(statementList);
        prevStmList = std::unique_ptr<IRStmList>(statementList);
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
        newList->expressions.emplace_back(std::move(prevExp));
    }

//    updateLastExpList(std::move(newList));
    prevExpList = std::move(std::unique_ptr<IRExpList>(newList));
}

void SEQCanonizer::visit(const IRStmList *list) {
    assert(false);
}

void SEQCanonizer::saveCreatedStm(std::unique_ptr<IIRStm> result) {
    if (stackDepthCounter.back() == 1) {
        stackOfSeqChilds.back()->push_back(std::move(result));
    } else {
//        updateLastStm(std::move(result));
        prevStm = std::move(result);
    }
}