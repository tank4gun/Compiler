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
    void visit(const AndExp *n) override {
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
    void visit(const LengthExp *n) override {
      n->e1->Accept(this);
    }
    void visit(const CallMethodExp *n) override {
      n->e1->Accept(this);
      n->i1->Accept(this);
      n->e2->Accept(this);
      n->e3->Accept(this);
    }
    void visit(const IntExp *n) override {}

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

    void visit(const ParenExp *n) override {
        n->e1->Accept(this);
    }

    // for Identifiers.h

    void visit(const Identifier *n) override {}


    // for Statements.h

    void visit(const IfStatement *n) override {
      n->exp->Accept(this);
      n->statement1->Accept(this);
      n->statement2->Accept(this);
    }
    void visit(const WhileStatement *n) override {
      n->exp->Accept(this);
      n->statement->Accept(this);
    }
    void visit(const OutputStatement *n) override {
      n->exp->Accept(this);
    }
    void visit(const AssignStatement *n) override {
      n->identifier->Accept(this);
      n->exp->Accept(this);
    }
    void visit(const ArrayAssignStatement *n) override {
      n->identifier->Accept(this);
      n->exp1->Accept(this);
      n->exp2->Accept(this);
    }
    void visit(const StatementsList *n) override {
      n->statement_val->Accept(this);
      n->statement_next->Accept(this);
    }
    void visit(const BraceStatement *n) override {
        n->statements->Accept(this);
    }

    // for Types.h

    void visit(const IntArrayType *n) override {}
    void visit(const IntType *n) override {}
    void visit(const BooleanType *n) override {}
    void visit(const IdentifierType *n) override {
        n->id->Accept(this);
    }

    // for MethodDeclaration.h

    void visit(const Argument *n) override {
        n->id->Accept(this);
        n->type->Accept(this);
    }
    void visit(const ArgumentsList *n) override {
        n->var_next->Accept(this);
        n->var_val->Accept(this);
    }
    void visit(const MethodDeclaration *n) override {
        n->type->Accept(this);
        n->id->Accept(this);
        n->exp->Accept(this);
        n->statements->Accept(this);
        n->args->Accept(this);
        n->vars->Accept(this);
    }
    void visit(const MethodDeclarationsList *n) override {
        n->method_next->Accept(this);
        n->method_val->Accept(this);
    }

    // for VarDeclaration.h

    void visit(const VarDeclaration *n) override {
        n->id->Accept(this);
        n->type->Accept(this);
    }
    void visit(const VarDeclarationsList *n) override {
        n->var_val->Accept(this);
        n->var_next->Accept(this);
    }

    // for ClassDeclaration.h

    void visit(const ClassDeclaration *n) override {
        n->i1->Accept(this);
        n->i2->Accept(this);
        n->methods->Accept(this);
        n->vars->Accept(this);
    }
    void visit(const MainClass *n) override {
        n->id1->Accept(this);
        n->id2->Accept(this);
        n->statement->Accept(this);
    }
    void visit(const ClassDeclarationsList *n) override {
        n->class_val->Accept(this);
        n->class_next->Accept(this);
    }

    // for Goal.h

    virtual void visit(const Goal *n) {
        n->mainClass->Accept(this);
        n->classes->Accept(this);
    }
};