#include "CodeGen.h"

std::list<const Instruction *> CCodeGeneration::getList(CBaseInstructionList *list) {
    std::list<const Instruction *> newList;
    for (; list != nullptr; list = list->tail) {
        newList.push_back(list->head);
    }
    return newList;
}

std::list<const Instruction *> CCodeGeneration::GenerateCode() {
    for (auto &block: *fragment->traces) {
        for (auto &stm: block->GetStatements()) {
            munchStm(stm.get());
        }
    }

    CBaseInstructionList *list = instructList;
    instructList = last = nullptr;
    return getList(list);
}

void CCodeGeneration::munchStm(const IRStmList *stm) {
    for (auto &root: stm->statements) {
        munchStm(root.get());
    }
}

void CCodeGeneration::emit(Instruction *instruct) {
    if (last != nullptr) {
        last = last->tail = new CBaseInstructionList(instruct, nullptr);
    } else {
        last = instructList = new CBaseInstructionList(instruct, nullptr);
    }
}

void CCodeGeneration::munchStm(const SeqStm *stm) {
    // В обрабатываемом дереве отсутствуют Seq.
    assert(false);
}

void CCodeGeneration::munchStm(const MoveStm *stm) {
    if (INSTANCEOF(stm->to, MemoryExp)) {
        auto destMem = CAST(stm->to, MemoryExp);

        if (INSTANCEOF(destMem->GetMem(), BinaryExp)) {
            auto binOp = CAST(destMem->GetMem(), BinaryExp);
            if (binOp->isPlus() || binOp->isMinus()) {
                if (INSTANCEOF(binOp->GetLeft(), ConstExp) || INSTANCEOF(binOp->GetRight(), ConstExp)) {
                    const IRT::IExp *binOpExpr;
                    const IRT::CConstExp *constantExpr;
                    if (INSTANCEOF(binOp->GetLeft(), ConstExp)) {
                        binOpExpr = binOp->GetRight();
                        constantExpr = CAST(binOp->GetLeft(), ConstExp);
                    } else {
                        binOpExpr = binOp->GetLeft();
                        constantExpr = CAST(binOp->GetRight(), ConstExp);
                    }
                    // munchExp( binOpExpr ) был внесен в dest
                    emit(new COper(std::string("mov ['d0") +
                                       ((binOp->isPlus()) ? "+" : "-") +
                                       std::to_string(constantExpr->GetValue()) +
                                       std::string("], 's0\n"),

                                   std::make_shared<const TempList>(munchExp(binOpExpr), nullptr),

                                   std::make_shared<const TempList>(munchExp(stm->from), nullptr)));
                } else {
                    emit(new COper(std::string("mov ['d0], 's0\n"),
                                   std::make_shared<const TempList>(munchExp(binOp), nullptr),
                                   std::make_shared<const TempList>(munchExp(stm->from),
                                                                    nullptr)));
                }
            }
        } else if (INSTANCEOF(destMem->GetMem(), ConstExp)) {
            // MOVE( mem( CONST(i) ), e2 )
            const ConstExp *constantExpr = CAST(destMem->GetMem(), ConstExp);
            emit(new COper(std::string("mov ['d0+") +
                               std::to_string(constantExpr->GetValue()) +
                               std::string("], 's0\n"),
                           nullptr,
                           std::make_shared<const TempList>(munchExp(stm->from),
                                                            nullptr)));
        } else if (INSTANCEOF(destMem->GetMem(), Temp)) {
            // MOVE( mem( TEMP ), e2 )
            emit(new COper(std::string("mov ['d0], 's0\n"),
                           std::make_shared<const TempList>(munchExp(destMem->GetMem()),
                                                            nullptr),
                           std::make_shared<const TempList>(munchExp(stm->from),
                                                            nullptr)));
        } else if (INSTANCEOF(destMem->GetMem(), MemoryExp)) {
            if (INSTANCEOF(stm->from, MemoryExp)) {
                emit(new COper(std::string("mov ['d0], ['s0]\n"),
                               nullptr,
                               std::make_shared<const TempList>(
                                   munchExp(stm->from),
                                   std::make_shared<const TempList>(munchExp(stm->from),
                                                                    nullptr))));
            } else {
                emit(new COper(std::string("mov ['d0], 's0\n"),
                               nullptr,
                               std::make_shared<const TempList>(
                                   munchExp(stm->from),
                                   std::make_shared<const TempList>(munchExp(stm->from),
                                                                    nullptr))));
            }
        }
    } else if (INSTANCEOF(stm->to, TempExp)) {
        const TempExp *temp = CAST(stm->to, TempExp);
        emit(new COper("mov 'd0, 's0\n",
                       std::make_shared<const TempList>(std::make_shared<const Temp>(temp->GetTemp()),
                                                        nullptr),
                       std::make_shared<const TempList>(munchExp(stm->from), nullptr)));
    } else {
        // У Move dst либо Temp, либо Mem.
        assert(false);
    }
}

