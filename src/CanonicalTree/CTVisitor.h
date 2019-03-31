#pragma once

class CTVisitor : public IIRVisitor {
  public:
    virtual void visit(const IRStmList *n) = 0;
    virtual void visit(const IRExpList *n) = 0;
};
