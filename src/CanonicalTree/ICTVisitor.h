#pragma once

#include <IRTree/IIRVisitor.h>
#include <IRTree/IIRExp.h>
#include <IRTree/IIRStm.h>

class ICTVisitor : public IIRVisitor {
  public:
    virtual void visit(const IRStmList *n) = 0;
    virtual void visit(const IRExpList *n) = 0;
};
