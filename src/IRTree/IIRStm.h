#pragma once
#include "Label.h"
#include <memory>
#include <map>
#include "IIRVisitor.h"
#include "IIRExp.h"

class IIRExp;
class ICTVisitor;

class IIRStm {
  public:
    IIRStm() = default;
//    virtual ~IIRStm() = default;
    virtual std::unique_ptr<IIRStm> Copy() = 0;
    virtual void Accept(IIRVisitor* v) const = 0;
};

class MoveStm: public IIRStm {
  public:
    MoveStm(IIRExp* from, IIRExp* to);
    void Accept(IIRVisitor* v) const override;
    std::unique_ptr<IIRStm> Copy() override;

    std::unique_ptr<IIRExp> from;
    std::unique_ptr<IIRExp> to;
};

class ExpStm: public IIRStm {
  public:
    explicit ExpStm(IIRExp* exp);
    void Accept(IIRVisitor* v) const override;
    std::unique_ptr<IIRStm> Copy() override;

    std::unique_ptr<IIRExp> exp;
};

class JumpStm: public IIRStm {
  public:
    explicit JumpStm(Label target);
    void Accept(IIRVisitor* v) const override;
    std::unique_ptr<IIRStm> Copy() override;

    Label target;
};

enum RelType {EQ, NE, LT};

class CJumpStm: public IIRStm {
  public:

    CJumpStm(RelType relType, IIRExp* exp1, IIRExp* exp2, Label labelTrue, Label labelFalse);
    void Accept(IIRVisitor* v) const override;
    std::unique_ptr<IIRStm> Copy() override;

    std::string getType() const;

    RelType relType;
    std::unique_ptr<IIRExp> exp1;
    std::unique_ptr<IIRExp> exp2;
    Label labelTrue;
    Label labelFalse;
};

class SeqStm : public IIRStm {
  public:
    SeqStm(IIRStm* stm1, IIRStm* stm2);
    void Accept(IIRVisitor* v) const override;
    std::unique_ptr<IIRStm> Copy() override;

    std::unique_ptr<IIRStm> leftStm;
    std::unique_ptr<IIRStm> rightStm;
};

class LabelStm : public IIRStm {
  public:

    explicit LabelStm(Label label);
    void Accept(IIRVisitor* v) const override;
    std::unique_ptr<IIRStm> Copy() override;

    Label label;
};

class IRStmList: public IIRStm {
  public:
    IRStmList() = default;

    explicit IRStmList( IIRStm* statement )
    {
        statements.emplace_back( std::unique_ptr<IIRStm>( statement ));
    }

    void Accept(IIRVisitor* v) const override;
    std::unique_ptr<IIRStm> Copy() override { return nullptr; }

    std::vector<std::unique_ptr<IIRStm>> statements;

};
