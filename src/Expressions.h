#pragma once
#include "IVisitor.h"
#include "Identifiers.h"

class IVisitor;
class IIdentifier;
class Identifier;

class IExp {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class PlusExp : public IExp {
  public:
    PlusExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class MinusExp : public IExp {
  public:
    MinusExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class TimesExp : public IExp {
  public:
    TimesExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class DivideExp : public IExp {
  public:
    DivideExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class AndExp : public IExp {
  public:
    AndExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class LessExp : public IExp {
  public:
    LessExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class IndexExp : public IExp {
  public:
    IndexExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class LengthExp : public IExp {
  public:
    explicit LengthExp(IExp* e1);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
};

class ExpList : IExp {
  public:
    ExpList();
    explicit ExpList(IExp *exp_val);
    ExpList(IExp *exp_val, ExpList *exp_next);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IExp *exp_val;
    const ExpList *exp_next;
};

class CallMethodExp : IExp {
  public:
    CallMethodExp(IExp* e1, IIdentifier* i1, IExp* e2, ExpList* e3);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IIdentifier* i1;
    const IExp* e2;
    const ExpList* e3;
};

class IntExp: IExp {
  public:
    explicit IntExp(int num);
    void Accept(IVisitor* v) const override;
    char *Name() const override;
    int num;
};

class TrueExp : public IExp {
  public:
    TrueExp();
    void Accept(IVisitor *v) const override;
    char *Name() const override;
};

class FalseExp : public IExp {
  public:
    FalseExp();
    void Accept(IVisitor *v) const override;
    char *Name() const override;
};

class IdExp : public IExp {
  public:
    explicit IdExp(IIdentifier* i1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    IIdentifier* i1;
};

class ThisExp : public IExp {
  public:
    ThisExp();
    void Accept(IVisitor* v) const override;
    char* Name() const override;
};

class NewIntExp : public IExp {
  public:
    explicit NewIntExp(IExp* e1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    IExp* e1;
};

class NewIdExp : public IExp {
  public:
    explicit NewIdExp(IIdentifier* i1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    IIdentifier* i1;
};

class NotExp : public IExp {
  public:
    explicit NotExp(IExp* e1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    IExp* e1;
};

class ParenExp: public IExp {
  public:
    explicit ParenExp(IExp* e1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    IExp* e1;
};