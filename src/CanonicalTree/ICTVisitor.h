#pragma once

#include <IRTree/IIRVisitor.h>

class IRExpList;
class IRStmList;

class ICTVisitor : public IIRVisitor {
  public:
    virtual void visit(const IRExpList *n) = 0;
    virtual void visit(const IRStmList *n) = 0;
};
