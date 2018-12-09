#pragma once
#include <memory>
#include <map>

class IIRVisitor;
class IIRExp;
class Label;

class IIRStm {
  public:
    IIRStm() = default;
    virtual ~IIRStm() = default;
    virtual void Accept(IIRVisitor* v) const = 0;
};

class MoveStm: public IIRStm {
  public:
    MoveStm(IIRExp* from, IIRExp* to);
    void Accept(IIRVisitor* v) const override;

    std::unique_ptr<IIRExp> from;
    std::unique_ptr<IIRExp> to;
};

class ExpStm: public IIRStm {
  public:
    explicit ExpStm(IIRExp* exp);
    void Accept(IIRVisitor* v) const override;

    std::unique_ptr<IIRExp> exp;
};

class JumpStm: public IIRStm {
  public:
    explicit JumpStm(Label target);
    void Accept(IIRVisitor* v) const override;

    Label target;
};

enum RelType {EQ, NE, LT};

class CJumpStm: public IIRStm {
  public:

    CJumpStm(RelType relType, IIRExp* exp1, IIRExp* exp2, Label labelTrue, Label labelFalse);
    void Accept(IIRVisitor* v) const override;

    const std::string& GetTypeStr() const;

    const static std::map<RelType, const std::string> TypeToStr;
    RelType relType;
    std::unique_ptr<IIRExp> exp1;
    std::unique_ptr<IIRExp> exp2;
    Label labelTrue;
    Label labeFalse;
};

class SeqStm : public IIRStm {
  public:
    SeqStm(IIRStm* stm1, IIRStm* stm2);
    void Accept(IIRVisitor* v) const override;

    std::unique_ptr<IIRStm> leftStm;
    std::unique_ptr<IIRStm> rightStm;
};

class LabelStm : public IIRStm {
  public:

    explicit LabelStm(Label label);
    void Accept(IIRVisitor* v) const override;

    Label label;
};
