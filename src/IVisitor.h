#pragma once
#include "Expressions.h"

class IVisitor {
  public:
    virtual void visit(const PlusExp *n) = 0;
    virtual void visit(const MinusExp *n) = 0;
    virtual void visit(const TimesExp *n) = 0;
    virtual void visit(const DivideExp *n) = 0;
    virtual void visit(const AddExp *n) = 0;
    virtual void visit(const LessExp *n) = 0;
    virtual void visit(const IndexExp *n) = 0;
    virtual void visit(const TrueExp *n) = 0;
    virtual void visit(const FalseExp *n) = 0;
};