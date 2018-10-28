//
// Created by daniil on 27.10.18.
//
#pragma once
#include <cstdio>
#include "ASTBuilder.h"
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

ASTBuilder::ASTBuilder() {
  printf("AST build started");
}

ASTBuilder::~ASTBuilder() {
  printf("AST build completed");
}

// for Expressions.h

void ASTBuilder::visit(const PlusExp *n) {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  n->e2->Accept(this);
  IExp* e2 = this->exp_pointer;
  PlusExp* ast_exp = new PlusExp(e1, e2);
  this->exp_pointer = ast_exp;
}
void ASTBuilder::visit(const MinusExp *n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  n->e2->Accept(this);
  IExp* e2 = this->exp_pointer;
  MinusExp* ast_exp = new MinusExp(e1, e2);
  this->exp_pointer = ast_exp;
}
void ASTBuilder::visit(const TimesExp *n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  n->e2->Accept(this);
  IExp* e2 = this->exp_pointer;
  TimesExp* ast_exp = new TimesExp(e1, e2);
  this->exp_pointer = ast_exp;
}
void ASTBuilder::visit(const DivideExp *n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  n->e2->Accept(this);
  IExp* e2 = this->exp_pointer;
  DivideExp* ast_exp = new DivideExp(e1, e2);
  this->exp_pointer = ast_exp;
}
void ASTBuilder::visit(const AndExp *n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  n->e2->Accept(this);
  IExp* e2 = this->exp_pointer;
  AndExp* ast_exp = new AndExp(e1, e2);
  this->exp_pointer = ast_exp;
}
void ASTBuilder::visit(const LessExp *n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  n->e2->Accept(this);
  IExp* e2 = this->exp_pointer;
  LessExp* ast_exp = new LessExp(e1, e2);
  this->exp_pointer = ast_exp;
}
void ASTBuilder::visit(const IndexExp *n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  n->e2->Accept(this);
  IExp* e2 = this->exp_pointer;
  IndexExp* ast_exp = new IndexExp(e1, e2);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const LengthExp* n)  {
  n->e1->Accept(this);
  IExp* exp = this->exp_pointer;
  LengthExp* ast_exp = new LengthExp(exp);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const ExpList* n)  {
  const ExpList* curr_node = n;
  std::vector<IExp*> list = std::vector<IExp*>();
  while(curr_node->exp_next != nullptr) {
    curr_node->exp_val->Accept(this);
    IExp* exp = this->exp_pointer;
    list.push_back(exp);
    curr_node = curr_node->exp_next;
  }
  IExp* exp_decl = new ASTExpressionDeclarations(list);
  this->exp_pointer = exp_decl;
}

void ASTBuilder::visit(const CallMethodExp* n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  n->i1->Accept(this);
  IIdentifier* i1 = this->id_pointer;
  n->e3->Accept(this);
  IExp* list = this->exp_pointer;
  IExp* ast_exp = new ASTCallMethodExp(e1, i1, list);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const IntExp* n)  {
  IntExp* ast_exp = new IntExp(n->num);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const TrueExp *n)  {
  this->exp_pointer = new TrueExp();
}

void ASTBuilder::visit(const FalseExp *n)  {
  this->exp_pointer = new FalseExp();
}

void ASTBuilder::visit(const IdExp *n)  {
  n->i1->Accept(this);
  IIdentifier* i1 = this->id_pointer;
  IdExp* ast_exp = new IdExp(i1);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const ThisExp *n)  {
  this->exp_pointer = new ThisExp();
}

void ASTBuilder::visit(const NewIntExp *n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  NewIntExp* ast_exp = new NewIntExp(e1);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const NewIdExp *n)  {
  n->i1->Accept(this);
  IIdentifier* i1 = this->id_pointer;
  NewIdExp* ast_exp = new NewIdExp(i1);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const NotExp *n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  NotExp* ast_exp = new NotExp(e1);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const ParenExp* n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  ParenExp* paren_exp = new ParenExp(e1);
  this->exp_pointer = paren_exp;
}

void ASTBuilder::visit(const ASTCallMethodExp* n) {
  return;
}

void ASTBuilder::visit(const ASTExpressionDeclarations *n) {
  return;
}

// for Identifiers.h

void ASTBuilder::visit(const Identifier *n)  {
  IIdentifier* ast_id = new Identifier(n->id);
  this->id_pointer = ast_id;
}


// for Statements.h

