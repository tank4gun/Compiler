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

class CallMethodExp : IExp {
  public:
    CallMethodExp(IExp* e1, IIdentifier* i1, IExp* e2, IExp* e3);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    const IExp *e1;
    const IIdentifier* i1;
    const IExp* e2;
    const IExp* e3;
};

class TrueExp : IExp {
    TrueExp();
    void Accept(IVisitor *v) const override;
    char *Name() const override;
};

class FalseExp : IExp {
    FalseExp();
    void Accept(IVisitor *v) const override;
    char *Name() const override;
};