void CCodeGeneration::munchStm(const LabelStm *stm) {
    emit(new CLabel(stm->GetLabel().String() + std::string(":\n"),
                    std::make_shared<const IRT::CLabel>(stm->GetLabel())));
}

void CCodeGeneration::munchStm(const IRT::CExpStm *stm) {
    munchExp(stm->GetExp());
}

void CCodeGeneration::munchStm(const IRT::CJumpStm *stm) {
    emit(new COper("jmp 'j0\n",
                   nullptr,
                   nullptr,
                   std::make_shared<CLabelList>(std::make_shared<const IRT::CLabel>(stm->GetLabel()),
                                                nullptr)));
}

void CCodeGeneration::munchStm(const IRT::CCJumpStm *stm) {
    auto leftTemp = munchExp(stm->GetLeft());
    auto rightTemp = munchExp(stm->GetRight());
    emit(new COper("cmp 's0, 's1\n", nullptr,
                   std::make_shared<const TempList>(leftTemp,
                                                    std::make_shared<const TempList>(rightTemp,
                                                                                     nullptr))));
    std::string oper("jl");
    // TODO:
    //switch( stm->relationType ) {
    //    case CCJumpStm::ERelationType::LT:
    //        oper = "jl";
    //        break;
    //    case CCJumpStm::ERelationType::NE:
    //        oper = "jge";
    //        break;
    //}
    emit(new COper(oper + " 'l0\n", nullptr, nullptr,
                   std::make_shared<const IRT::CLabelList>(std::make_shared<const IRT::CLabel>(stm->GetTrueLabel()),
                                                           nullptr)));
}

void CCodeGeneration::munchStm(const IRT::IStm *stm) {
    if (INSTANCEOF(stm, IRT::CSeqStm)) {
        munchStm(CAST(stm, IRT::CSeqStm));
    } else if (INSTANCEOF(stm, IRT::CMoveStm)) {
        munchStm(CAST(stm, IRT::CMoveStm));
    } else if (INSTANCEOF(stm, LabelStm)) {
        munchStm(CAST(stm, LabelStm));
    } else if (INSTANCEOF(stm, IRT::CExpStm)) {
        munchStm(CAST(stm, IRT::CExpStm));
    } else if (INSTANCEOF(stm, IRT::CJumpStm)) {
        munchStm(CAST(stm, IRT::CJumpStm));
    } else if (INSTANCEOF(stm, IRT::CCJumpStm)) {
        munchStm(CAST(stm, IRT::CCJumpStm));
    } else if (INSTANCEOF(stm, IRT::CStmList)) {
        munchStm(CAST(stm, IRT::CStmList));
    }
}

std::shared_ptr<const Temp> CCodeGeneration::munchExp(const IRT::CMemoryExp *expr) {
    auto temp = std::make_shared<const Temp>();
    emit(new CMove("mov 'd0, ['s0]\n", temp, munchExp(expr->GetMem())));
    return temp;
}

std::shared_ptr<const Temp> CCodeGeneration::munchExpJump(const IRT::CBinaryExp *binOp) {
    auto temp = std::make_shared<Temp>();
    emit(new COper("mov 'd0, 0\n", std::make_shared<const TempList>(temp, nullptr), nullptr));

    auto left = std::make_shared<Temp>();
    auto right = std::make_shared<Temp>();
    emit(new CMove("mov 'd0, 's0\n", left, munchExp(binOp->GetLeft())));
    emit(new CMove("mov 'd0, 's0\n", right, munchExp(binOp->GetRight())));

    auto source =
        std::make_shared<const TempList>(left, std::make_shared<const TempList>(right, nullptr));

    emit(new COper("cmp 's0, s1\n", nullptr, source));

    auto label = std::make_shared<const IRT::CLabel>();

    emit(new COper("jnl 'l0\n", nullptr, nullptr, std::make_shared<const IRT::CLabelList>(label, nullptr)));
    emit(new COper("mov 'd0, 1\n", std::make_shared<const TempList>(temp, nullptr), nullptr));
    emit(new CLabel(label->String() + ":\n", label));

    return temp;
}

