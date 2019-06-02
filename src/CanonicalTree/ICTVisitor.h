#pragma once

#include <IRTree/IIRVisitor.h>

class IRExpList;
class IRStmList;

static int counter = 0;
static const std::string tempLabel = "temp";

class ICTVisitor : public IIRVisitor {
  public:
    virtual void visit(const IRExpList *n) = 0;
    virtual void visit(const IRStmList *n) = 0;
};
