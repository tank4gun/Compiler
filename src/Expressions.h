#pragma once
#include "IVisitor.h"

class IVisitor;

class IExp {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class PlusExp : IExp {
  public:
    PlusExp(IExp *e1, IExp *e2);
    const IExp *e1;
    const IExp *e2;
};

class MinusExp : IExp {
  public:
    MinusExp(IExp *e1, IExp *e2);
    const IExp *e1;
    const IExp *e2;
};

class TimesExp : IExp {
  public:
    TimesExp(IExp *e1, IExp *e2);
    const IExp *e1;
    const IExp *e2;
};

class DivideExp : IExp {
  public:
    DivideExp(IExp *e1, IExp *e2);
    const IExp *e1;
    const IExp *e2;
};

class AddExp : IExp {
  public:
    AddExp(IExp *e1, IExp *e2);
    const IExp *e1;
    const IExp *e2;
};

class LessExp : IExp {
  public:
    LessExp(IExp *e1, IExp *e2);
    const IExp *e1;
    const IExp *e2;
};

class IndexExp : IExp {
  public:
    IndexExp(IExp *e1, IExp *e2);
    const IExp *e1;
    const IExp *e2;
};

class TrueExp : IExp {
};

class FalseExp : IExp {
};
