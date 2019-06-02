#include "CodeGen.h"
#include "../IRTree/IIRStm.h"

std::list<const Instruction *> CodeGen::getList(std::shared_ptr<InstructionList> list) {
    std::list<const Instruction *> newList;
    for (; list != nullptr; list = list->tail) {
        newList.push_back(list->head.get());
    }
    return newList;
}

std::list<const Instruction *> CodeGen::GenerateCode() {
    for (auto &block: *fragment->traces) {
        for (auto &stm: block->GetStatements()) {
            munchStm(stm.get());
        }
    }

    std::shared_ptr<InstructionList> list = instructList;
//    instructList = last = nullptr;
    return getList(list);
}

void CodeGen::munchStm(const IRStmList *stm) {
    for (auto &root: stm->statements) {
        munchStm(root.get());
    }
}

void CodeGen::emit(Instruction *instruct) {
    if (last != nullptr) {
        last = last->tail = std::make_shared<InstructionList>(instruct, nullptr);
    } else {
        last = instructList = std::make_shared<InstructionList>(instruct, nullptr);
    }
}

void CodeGen::munchStm(const SeqStm *stm) {
    // В обрабатываемом дереве отсутствуют Seq.
    assert(false);
}

void CodeGen::munchStm(const MoveStm *stm) {
    if (dynamic_cast<const MemoryExp*>(stm->to) != nullptr) {
        auto destMem = dynamic_cast<const MemoryExp*>(stm->to);

        if (dynamic_cast<const BinaryExp*>(destMem->GetMem()) != nullptr) {
            auto binOp = dynamic_cast<const BinaryExp*>(destMem->GetMem());
            if (binOp->isPlus() || binOp->isMinus()) {
                if ((dynamic_cast<const ConstExp*>(binOp->GetLeft()) != nullptr) || (dynamic_cast<const ConstExp*>(binOp->GetRight()) != nullptr)) {
                    const IIRExp *binOpExpr;
                    const ConstExp *constantExpr;
                    if ((dynamic_cast<const ConstExp*>(binOp->GetLeft()) != nullptr)) {
                        binOpExpr = binOp->GetRight();
                        constantExpr = dynamic_cast<const ConstExp*>(binOp->GetLeft());
                    } else {
                        binOpExpr = binOp->GetLeft();
                        constantExpr = dynamic_cast<const ConstExp*>(binOp->GetRight());
                    }
                    // munchExp( binOpExpr ) был внесен в dest
                    emit(new Oper(std::string("mov ['d0") +
                                       ((binOp->isPlus()) ? "+" : "-") +
                                       std::to_string(constantExpr->GetValue()) +
                                       std::string("], 's0\n"),

                                   std::make_shared<const TempList>(munchExp(binOpExpr), nullptr),

                                   std::make_shared<const TempList>(munchExp(stm->from), nullptr)));
                } else {
                    emit(new Oper(std::string("mov ['d0], 's0\n"),
                                   std::make_shared<const TempList>(munchExp(binOp), nullptr),
                                   std::make_shared<const TempList>(munchExp(stm->from),
                                                                    nullptr)));
                }
            }
        } else if (dynamic_cast<const ConstExp*>(destMem->GetMem()) != nullptr) {
            // MOVE( mem( CONST(i) ), e2 )
            const ConstExp *constantExpr = dynamic_cast<const ConstExp*>(destMem->GetMem());
            emit(new Oper(std::string("mov ['d0+") +
                               std::to_string(constantExpr->GetValue()) +
                               std::string("], 's0\n"),
                           nullptr,
                           std::make_shared<const TempList>(munchExp(stm->from),
                                                            nullptr)));
        } else if (dynamic_cast<const Temp*>(destMem->GetMem()) != nullptr) {
            // MOVE( mem( TEMP ), e2 )
            emit(new Oper(std::string("mov ['d0], 's0\n"),
                           std::make_shared<const TempList>(munchExp(destMem->GetMem()),
                                                            nullptr),
                           std::make_shared<const TempList>(munchExp(stm->from),
                                                            nullptr)));
        } else if (dynamic_cast<const MemoryExp*>(destMem->GetMem()) != nullptr) {
            if (dynamic_cast<const MemoryExp*>(stm->from) != nullptr) {
                emit(new Oper(std::string("mov ['d0], ['s0]\n"),
                               nullptr,
                               std::make_shared<const TempList>(
                                   munchExp(stm->from),
                                   std::make_shared<const TempList>(munchExp(stm->from),
                                                                    nullptr))));
            } else {
                emit(new Oper(std::string("mov ['d0], 's0\n"),
                               nullptr,
                               std::make_shared<const TempList>(
                                   munchExp(stm->from),
                                   std::make_shared<const TempList>(munchExp(stm->from),
                                                                    nullptr))));
            }
        }
    } else if (dynamic_cast<const TempExp*>(stm->to) != nullptr) {
        const TempExp *temp = dynamic_cast<const TempExp*>(stm->to);
        emit(new Oper("mov 'd0, 's0\n",
                       std::make_shared<const TempList>(std::make_shared<const Temp>(temp->GetTemp()),
                                                        nullptr),
                       std::make_shared<const TempList>(munchExp(stm->from), nullptr)));
    } else {
        // У Move dst либо Temp, либо Mem.
        assert(false);
    }
}

