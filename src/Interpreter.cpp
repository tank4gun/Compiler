#include "IVisitor.h"

class Interpreter : public IVisitor {


    // for Expressions.h

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
        n->e3->Accept(this);
    }
    void visit(const IntExp *n) override {}

    void visit(const BooleanExp *n) override {}

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
    void visit(const ExpList *n) override {
        if (n->exp_val == nullptr) {
            return;
        }
        n->exp_val->Accept(this);
        if (n->exp_next == nullptr) {
            return;
        }
        n->exp_next->Accept(this);
    }

    void visit(const NewExp *n) override {
        n->id->Accept(this);
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
    void visit(const StatementsList *n) {
        if (n->statement_val == nullptr) {
            return;
        }
        n->statement_val->Accept(this);
        if (n->statement_next == nullptr) {
            return;
        }
        n->statement_next->Accept(this);
    }
    void visit(const BraceStatement *n) override {
        n->statements->Accept(this);
    }
    void visit(const ReturnStatement* n) override {
        n->exp->Accept(this);
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
        if (n->var_val == nullptr) {
            return;
        }
        n->var_val->Accept(this);
        if (n->var_next == nullptr) {
            return;
        }
        n->var_next->Accept(this);
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
        if (n->method_val == nullptr) {
            return;
        }
        n->method_val->Accept(this);
        if (n->method_next == nullptr) {
            return;
        }
        n->method_next->Accept(this);
    }

    // for VarDeclaration.h

    void visit(const VarDeclaration *n) override {
        n->id->Accept(this);
        n->type->Accept(this);
    }
    void visit(const VarDeclarationsList *n) override {
        if (n->var_val == nullptr) {
            return;
        }
        n->var_val->Accept(this);
        if (n->var_next == nullptr) {
            return;
        }
        n->var_next->Accept(this);
    }

    // for ClassDeclaration.h

    void visit(const ClassDeclaration *n) override {
        n->i1->Accept(this);
        n->ext->Accept(this);
        n->methods->Accept(this);
        n->vars->Accept(this);
    }
    void visit(const MainClass *n) override {
        n->id1->Accept(this);
        n->id2->Accept(this);
        n->statement->Accept(this);
    }
    void visit(const ClassDeclarationsList *n) override {
        if (n->class_val == nullptr) {
            return;
        }
        n->class_val->Accept(this);
        if (n->class_next == nullptr) {
            return;
        }
        n->class_next->Accept(this);
    }
    void visit(const Extends *n) override {
        if (n->id != nullptr) {
            n->id->Accept(this);
        }
    }

    // for Goal.h

    void visit(const Goal *n) override {
        n->mainClass->Accept(this);
        n->classes->Accept(this);
    }
};