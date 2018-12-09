#pragma once

#include <iosfwd>
#include <memory>
#include <map>
#include "IIRStm.h"
#include "Label.h"
#include "List.h"

class IIRVisitor;

class IIRExp {
  public:
    IIRExp() = default;
    virtual ~IIRExp() = default;

    virtual void Accept(IIRVisitor *v) const = 0;
};

class CConstExp : public IIRExp {
  public:
    explicit CConstExp(int value);
    void Accept(IIRVisitor *v) const override;

    int value;
};

class CNameExp : public IIRExp {
  public:
    explicit CNameExp(Label label);
    void Accept(IIRVisitor *v) const override;

    Label label;
};

class CTempExp : public IIRExp {
  public:
    explicit CTempExp(Temp value_);
    void Accept(IIRVisitor *v) const override;
    std::string GetValueLabel();

  private:
    Temp value;
};

class CBinaryExp : public IIRExp {
  public:
    CBinaryExp(EBinaryType binaryType, IIRExp *left, IIRExp *right);
    void Accept(IIRVisitor *v) const override;
    std::string &GetTypeStr();

    static std::map<EBinaryType, std::string> TypeToStr;
    EBinaryType binType;
    std::unique_ptr<IIRExp> leftExp;
    std::unique_ptr<IIRExp> rightExp;
};

class CMemoryExp : public IIRExp {
  public:
    explicit CMemoryExp(IIRExp *exp);
    void Accept(IIRVisitor *v) const override;

    std::unique_ptr<IIRExp> exp;
};

class CCallExp : public IIRExp {
  public:
    CCallExp(IIRExp *funcExp, CExpList *args);
    void Accept(IIRVisitor *v) const override;


    std::unique_ptr<IIRExp> funcExp;
    std::unique_ptr<CExpList> args;
};

class CESeqExp : public IIRExp {
  public:
    CESeqExp(IIRStm *stm, IIRExp *exp);
    void Accept(IIRVisitor *v) const override;

    std::unique_ptr<IIRStm> stm;
    std::unique_ptr<IIRExp> exp;
};