std::shared_ptr<const Temp> CCodeGeneration::munchExp(const IRT::CBinaryExp *binOp) {
    // TODO: подобрать сравнение
    //if( binOp->GetType() == CBinaryExp::TYPE::LESS ) {
    //    munchExpJump( binOp );
    //}

    if (INSTANCEOF(binOp->GetLeft(), CConstExp) && INSTANCEOF(binOp->GetRight(), CConstExp)) {
        // const-const
        int leftVal = CAST(binOp->GetLeft(), IRT::CConstExp)->GetValue();
        int rightVal = CAST(binOp->GetRight(), IRT::CConstExp)->GetValue();
        auto temp = std::make_shared<const Temp>();
        // ����� � frame->eax ����� ���������
        emit(new CMove("mov 'd0, " + std::to_string(leftVal) + "\n", fragment->eax, nullptr));
        if (binOp->isMult()) {
            emit(new CMove("mov 'd0, 0\n", fragment->edx, nullptr));
        }
        if (binOp->isPlus()) {
            emit(new COper("add 'd0, " + std::to_string(rightVal) + "\n",
                           std::make_shared<const TempList>(fragment->eax, nullptr),
                           nullptr));
        } else if (binOp->isMinus()) {
            emit(new COper("sub 'd0, " + std::to_string(rightVal) + "\n",
                           std::make_shared<const TempList>(fragment->eax, nullptr),
                           nullptr));
        } else if (binOp->isMult()) {
            emit(new COper("mul " + std::to_string(rightVal) + "\n",
                           std::make_shared<const TempList>(fragment->eax,
                                                            std::make_shared<const TempList>(
                                                                fragment->edx,
                                                                nullptr)),
                           nullptr));
        }
        emit(new CMove("mov 'd0, 's0\n\n", temp, fragment->eax));
        return temp;
    }
    if (INSTANCEOF(binOp->GetLeft(), CConstExp)) {
        // const-expr
        int leftVal = CAST(binOp->GetLeft(), IRT::CConstExp)->GetValue();
        auto temp = std::make_shared<const Temp>();
        auto rightTemp = munchExp(binOp->GetRight());
        // ����� � frame->eax ����� ���������
        emit(new CMove("mov 'd0, " + std::to_string(leftVal) + "\n", fragment->eax, nullptr));
        // ���������� ������
        emit(new CMove("mov 'd0, 's0\n", temp, rightTemp));
        if (binOp->isMult()) {
            emit(new CMove("mov 'd0, 0\n", fragment->edx, nullptr));
        }
        std::shared_ptr<const TempList> usedRegisters;
        if (binOp->isPlus()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
            emit(new COper("add 'd0, 's0\n", usedRegisters,
                           std::make_shared<const TempList>(temp, nullptr)));
        } else if (binOp->isMinus()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
            emit(new COper("sub 'd0, 's0\n", usedRegisters,
                           std::make_shared<const TempList>(temp, nullptr)));
        } else if (binOp->isMult()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax,
                                                             std::make_shared<const TempList>(fragment
                                                                                                  ->edx,
                                                                                              nullptr));
            emit(new COper("mul 's0\n", usedRegisters,
                           std::make_shared<const TempList>(temp, nullptr)));
        }
        auto temp2 = std::make_shared<const Temp>();
        emit(new CMove("mov 'd0, 's0\n\n", temp2, usedRegisters->Head()));
        return temp2;
    }
    if (INSTANCEOF(binOp->GetRight(), CConstExp)) {
        // expr-const
        int rightVal = CAST(binOp->GetRight(), IRT::CConstExp)->GetValue();
        auto leftTemp = munchExp(binOp->GetLeft());
        auto temp = std::make_shared<const Temp>();
        // ���������� �����
        emit(new CMove("mov 'd0, 's0\n", fragment->eax, leftTemp));
        if (binOp->isMult()) {
            emit(new CMove("mov 'd0, 0\n", fragment->edx, nullptr));
        }
        std::shared_ptr<const TempList> usedRegisters;
        if (binOp->isPlus()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
            emit(new COper("add 'd0, " + std::to_string(rightVal) + "\n", usedRegisters,
                           nullptr));
        } else if (binOp->isMinus()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
            emit(new COper("sub 'd0, " + std::to_string(rightVal) + "\n", usedRegisters,
                           nullptr));
        } else if (binOp->isMult()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax,
                                                             std::make_shared<const TempList>(fragment
                                                                                                  ->edx,
                                                                                              nullptr));
            emit(new COper("mul " + std::to_string(rightVal) + "\n", usedRegisters,
                           nullptr));
        }
        emit(new CMove("mov 'd0, 's0\n\n", temp, usedRegisters->Head()));
        return temp;
    }
    // expr-expr
    auto temp1 = std::make_shared<const Temp>();
    auto temp2 = std::make_shared<const Temp>();
    auto leftTemp = munchExp(binOp->GetLeft());
    auto rightTemp = munchExp(binOp->GetRight());
    emit(new CMove("mov 'd0, 's0\n", fragment->eax, leftTemp));
    emit(new CMove("mov 'd0, 's0\n", temp2, rightTemp));
    if (binOp->isMult()) {
        emit(new CMove("mov 'd0, 0\n", fragment->edx, nullptr));
    }
    std::shared_ptr<const TempList> usedRegisters;
    if (binOp->isPlus()) {
        usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
        emit(new COper("add 'd0, 's0\n", usedRegisters,
                       std::make_shared<const TempList>(temp2, nullptr)));
    } else if (binOp->isMinus()) {
        usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
        emit(new COper("sub 'd0, 's0\n", usedRegisters,
                       std::make_shared<const TempList>(temp2, nullptr)));
    } else if (binOp->isMult()) {
        usedRegisters = std::make_shared<const TempList>(fragment->eax,
                                                         std::make_shared<const TempList>(fragment->edx,
                                                                                          nullptr));
        emit(new COper("mul 's0\n", usedRegisters,
                       std::make_shared<const TempList>(temp2, nullptr)));
    }
    emit(new CMove("mov 'd0, 's0\n\n", temp1, usedRegisters->Head()));
    return temp1;
}

