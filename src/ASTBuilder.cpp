//
// Created by daniil on 27.10.18.
//
#pragma once
#include "IVisitor.h"
#include "ClassDeclaration.h"
#include "Expressions.h"
#include "Goal.h"
#include "Identifiers.h"
#include "MethodDeclaration.h"
#include "Statements.h"
#include "Types.h"
#include "VarDeclaration.h"
#include "ASTClasses.h"

class ASTBuilder : IVisitor {

    IExp* exp_pointer;
    IIdentifier* id_pointer;
    IStatement* statement_pointer;
    Goal* goal_pointer;
    IVarDeclaration* var_pointer;
    IType* type_pointer;
    IArgument* arg_pointer;
    IMethodDeclaration* meth_pointer;
    IClass* class_pointer;
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
    void visit(const AndExp *n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      n->e2->Accept(this);
      IExp* e2 = this->exp_pointer;
      AndExp* ast_exp = new AndExp(e1, e2);
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

    void visit(const LengthExp* n) override {
      n->e1->Accept(this);
      IExp* exp = this->exp_pointer;
      LengthExp* ast_exp = new LengthExp(exp);
      this->exp_pointer = ast_exp;
    }

    void visit(const ExpList* n) override {
      const ExpList* curr_node = n;
      std::vector<IExp*> list = std::vector<IExp*>();
      while(curr_node->exp_next != nullptr) {
        curr_node->exp_val->Accept(this);
        IExp* exp = this->exp_pointer;
        list.push_back(exp);
        curr_node = curr_node->exp_next;
      }
      ASTExpressionDeclarations* exp_decl = new ASTExpressionDeclarations(list);
      this->exp_pointer = exp_decl;
    }

    void visit(const CallMethodExp* n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      n->i1->Accept(this);
      IIdentifier* i1 = this->id_pointer;
      n->e3->Accept(this);
      IExp* list = this->exp_pointer;
      ASTCallMethodExp* ast_exp = new ASTCallMethodExp(e1, i1, list);
      this->exp_pointer = ast_exp;
    }

    void visit(const IntExp* n) override {
      IntExp* ast_exp = new IntExp(n->num);
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
      IIdentifier* i1 = this->id_pointer;
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

    void visit(const ParenExp* n) override {
      n->e1->Accept(this);
      IExp* e1 = this->exp_pointer;
      ParenExp* paren_exp = new ParenExp(e1);
      this->exp_pointer = paren_exp;
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
      const StatementsList* curr_node = n;
      std::vector<IStatement*> list = std::vector<IStatement*>();
      while(curr_node->statement_next != nullptr) {
        curr_node->statement_val->Accept(this);
        IStatement* ast_st = this->statement_pointer;
        list.push_back(ast_st);
        curr_node = curr_node->statement_next;
      }
      ASTStatementDeclarations* ast_list = new ASTStatementDeclarations(list);
      this->statement_pointer = ast_list;
    }
    void visit(const BraceStatement* n) override {
      n->statements->Accept(this);
      IStatement* list = this->statement_pointer;
      BraceStatement* ast_st = new BraceStatement(list);
      this->statement_pointer = ast_st;
    }
    // for Types.h

    void visit(const IntArrayType* n) override {
      IntArrayType* ast_type = new IntArrayType();
      this->type_pointer = ast_type;
    }

    void visit(const BooleanType* n) override {
      BooleanType* ast_type = new BooleanType();
      this->type_pointer = ast_type;
    }

    void visit(const IntType* n) override {
      IntType* ast_type = new IntType();
      this->type_pointer = ast_type;
    }

    void visit(const IdentifierType* n) override {
      n->id->Accept(this);
      IIdentifier* id = this->id_pointer;
      IdentifierType* ast_type = new IdentifierType(id);
      this->type_pointer = ast_type;
    }

    // for VarDeclaration.h

    void visit(const VarDeclaration* n) override {
      n->type->Accept(this);
      IType* type = this->type_pointer;
      n->id->Accept(this);
      IIdentifier* id = this->id_pointer;
      VarDeclaration* ast_var = new VarDeclaration(type, id);
      this->var_pointer = ast_var;
    }

    void visit(const VarDeclarationsList* n) override {
      std::vector<IVarDeclaration*> list = std::vector<IVarDeclaration*>();
      const VarDeclarationsList* curr_node = n;
      while(curr_node->var_next != nullptr) {
        n->var_val->Accept(this);
        IVarDeclaration* var = this->var_pointer;
        list.push_back(var);
        curr_node = curr_node->var_next;
      }
      IVarDeclaration* ast_var = new ASTVarDeclarations(list);
      this->var_pointer = ast_var;
    }

    // for MethodDeclaration.h

    void visit(const Argument* n) {
      n->type->Accept(this);
      IType* type = this->type_pointer;
      n->id->Accept(this);
      IIdentifier* id = this->id_pointer;
      Argument* ast_arg = new Argument(type, id);
      this->arg_pointer = ast_arg;
    }

    void visit(const ArgumentsList* n) {
      std::vector<IArgument*> list = std::vector<IArgument*>();
      const ArgumentsList* curr_node = n;
      while(curr_node->var_next != nullptr) {
        curr_node->var_val->Accept(this);
        IArgument* arg = this->arg_pointer;
        list.push_back(arg);
        curr_node = curr_node->var_next;
      }
      ASTArgumentDeclarations* ast_args = new ASTArgumentDeclarations(list);
      this->arg_pointer = ast_args;
    }

    void visit(const MethodDeclaration* n) {
      n->type->Accept(this);
      IType* type = this->type_pointer;
      n->id->Accept(this);
      IIdentifier* id = this->id_pointer;
      n->args->Accept(this);
      IArgument* args = this->arg_pointer;
      n->vars->Accept(this);
      IVarDeclaration* vars = this->var_pointer;
      n->statements->Accept(this);
      IStatement* statements = this->statement_pointer;
      n->exp->Accept(this);
      IExp* exp = this->exp_pointer;
      IMethodDeclaration* method = new ASTMethodDeclaration(type, id, args, vars, statements, exp);
      this->meth_pointer = method;
    }

    void visit(const MethodDeclarationsList* n) {
      std::vector<IMethodDeclaration*> list = std::vector<IMethodDeclaration*>();
      const MethodDeclarationsList* curr_node = n;
      while(curr_node->method_next != nullptr) {
        curr_node->method_val->Accept(this);
        IMethodDeclaration* method = this->meth_pointer;
        list.push_back(method);
        curr_node = curr_node->method_next;
      }
      ASTMethodDeclarations* methods = new ASTMethodDeclarations(list);
      this->meth_pointer = methods;
    }

    // for Goal.h

    void visit(const Goal* n) {
      n->mainClass->Accept(this);
      IClass* mainClass = this->class_pointer;
      n->classes->Accept(this);
      IClass* classes = this->class_pointer;
      Goal* ast_goal = new Goal(mainClass, classes);
      this->goal_pointer = ast_goal;
    }

    // for ClassDeclaration.h

    void visit(const Extends* n) override {
      n->id->Accept(this);
      IIdentifier* id = this->id_pointer;
      Extends* ast_class = new Extends(id);
      this->class_pointer = ast_class;
    }

    void visit(const ClassDeclaration* n) override {
      n->i1->Accept(this);
      IIdentifier* i1 = this->id_pointer;
      n->ext->Accept(this);
      IClass* ext = this->class_pointer;
      n->vars->Accept(this);
      IVarDeclaration* ast_vars = this->var_pointer;
      n->methods->Accept(this);
      IMethodDeclaration* ast_list = this->meth_pointer;
      ClassDeclaration* ast_class = new ClassDeclaration(i1, ext, ast_vars, ast_list);
      this->class_pointer = ast_class;
    }

    void visit(const MainClass* n) override {
      n->id1->Accept(this);
      IIdentifier* i1 = this->id_pointer;
      n->id2->Accept(this);
      IIdentifier* i2 = this->id_pointer;
      n->statement->Accept(this);
      IStatement* statement = this->statement_pointer;
      MainClass* ast_class = new MainClass(i1, i2, statement);
      this->class_pointer = ast_class;
    }

    void visit(const ClassDeclarationsList* n) override {
      const ClassDeclarationsList* curr_node = n;
      std::vector<IClass*> list;
      while(curr_node->class_next != nullptr) {
        curr_node->class_val->Accept(this);
        IClass* class_val = this->class_pointer;
        list.push_back(class_val);
        curr_node = curr_node->class_next;
      }
      IClass* ast_classes = new ASTClassDeclarations(list);
      this->class_pointer = ast_classes;
    }
};
