#pragma once

#include <iosfwd>
#include <memory>
#include <map>
#include <vector>
#include "IIRStm.h"
#include "Label.h"
#include "ST-AST/Expressions.h"

class IIRVisitor;
class IIRStm;

class IIRExp {
  public:
    IIRExp() = default;
    virtual ~IIRExp() = default;

    virtual void Accept(IIRVisitor *v) const = 0;
};

class IRExpList {
  public:
    IRExpList() = default;

    explicit IRExpList(IIRExp* expression) {
        expressions.emplace_back(expression);
    }

    std::vector<std::unique_ptr<IIRExp>> expressions;
};

class ConstExp : public IIRExp {
  public:
    explicit ConstExp(int value);
    void Accept(IIRVisitor *v) const override;

    int value;
};

class NameExp : public IIRExp {
  public:
    explicit NameExp(Label label);
    void Accept(IIRVisitor *v) const override;

    Label label;
};

class TempExp : public IIRExp {
  public:
    explicit TempExp(Temp value);
    void Accept(IIRVisitor *v) const override;

    Temp value;
};

class BinaryExp : public IIRExp {
  public:
    BinaryExp(BinaryOps binaryType, IIRExp *left, IIRExp *right);
    void Accept(IIRVisitor *v) const override;
    std::string getType() const;

    BinaryOps binType;
    std::unique_ptr<IIRExp> leftExp;
    std::unique_ptr<IIRExp> rightExp;
};

class MemoryExp : public IIRExp {
  public:
    explicit MemoryExp(IIRExp *exp);
    void Accept(IIRVisitor *v) const override;

    std::unique_ptr<IIRExp> exp;
};

class CallExp : public IIRExp {
  public:
    CallExp(IIRExp *funcExp, IRExpList *args);
    void Accept(IIRVisitor *v) const override;

    std::unique_ptr<IIRExp> funcExp;
    std::unique_ptr<IRExpList> args;
};

class ESeqExp : public IIRExp {
  public:
    ESeqExp(IIRStm *stm, IIRExp *exp);
    void Accept(IIRVisitor *v) const override;

    std::unique_ptr<IIRStm> stm;
    std::unique_ptr<IIRExp> exp;
};