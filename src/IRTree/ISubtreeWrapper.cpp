#include "ISubtreeWrapper.h"


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