void ASTBuilder::visit(const IfStatement *n)  {
  n->exp->Accept(this);
  IExp* exp = this->exp_pointer;
  n->statement1->Accept(this);
  IStatement* statement1 = this->statement_pointer;
  n->statement2->Accept(this);
  IStatement* statement2 = this->statement_pointer;
  IfStatement* ast_st = new IfStatement(exp, statement1, statement2);
  this->statement_pointer = ast_st;
}
void ASTBuilder::visit(const WhileStatement *n)  {
  n->exp->Accept(this);
  IExp* exp = this->exp_pointer;
  n->statement->Accept(this);
  IStatement* statement = this->statement_pointer;
  WhileStatement* ast_st = new WhileStatement(exp, statement);
  this->statement_pointer = ast_st;
}
void ASTBuilder::visit(const OutputStatement *n)  {
  n->exp->Accept(this);
  IExp* exp = this->exp_pointer;
  OutputStatement* ast_st = new OutputStatement(exp);
  this->statement_pointer = ast_st;
}
void ASTBuilder::visit(const AssignStatement *n)  {
  n->identifier->Accept(this);
  IIdentifier* identifier = this->id_pointer;
  n->exp->Accept(this);
  IExp* exp = this->exp_pointer;
  AssignStatement* ast_st = new AssignStatement(exp, identifier);
  this->statement_pointer = ast_st;
}
void ASTBuilder::visit(const ArrayAssignStatement *n)  {
  n->identifier->Accept(this);
  IIdentifier* identifier = this->id_pointer;
  n->exp1->Accept(this);
  IExp* exp1 = this->exp_pointer;
  n->exp2->Accept(this);
  IExp* exp2 = this->exp_pointer;
  ArrayAssignStatement* ast_st = new ArrayAssignStatement(identifier, exp1, exp2);
  this->statement_pointer = ast_st;
}
void ASTBuilder::visit(const StatementsList *n)  {
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
void ASTBuilder::visit(const BraceStatement* n)  {
  n->statements->Accept(this);
  IStatement* list = this->statement_pointer;
  BraceStatement* ast_st = new BraceStatement(list);
  this->statement_pointer = ast_st;
}

void ASTBuilder::visit(const ASTStatementDeclarations* n) {
  return;
}


// for Types.h

void ASTBuilder::visit(const IntArrayType* n)  {
  IntArrayType* ast_type = new IntArrayType();
  this->type_pointer = ast_type;
}

void ASTBuilder::visit(const BooleanType* n)  {
  BooleanType* ast_type = new BooleanType();
  this->type_pointer = ast_type;
}

void ASTBuilder::visit(const IntType* n)  {
  IntType* ast_type = new IntType();
  this->type_pointer = ast_type;
}

void ASTBuilder::visit(const IdentifierType* n)  {
  n->id->Accept(this);
  IIdentifier* id = this->id_pointer;
  IdentifierType* ast_type = new IdentifierType(id);
  this->type_pointer = ast_type;
}

// for VarDeclaration.h

void ASTBuilder::visit(const VarDeclaration* n)  {
  n->type->Accept(this);
  IType* type = this->type_pointer;
  n->id->Accept(this);
  IIdentifier* id = this->id_pointer;
  VarDeclaration* ast_var = new VarDeclaration(type, id);
  this->var_pointer = ast_var;
}

void ASTBuilder::visit(const VarDeclarationsList* n)  {
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

void ASTBuilder::visit(const ASTVarDeclarations *n) {
  return;
}


// for MethodDeclaration.h

void ASTBuilder::visit(const Argument* n) {
  n->type->Accept(this);
  IType* type = this->type_pointer;
  n->id->Accept(this);
  IIdentifier* id = this->id_pointer;
  Argument* ast_arg = new Argument(type, id);
  this->arg_pointer = ast_arg;
}

void ASTBuilder::visit(const ArgumentsList* n) {
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

void ASTBuilder::visit(const MethodDeclaration* n) {
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

void ASTBuilder::visit(const MethodDeclarationsList* n) {
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

void ASTBuilder::visit(const ASTMethodDeclaration *n) {
  return;
}

void ASTBuilder::visit(const ASTArgumentDeclarations *n) {
  return;
}

void ASTBuilder::visit(const ASTMethodDeclarations* n) {
  return;
}

// for Goal.h

void ASTBuilder::visit(const Goal* n) {
  n->mainClass->Accept(this);
  IClass* mainClass = this->class_pointer;
  n->classes->Accept(this);
  IClass* classes = this->class_pointer;
  Goal* ast_goal = new Goal(mainClass, classes);
  this->goal_pointer = ast_goal;
}

// for ClassDeclaration.h

void ASTBuilder::visit(const Extends* n)  {
  IIdentifier* id;
  if (n->id != nullptr) {
    n->id->Accept(this);
    id = this->id_pointer;
  } else {
    id = nullptr;
  }
  Extends* ast_class = new Extends(id);
  this->class_pointer = ast_class;
}

void ASTBuilder::visit(const ClassDeclaration* n)  {
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

void ASTBuilder::visit(const MainClass* n)  {
  n->id1->Accept(this);
  IIdentifier* i1 = this->id_pointer;
  n->id2->Accept(this);
  IIdentifier* i2 = this->id_pointer;
  n->statement->Accept(this);
  IStatement* statement = this->statement_pointer;
  MainClass* ast_class = new MainClass(i1, i2, statement);
  this->class_pointer = ast_class;
}

void ASTBuilder::visit(const ClassDeclarationsList* n)  {
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

void ASTBuilder::visit(const ASTClassDeclarations* n) {
  return;
}
