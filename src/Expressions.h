#pragma once
#include "IVisitor.h"
#include "Identifiers.h"

class IVisitor;
class IIdentifier;

class IExp {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class PlusExp : IExp {
  public:
    PlusExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class MinusExp : IExp {
  public:
    MinusExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class TimesExp : IExp {
  public:
    TimesExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class DivideExp : IExp {
  public:
    DivideExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class AddExp : IExp {
  public:
    AddExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class LessExp : IExp {
  public:
    LessExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class IndexExp : IExp {
  public:
    IndexExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IExp *e2;
};

class LengthExp : IExp {
  public:
    LengthExp(IExp* e1);
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
    IntExp(int num);
    void Accept(IVisitor* v) const override;
    char *Name() const override;
    const int num;
};

class TrueExp : IExp {
  public:
    TrueExp();
    void Accept(IVisitor *v) const override;
    char *Name() const override;
};

class FalseExp : IExp {
  public:
    FalseExp();
    void Accept(IVisitor *v) const override;
    char *Name() const override;
};

class IdExp : IExp {
  public:
    IdExp(IIdentifier* i1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    IIdentifier* i1;
};

class ThisExp : IExp {
  public:
    ThisExp();
    void Accept(IVisitor* v) const override;
    char* Name() const override;
};

class NewIntExp : IExp {
  public:
    explicit NewIntExp(IExp* e1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    IExp* e1;
};

class NewIdExp : IExp {
  public:
    explicit NewIdExp(IIdentifier* i1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    IIdentifier* i1;
};

class NotExp : IExp {
  public:
    explicit NotExp(IExp* e1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    IExp* e1;
};