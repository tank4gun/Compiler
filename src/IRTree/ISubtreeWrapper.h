#pragma once

#include "IIRStm.h"
#include "IIRExp.h"

class ISubtreeWrapper {
  public:
    virtual ~ISubtreeWrapper() = default;

    virtual IIRExp *ToExp() const = 0;
    virtual IIRStm *ToStm() const = 0;
    virtual IIRStm *ToConditional(Label t, Label f) const = 0;
};

class ExpConverter : public ISubtreeWrapper {
  public:
    explicit ExpConverter(IIRExp *e) : expr(e) {}

    IIRExp *ToExp() const override {
        return expr;
    }

    IIRStm *ToStm() const override {
        return new ExpStm(expr);
    }

    IIRStm *ToConditional(Label t, Label f) const override {
        return new CJumpStm(RelType::LT, expr, static_cast<IIRExp *>(new ConstExp(0)), t, f);
    }

    IIRExp *expr;
};

class StmtConverter : public ISubtreeWrapper {
  public:
    explicit StmtConverter(IIRStm *s) : stmt(s) {}

    IIRStm *ToStm() const override {
        return stmt;
    }

    IIRStm *stmt;
};

class CondConverter : public ISubtreeWrapper {
  public:
    IIRExp *ToExp() const override = 0;

    IIRStm *ToStm() const override = 0;

    IIRStm *ToConditional(Label t, Label f) const override = 0;
};

class RelCondConverter : public CondConverter {
  public:
    RelCondConverter(RelType type, IIRExp *leftOp, IIRExp *rightOp)
        : type(type), leftOp(leftOp), rightOp(rightOp) {}

    IIRStm *ToConditional(Label labelTrue, Label labelFalse) const override;

  private:
    RelType type;
    IIRExp *leftOp;
    IIRExp *rightOp;
};

class LogicAndCondConverter : public CondConverter {
  public:
    LogicAndCondConverter(ISubtreeWrapper *leftOp_, ISubtreeWrapper *rightOp_)
        : leftOp(leftOp_), rightOp(rightOp_) {}

    IIRStm *ToConditional(Label labelTrue, Label labelFalse) const override;

  private:
    std::unique_ptr<ISubtreeWrapper> leftOp;
    std::unique_ptr<ISubtreeWrapper> rightOp;
};

class LogicNegCondConverter : public CondConverter {
  public:
    explicit LogicNegCondConverter(ISubtreeWrapper *wrapper_) : wrapper(wrapper_) {}

    IIRStm *ToConditional(Label labelTrue, Label labelFalse) const override;
  private:
    std::unique_ptr<ISubtreeWrapper> wrapper;
};