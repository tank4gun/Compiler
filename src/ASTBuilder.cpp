//
// Created by daniil on 27.10.18.
//
#include "IVisitor.h"
#include "ClassDeclaration.h"
#include "Expressions.h"
#include "Goal.h"
#include "Identifiers.h"
#include "MainClass.h"
#include "MethodDeclaration.h"
#include "Statements.h"
#include "Type.h"
#include "VarDeclaration.h"

class ASTBuilder : IVisitor {

    IExp* exp_pointer;
    IIdentifier* id_pointer;
    IStatement* statement_pointer;
    ClassDeclaration* class_pointer;
    ASTClassDeclarations* ast_classes_pointer;
    ASTExpressionDeclarations ast_expr_pointer;
    ASTStatementDeclarations ast_st_pointer;
    ASTMethodDeclarations ast_method_pointer;
    ASTVarDeclarations ast_var_pointer;
    Goal goal_pointer;
    MainClass main_class_pointer;
    // Var
    // Type

    // for Expressions.h

    void visit(const PlusExp *n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      n->e2->Accept(this);
      IExp* e2 = this->exp_pointer;
      PlusExp* ast_exp = new PlusExp(e1, e2);
      this->exp_pointer = ast_exp;
    }
    void visit(const MinusExp *n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      n->e2->Accept(this);
      IExp* e2 = this->exp_pointer;
      MinusExp* ast_exp = new MinusExp(e1, e2);
      this->exp_pointer = ast_exp;
    }
    void visit(const TimesExp *n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      n->e2->Accept(this);
      IExp* e2 = this->exp_pointer;
      TimesExp* ast_exp = new TimesExp(e1, e2);
      this->exp_pointer = ast_exp;
    }
    void visit(const DivideExp *n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      n->e2->Accept(this);
      IExp* e2 = this->exp_pointer;
      DivideExp* ast_exp = new DivideExp(e1, e2);
      this->exp_pointer = ast_exp;
    }
    void visit(const AddExp *n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      n->e2->Accept(this);
      IExp* e2 = this->exp_pointer;
      AddExp* ast_exp = new AddExp(e1, e2);
      this->exp_pointer = ast_exp;
    }
    void visit(const LessExp *n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      n->e2->Accept(this);
      IExp* e2 = this->exp_pointer;
      LessExp* ast_exp = new LessExp(e1, e2);
      this->exp_pointer = ast_exp;
    }
    void visit(const IndexExp *n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      n->e2->Accept(this);
      IExp* e2 = this->exp_pointer;
      IndexExp* ast_exp = new IndexExp(e1, e2);
      this->exp_pointer = ast_exp;
    }
    void visit(const TrueExp *n) override {
      this->exp_pointer = new TrueExp();
    }

    void visit(const FalseExp *n) override {
      this->exp_pointer = new FalseExp();
    }

    void visit(const IdExp *n) override {
      n->i1->Accept(this);
      IExp* i1 = this->exp_pointer;
      IdExp* ast_exp = new IdExp(i1);
      this->exp_pointer = ast_exp;
    }

    void visit(const ThisExp *n) override {
      this->exp_pointer = new ThisExp();
    }

    void visit(const NewIntExp *n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      NewIntExp* ast_exp = new NewIntExp(e1);
      this->exp_pointer = ast_exp;
    }

    void visit(const NewIdExp *n) override {
      n->i1->Accept(this);
      IIdentifier* i1 = this->id_pointer;
      NewIdExp* ast_exp = new NewIdExp(i1);
      this->exp_pointer = ast_exp;
    }

    void visit(const NotExp *n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      NotExp* ast_exp = new NotExp(e1);
      this->exp_pointer = ast_exp;
    }


    // for Identifiers.h

    void visit(const Identifier *n) override {
      IIdentifier* ast_id = new Identifier(n->id);
      this->id_pointer = ast_id;
    }


    // for Statements.h

    void visit(const IfStatement *n) override {
      n->exp->Accept(this);
      IExp* exp = this->exp_pointer;
      n->statement1->Accept(this);
      IStatement* statement1 = this->statement_pointer;
      n->statement2->Accept(this);
      IStatement* statement2 = this->statement_pointer;
      IfStatement* ast_st = new IfStatement(exp, statement1, statement2);
      this->statement_pointer = ast_st;
    }
    void visit(const WhileStatement *n) override {
      n->exp->Accept(this);
      IExp* exp = this->exp_pointer;
      n->statement->Accept(this);
      IStatement* statement = this->statement_pointer;
      WhileStatement* ast_st = new WhileStatement(exp, statement);
      this->statement_pointer = ast_st;
    }
    void visit(const OutputStatement *n) override {
      n->exp->Accept(this);
      IExp* exp = this->exp_pointer;
      OutputStatement* ast_st = new OutputStatement(exp);
      this->statement_pointer = ast_st;
    }
    void visit(const AssignStatement *n) override {
      n->identifier->Accept(this);
      IIdentifier* identifier = this->id_pointer;
      n->exp->Accept(this);
      IExp* exp = this->exp_pointer;
      AssignStatement* ast_st = new AssignStatement(exp, identifier);
      this->statement_pointer = ast_st;
    }
    void visit(const ArrayAssignStatement *n) override {
      n->identifier->Accept(this);
      IIdentifier* identifier = this->id_pointer;
      n->exp1->Accept(this);
      IExp* exp1 = this->exp_pointer;
      n->exp2->Accept(this);
      IExp* exp2 = this->exp_pointer;
      ArrayAssignStatement* ast_st = new ArrayAssignStatement(identifier, exp1, exp2);
      this->statement_pointer = ast_st;
    }
    void visit(const StatementsList *n) override {
      n->statement_val->Accept(this);
      IStatement* statement1 = this->statement_pointer;
      n->statement_next->Accept(this);
      IStatement* statement2 = this->statement_pointer;
      StatementsList* ast_st = new StatementsList(statement1, statement2);
    }

};
