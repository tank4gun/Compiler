#include "ISubtreeWrapper.h"

//const IIRExp *CondConverter::ToExp() const {
//    assert(false);
//    TempExp *tempExp = new TempExp(Temp());
//    Label labelFalse;
//    Label labelTrue;
//    return
//        new ESeqExp(
//            new SeqStm(
//                new MoveStm(tempExp, new ConstExp(1)),
//                new SeqStm(
//                    ToConditional(labelTrue, labelFalse),
//                    new SeqStm(
//                        new LabelStm(labelFalse),
//                        new SeqStm(
//                            new MoveStm(tempExp, new ConstExp(0)),
//                            new LabelStm(labelTrue)
//                        )
//                    )
//                )
//            ),
//            tempExp
//        );
//}

IIRStm *RelCondConverter::ToConditional(const Label labelTrue, const Label labelFalse) const {
    return new CJumpStm(type, leftOp, rightOp, labelTrue, labelFalse);
}

IIRStm *LogicAndCondConverter::ToConditional(const Label labelTrue, const Label labelFalse) const {
    Label labelMiddle;
    return new SeqStm(leftOp->ToConditional(labelMiddle, labelFalse),
                      new SeqStm(new LabelStm(labelMiddle),
                                 rightOp->ToConditional(labelTrue, labelFalse)));
}

IIRStm *LogicNegCondConverter::ToConditional(const Label labelTrue, const Label labelFalse) const {
    return wrapper->ToConditional(labelFalse, labelTrue);
}