void CodeGen::munchStm(const LabelStm *stm) {
    emit(new InstrLabel(stm->GetLabel().String() + std::string(":\n"),
                    std::make_shared<const Label>(stm->GetLabel())));
}

void CodeGen::munchStm(const ExpStm *stm) {
    munchExp(stm->GetExp());
}

void CodeGen::munchStm(const JumpStm *stm) {
    emit(new Oper("jmp 'j0\n",
                   nullptr,
                   nullptr,
                   std::make_shared<LabelList>(std::make_shared<const Label>(stm->GetLabel()),
                                                nullptr)));
}

void CodeGen::munchStm(const CJumpStm *stm) {
    auto leftTemp = munchExp(stm->GetLeft());
    auto rightTemp = munchExp(stm->GetRight());
    emit(new Oper("cmp 's0, 's1\n", nullptr,
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
    emit(new Oper(oper + " 'l0\n", nullptr, nullptr,
                   std::make_shared<const LabelList>(std::make_shared<const Label>(stm->GetTrueLabel()),
                                                           nullptr)));
}

void CodeGen::munchStm(const IIRStm *stm) {
    if (dynamic_cast<const SeqStm*>(stm) != nullptr) {
        munchStm(dynamic_cast<const SeqStm*>(stm));
    } else if (dynamic_cast<const MoveStm*>(stm) != nullptr) {
        munchStm(dynamic_cast<const MoveStm*>(stm));
    } else if (dynamic_cast<const LabelStm*>(stm) != nullptr) {
        munchStm(dynamic_cast<const LabelStm*>(stm));
    } else if (dynamic_cast<const ExpStm*>(stm) != nullptr) {
        munchStm(dynamic_cast<const ExpStm*>(stm));
    } else if (dynamic_cast<const JumpStm*>(stm) != nullptr) {
        munchStm(dynamic_cast<const JumpStm*>(stm));
    } else if (dynamic_cast<const CJumpStm*>(stm) != nullptr) {
        munchStm(dynamic_cast<const CJumpStm*>(stm));
    } else if (dynamic_cast<const IRStmList*>(stm) != nullptr) {
        munchStm(dynamic_cast<const IRStmList*>(stm));
    }
}

std::shared_ptr<const Temp> CodeGen::munchExp(const MemoryExp *expr) {
    auto temp = std::make_shared<const Temp>();
    emit(new Move("mov 'd0, ['s0]\n", temp, munchExp(expr->GetMem())));
    return temp;
}

std::shared_ptr<const Temp> CodeGen::munchExpJump(const BinaryExp *binOp) {
    auto temp = std::make_shared<Temp>();
    emit(new Oper("mov 'd0, 0\n", std::make_shared<const TempList>(temp, nullptr), nullptr));

    auto left = std::make_shared<Temp>();
    auto right = std::make_shared<Temp>();
    emit(new Move("mov 'd0, 's0\n", left, munchExp(binOp->GetLeft())));
    emit(new Move("mov 'd0, 's0\n", right, munchExp(binOp->GetRight())));

    auto source =
        std::make_shared<const TempList>(left, std::make_shared<const TempList>(right, nullptr));

    emit(new Oper("cmp 's0, s1\n", nullptr, source));

    auto label = std::make_shared<const Label>();

    emit(new Oper("jnl 'l0\n", nullptr, nullptr, std::make_shared<const LabelList>(label, nullptr)));
    emit(new Oper("mov 'd0, 1\n", std::make_shared<const TempList>(temp, nullptr), nullptr));
    emit(new InstrLabel(label->String() + ":\n", label));

    return temp;
}

std::shared_ptr<const Temp> CodeGen::munchExp(const BinaryExp *binOp) {
    // TODO: подобрать сравнение
    //if( binOp->GetType() == CBinaryExp::TYPE::LESS ) {
    //    munchExpJump( binOp );
    //}

    if ((dynamic_cast<const ConstExp*>(binOp->GetLeft()) != nullptr) && (dynamic_cast<const ConstExp*>(binOp->GetRight()) != nullptr)) {
        // const-const
        int leftVal = (dynamic_cast<const ConstExp*>(binOp->GetLeft()))->GetValue();
        int rightVal = (dynamic_cast<const ConstExp*>(binOp->GetRight()))->GetValue();
        auto temp = std::make_shared<const Temp>();
        // ����� � frame->eax ����� ���������
        emit(new Move("mov 'd0, " + std::to_string(leftVal) + "\n", fragment->eax, nullptr));
        if (binOp->isMult()) {
            emit(new Move("mov 'd0, 0\n", fragment->edx, nullptr));
        }
        if (binOp->isPlus()) {
            emit(new Oper("add 'd0, " + std::to_string(rightVal) + "\n",
                           std::make_shared<const TempList>(fragment->eax, nullptr),
                           nullptr));
        } else if (binOp->isMinus()) {
            emit(new Oper("sub 'd0, " + std::to_string(rightVal) + "\n",
                           std::make_shared<const TempList>(fragment->eax, nullptr),
                           nullptr));
        } else if (binOp->isMult()) {
            emit(new Oper("mul " + std::to_string(rightVal) + "\n",
                           std::make_shared<const TempList>(fragment->eax,
                                                            std::make_shared<const TempList>(
                                                                fragment->edx,
                                                                nullptr)),
                           nullptr));
        }
        emit(new Move("mov 'd0, 's0\n\n", temp, fragment->eax));
        return temp;
    }
    if (dynamic_cast<const ConstExp*>(binOp->GetLeft()) != nullptr) {
        // const-expr
        int leftVal = (dynamic_cast<const ConstExp*>(binOp->GetLeft()))->GetValue();
        auto temp = std::make_shared<const Temp>();
        auto rightTemp = munchExp(binOp->GetRight());
        // ����� � frame->eax ����� ���������
        emit(new Move("mov 'd0, " + std::to_string(leftVal) + "\n", fragment->eax, nullptr));
        // ���������� ������
        emit(new Move("mov 'd0, 's0\n", temp, rightTemp));
        if (binOp->isMult()) {
            emit(new Move("mov 'd0, 0\n", fragment->edx, nullptr));
        }
        std::shared_ptr<const TempList> usedRegisters;
        if (binOp->isPlus()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
            emit(new Oper("add 'd0, 's0\n", usedRegisters,
                           std::make_shared<const TempList>(temp, nullptr)));
        } else if (binOp->isMinus()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
            emit(new Oper("sub 'd0, 's0\n", usedRegisters,
                           std::make_shared<const TempList>(temp, nullptr)));
        } else if (binOp->isMult()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax,
                                                             std::make_shared<const TempList>(fragment
                                                                                                  ->edx,
                                                                                              nullptr));
            emit(new Oper("mul 's0\n", usedRegisters,
                           std::make_shared<const TempList>(temp, nullptr)));
        }
        auto temp2 = std::make_shared<const Temp>();
        emit(new Move("mov 'd0, 's0\n\n", temp2, usedRegisters->Head()));
        return temp2;
    }
    if (dynamic_cast<const ConstExp*>(binOp->GetRight()) != nullptr) {
        // expr-const
        int rightVal = (dynamic_cast<const ConstExp*>(binOp->GetRight()))->GetValue();
        auto leftTemp = munchExp(binOp->GetLeft());
        auto temp = std::make_shared<const Temp>();
        // ���������� �����
        emit(new Move("mov 'd0, 's0\n", fragment->eax, leftTemp));
        if (binOp->isMult()) {
            emit(new Move("mov 'd0, 0\n", fragment->edx, nullptr));
        }
        std::shared_ptr<const TempList> usedRegisters;
        if (binOp->isPlus()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
            emit(new Oper("add 'd0, " + std::to_string(rightVal) + "\n", usedRegisters,
                           nullptr));
        } else if (binOp->isMinus()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
            emit(new Oper("sub 'd0, " + std::to_string(rightVal) + "\n", usedRegisters,
                           nullptr));
        } else if (binOp->isMult()) {
            usedRegisters = std::make_shared<const TempList>(fragment->eax,
                                                             std::make_shared<const TempList>(fragment
                                                                                                  ->edx,
                                                                                              nullptr));
            emit(new Oper("mul " + std::to_string(rightVal) + "\n", usedRegisters,
                           nullptr));
        }
        emit(new Move("mov 'd0, 's0\n\n", temp, usedRegisters->Head()));
        return temp;
    }
    // expr-expr
    auto temp1 = std::make_shared<const Temp>();
    auto temp2 = std::make_shared<const Temp>();
    auto leftTemp = munchExp(binOp->GetLeft());
    auto rightTemp = munchExp(binOp->GetRight());
    emit(new Move("mov 'd0, 's0\n", fragment->eax, leftTemp));
    emit(new Move("mov 'd0, 's0\n", temp2, rightTemp));
    if (binOp->isMult()) {
        emit(new Move("mov 'd0, 0\n", fragment->edx, nullptr));
    }
    std::shared_ptr<const TempList> usedRegisters;
    if (binOp->isPlus()) {
        usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
        emit(new Oper("add 'd0, 's0\n", usedRegisters,
                       std::make_shared<const TempList>(temp2, nullptr)));
    } else if (binOp->isMinus()) {
        usedRegisters = std::make_shared<const TempList>(fragment->eax, nullptr);
        emit(new Oper("sub 'd0, 's0\n", usedRegisters,
                       std::make_shared<const TempList>(temp2, nullptr)));
    } else if (binOp->isMult()) {
        usedRegisters = std::make_shared<const TempList>(fragment->eax,
                                                         std::make_shared<const TempList>(fragment->edx,
                                                                                          nullptr));
        emit(new Oper("mul 's0\n", usedRegisters,
                       std::make_shared<const TempList>(temp2, nullptr)));
    }
    emit(new Move("mov 'd0, 's0\n\n", temp1, usedRegisters->Head()));
    return temp1;
}

std::shared_ptr<const Temp> CodeGen::munchExp(const ConstExp *constantExpr) {
    std::shared_ptr<const Temp> temp(new Temp);

    emit(new Oper(std::string("mov 'd0, ") +
                       std::to_string(constantExpr->GetValue()) +
                       std::string("\n"),
                   std::make_shared<const TempList>(temp, nullptr), nullptr));

    return temp;
}

std::shared_ptr<const Temp> CodeGen::munchExp(const TempExp *expr) {
    return std::make_shared<const Temp>(expr->GetTemp());
}

std::shared_ptr<const Temp> CodeGen::munchExp(const NameExp *expr) {
    return std::make_shared<const Temp>();
}

std::shared_ptr<const Temp> CodeGen::munchExp(const CallExp *expr) {
    auto temps = munchArgs(expr->GetArgs());
    std::string functionName = (dynamic_cast<const NameExp*>(expr->GetFuncExp()))->GetLabel().String();
    emit(new Oper("call 'l0\n",
                   std::make_shared<const TempList>(fragment->eax,
                                                    std::make_shared<const TempList>(fragment->edx,
                                                                                     nullptr)),
                   nullptr,
                   std::make_shared<const LabelList>(std::make_shared<const Label>(functionName,
                                                                                               false,
                                                                                               false),
                                                           nullptr)));
    return fragment->eax;
}

std::shared_ptr<const Temp> CodeGen::munchExp(const IIRExp *expr) {
    if (dynamic_cast<const MemoryExp*>(expr) != nullptr) {
        return munchExp(dynamic_cast<const MemoryExp*>(expr));
    }
    if (dynamic_cast<const BinaryExp*>(expr) != nullptr) {
        return munchExp(dynamic_cast<const BinaryExp*>(expr));
    }
    if (dynamic_cast<const ConstExp*>(expr) != nullptr) {
        return munchExp(dynamic_cast<const ConstExp*>(expr));
    }
    if (dynamic_cast<const TempExp*>(expr) != nullptr) {
        return munchExp(dynamic_cast<const TempExp*>(expr));
    }
    if (dynamic_cast<const NameExp*>(expr) != nullptr) {
        return munchExp(dynamic_cast<const NameExp*>(expr));
    }
    if (dynamic_cast<const CallExp*>(expr) != nullptr) {
        return munchExp(dynamic_cast<const CallExp*>(expr));
    }
}

std::list<std::shared_ptr<const Temp>> CodeGen::munchArgs(const IRExpList *args) {
    std::list<std::shared_ptr<const Temp>> temps;

    for (auto &arg: args->GetExpressions()) {
        temps.push_back(munchExp(arg.get()));
        emit(new Oper("push 's0\n", nullptr, std::make_shared<const TempList>(temps.back(), nullptr)));
    }
    return temps;
}