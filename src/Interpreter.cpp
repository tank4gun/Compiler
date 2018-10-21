#include "IVisitor.h"

class Interpreter : public IVisitor {
    void visit(const PlusExp *n) override {
      n->e1->Accept(this);
      n->e2->Accept(this);
    }
    void visit(const MinusExp *n) override {
      n->e1->Accept(this);
      n->e2->Accept(this);
    }
    void visit(const TimesExp *n) override {
      n->e1->Accept(this);
      n->e2->Accept(this);
    }
    void visit(const DivideExp *n) override {
      n->e1->Accept(this);
      n->e2->Accept(this);
    }
    void visit(const AddExp *n) override {
      n->e1->Accept(this);
      n->e2->Accept(this);
    }
    void visit(const LessExp *n) override {
      n->e1->Accept(this);
      n->e2->Accept(this);
    }
    void visit(const IndexExp *n) override {
      n->e1->Accept(this);
      n->e2->Accept(this);
    }
    void visit(const TrueExp *n) override {}
    void visit(const FalseExp *n) override {}

};