std::shared_ptr<const Temp> CCodeGeneration::munchExp(const IRT::CConstExp *constantExpr) {
    std::shared_ptr<const Temp> temp(new Temp);

    emit(new COper(std::string("mov 'd0, ") +
                       std::to_string(constantExpr->GetValue()) +
                       std::string("\n"),
                   std::make_shared<const TempList>(temp, nullptr), nullptr));

    return temp;
}

std::shared_ptr<const Temp> CCodeGeneration::munchExp(const TempExp *expr) {
    return std::make_shared<const Temp>(expr->GetTemp());
}

std::shared_ptr<const Temp> CCodeGeneration::munchExp(const IRT::CNameExp *expr) {
    return std::make_shared<const Temp>();
}

std::shared_ptr<const Temp> CCodeGeneration::munchExp(const IRT::CCallExp *expr) {
    auto temps = munchArgs(expr->GetArgs());
    std::string functionName = CAST(expr->GetFuncExp(), CNameExp)->GetLabel().String();
    emit(new COper("call 'l0\n",
                   std::make_shared<const TempList>(fragment->eax,
                                                    std::make_shared<const TempList>(fragment
                                                                                         ->edx,
                                                                                     nullptr)),
                   nullptr,
                   std::make_shared<const IRT::CLabelList>(std::make_shared<const IRT::CLabel>(functionName,
                                                                                               false,
                                                                                               false),
                                                           nullptr)));
    return fragment->eax;
}

std::shared_ptr<const Temp> CCodeGeneration::munchExp(const IRT::IExp *expr) {
    if (INSTANCEOF(expr, IRT::CMemoryExp)) {
        return munchExp(CAST(expr, CMemoryExp));
    }
    if (INSTANCEOF(expr, IRT::CBinaryExp)) {
        return munchExp(CAST(expr, IRT::CBinaryExp));
    }
    if (INSTANCEOF(expr, IRT::CConstExp)) {
        return munchExp(CAST(expr, CConstExp));
    }
    if (INSTANCEOF(expr, TempExp)) {
        return munchExp(CAST(expr, TempExp));
    }
    if (INSTANCEOF(expr, IRT::CNameExp)) {
        return munchExp(CAST(expr, CNameExp));
    }
    if (INSTANCEOF(expr, IRT::CCallExp)) {
        return munchExp(CAST(expr, CCallExp));
    }
}

std::list<std::shared_ptr<const Temp>> CCodeGeneration::munchArgs(const IRT::CExpList *args) {
    std::list<std::shared_ptr<const Temp>> temps;

    for (auto &arg: args->GetExpressions()) {
        temps.push_back(munchExp(arg.get()));
        emit(new COper("push 's0\n", nullptr, std::make_shared<const TempList>(temps.back(), nullptr)));
    }
    return temps;
}