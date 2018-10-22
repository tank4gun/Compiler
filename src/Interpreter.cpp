#include "IVisitor.h"

class Interpreter : public IVisitor {


    // for Expressions.h

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

    void visit(const IdExp *n) override {
      n->i1->Accept(this);
    }

    void visit(const ThisExp *n) override {}

    void visit(const NewIntExp *n) override {
      n->e1->Accept(this);
    }

    void visit(const NewIdExp *n) override {
      n->i1->Accept(this);
    }

    void visit(const NotExp *n) override {
      n->e1->Accept(this);
    }


    // for Identifiers.h

    void visit(const Identifier *n) override {}
};
