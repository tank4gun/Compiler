//
// Created by daniil on 27.10.18.
//
#include "ASTBuilder.h"

ASTBuilder::ASTBuilder() {
  printf("AST build started");
}

ASTBuilder::~ASTBuilder() {
  printf("AST build completed");
}

// for Expressions.h


void ASTBuilder::visit(const IndexExp *n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  n->e2->Accept(this);
  IExp* e2 = this->exp_pointer;
  IndexExp* ast_exp = new IndexExp(e1, e2, n->location);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const LengthExp* n)  {
  n->e1->Accept(this);
  IExp* exp = this->exp_pointer;
  LengthExp* ast_exp = new LengthExp(exp, n->location);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const ExpList* n)  {
  const ExpList* curr_node = n;
  std::vector<std::unique_ptr<IExp>>* list = new std::vector<std::unique_ptr<IExp>>();
  if (curr_node->exp_val != nullptr) {
    curr_node->exp_val->Accept(this);
    std::unique_ptr<IExp> exp(this->exp_pointer);
    list->push_back(std::move(exp));
  }
  while(curr_node->exp_next != nullptr) {
    const ExpList* old = curr_node;
    curr_node = curr_node->exp_next;
//    delete(old);
    if (curr_node->exp_val != nullptr) {
      curr_node->exp_val->Accept(this);
      std::unique_ptr<IExp> exp(this->exp_pointer);
      list->push_back(std::move(exp));
    }
  }
  IListDeclaration* list_decl = new ASTExpressionDeclarations(list, n->location);
  this->list_pointer = list_decl;
}

void ASTBuilder::visit(const CallMethodExp* n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  n->i1->Accept(this);
  IIdentifier* i1 = this->id_pointer;
  n->e3->Accept(this);
  IListDeclaration* list = this->list_pointer;
  IExp* ast_exp = new ASTCallMethodExp(e1, i1, list, n->location);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const IntExp* n)  {
  IntExp* ast_exp = new IntExp(n->num, n->location);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const BooleanExp *n)  {
  this->exp_pointer = new BooleanExp(n->value, n->location);
}

void ASTBuilder::visit(const IdExp *n)  {
  n->i1->Accept(this);
  IIdentifier* i1 = this->id_pointer;
  IdExp* ast_exp = new IdExp(i1, n->location);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const ThisExp *n)  {
  this->exp_pointer = new ThisExp(n->location);
}

void ASTBuilder::visit(const NewIntExp *n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  NewIntExp* ast_exp = new NewIntExp(e1, n->location);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const NewIdExp *n)  {
  n->i1->Accept(this);
  IIdentifier* i1 = this->id_pointer;
  NewIdExp* ast_exp = new NewIdExp(i1, n->location);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const NotExp *n)  {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  NotExp* ast_exp = new NotExp(e1, n->location);
  this->exp_pointer = ast_exp;
}

void ASTBuilder::visit(const ASTCallMethodExp* n) {
}

void ASTBuilder::visit(const ASTExpressionDeclarations *n) {
}

void ASTBuilder::visit(const NewExp *n) {
  n->id->Accept(this);
  IIdentifier* e1 = this->id_pointer;
  NewExp* new_exp = new NewExp(e1, n->location);
  this->exp_pointer = new_exp;
}

void ASTBuilder::visit(const BinOp *n) {
  n->e1->Accept(this);
  IExp* e1 = this->exp_pointer;
  n->e2->Accept(this);
  IExp* e2 = this->exp_pointer;
  IExp* binop = new BinOp(n->operation, e1, e2, n->location);
  this->exp_pointer = binop;
}

// for Identifiers.h

void ASTBuilder::visit(const Identifier *n)  {
  IIdentifier* ast_id = new Identifier(n->id, n->location);
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
  IfStatement* ast_st = new IfStatement(exp, statement1, statement2, n->location);
  this->statement_pointer = ast_st;
}
void ASTBuilder::visit(const WhileStatement *n)  {
  n->exp->Accept(this);
  IExp* exp = this->exp_pointer;
  n->statement->Accept(this);
  IStatement* statement = this->statement_pointer;
  WhileStatement* ast_st = new WhileStatement(exp, statement, n->location);
  this->statement_pointer = ast_st;
}
void ASTBuilder::visit(const OutputStatement *n)  {
  n->exp->Accept(this);
  IExp* exp = this->exp_pointer;
  OutputStatement* ast_st = new OutputStatement(exp, n->location);
  this->statement_pointer = ast_st;
}
void ASTBuilder::visit(const AssignStatement *n)  {
  n->identifier->Accept(this);
  IIdentifier* identifier = this->id_pointer;
  n->exp->Accept(this);
  IExp* exp = this->exp_pointer;
  AssignStatement* ast_st = new AssignStatement(exp, identifier, n->location);
  this->statement_pointer = ast_st;
}
void ASTBuilder::visit(const ArrayAssignStatement *n)  {
  n->identifier->Accept(this);
  IIdentifier* identifier = this->id_pointer;
  n->exp1->Accept(this);
  IExp* exp1 = this->exp_pointer;
  n->exp2->Accept(this);
  IExp* exp2 = this->exp_pointer;
  ArrayAssignStatement* ast_st = new ArrayAssignStatement(identifier, exp1, exp2, n->location);
  this->statement_pointer = ast_st;
}
void ASTBuilder::visit(const StatementsList *n)  {
  const StatementsList* curr_node = n;
  std::vector<std::unique_ptr<IStatement>>* list = new std::vector<std::unique_ptr<IStatement>>();
  if (curr_node->statement_val != nullptr) {
    curr_node->statement_val->Accept(this);
    std::unique_ptr<IStatement> ast_st(this->statement_pointer);
    list->push_back(std::move(ast_st));
  }
  while(curr_node->statement_next != nullptr) {
    curr_node = curr_node->statement_next;
    if (curr_node->statement_val != nullptr) {
      curr_node->statement_val->Accept(this);
      std::unique_ptr<IStatement> ast_st(this->statement_pointer);
      list->push_back(std::move(ast_st));
    }
  }
  IListDeclaration* ast_list = new ASTStatementsList(list, n->location);
  this->list_pointer = ast_list;
}
void ASTBuilder::visit(const BraceStatement* n)  {
  n->statements->Accept(this);
  IListDeclaration* list = this->list_pointer;
  IStatement* ast_st = new ASTBraceStatement(list, n->location);
  this->statement_pointer = ast_st;
}

void ASTBuilder::visit(const ASTStatementsList* n) {}

void ASTBuilder::visit(const ASTBraceStatement *n) {}
void ASTBuilder::visit(const ReturnStatement *n) {
  n->exp->Accept(this);
  IExp* e1 = this->exp_pointer;
  ReturnStatement* return_exp = new ReturnStatement(e1, n->location);
  this->statement_pointer = return_exp;
}

// for Types.h

void ASTBuilder::visit(const IntArrayType* n)  {
  IntArrayType* ast_type = new IntArrayType(n->location);
  this->type_pointer = ast_type;
}

void ASTBuilder::visit(const BooleanType* n)  {
  BooleanType* ast_type = new BooleanType(n->location);
  this->type_pointer = ast_type;
}

void ASTBuilder::visit(const IntType* n)  {
  IntType* ast_type = new IntType(n->location);
  this->type_pointer = ast_type;
}

void ASTBuilder::visit(const IdentifierType* n)  {
  n->id->Accept(this);
  IIdentifier* id = this->id_pointer;
  IdentifierType* ast_type = new IdentifierType(id, n->location);
  this->type_pointer = ast_type;
}

// for VarDeclaration.h

void ASTBuilder::visit(const VarDeclaration* n)  {
  n->type->Accept(this);
  IType* type = this->type_pointer;
  n->id->Accept(this);
  IIdentifier* id = this->id_pointer;
  VarDeclaration* ast_var = new VarDeclaration(type, id, n->location);
  this->var_pointer = ast_var;
}

void ASTBuilder::visit(const VarDeclarationsList* n)  {
  std::vector<std::unique_ptr<IVarDeclaration>>* list = new std::vector<std::unique_ptr<IVarDeclaration>>();
  const VarDeclarationsList* curr_node = n;
  if (curr_node->var_val != nullptr) {
    curr_node->var_val->Accept(this);
    std::unique_ptr<IVarDeclaration> var(this->var_pointer);
    list->push_back(std::move(var));
  }
  while(curr_node->var_next != nullptr) {
    const VarDeclarationsList* old = curr_node;
    curr_node = curr_node->var_next;
//    delete(old);
    if (curr_node->var_val != nullptr) {
      curr_node->var_val->Accept(this);
      std::unique_ptr<IVarDeclaration> var(this->var_pointer);
      list->push_back(std::move(var));
    }
  }
  IListDeclaration* ast_var = new ASTVarDeclarations(list, n->location);
  this->list_pointer = ast_var;
}

void ASTBuilder::visit(const ASTVarDeclarations *n) {}


// for MethodDeclaration.h

void ASTBuilder::visit(const Argument* n) {
  n->type->Accept(this);
  IType* type = this->type_pointer;
  n->id->Accept(this);
  IIdentifier* id = this->id_pointer;
  Argument* ast_arg = new Argument(type, id, n->location);
  this->arg_pointer = ast_arg;
}

void ASTBuilder::visit(const ArgumentsList* n) {
  std::vector<std::unique_ptr<IArgument>>* list = new std::vector<std::unique_ptr<IArgument>>();
  const ArgumentsList* curr_node = n;
  if (curr_node->var_val != nullptr) {
    curr_node->var_val->Accept(this);
    std::unique_ptr<IArgument> arg(this->arg_pointer);
    list->push_back(std::move(arg));
  }
  while(curr_node->var_next != nullptr) {
    const ArgumentsList* old = curr_node;
    curr_node = curr_node->var_next;
//    delete(old);
    if (curr_node->var_val != nullptr) {
      curr_node->var_val->Accept(this);
      std::unique_ptr<IArgument> arg(this->arg_pointer);
      list->push_back(std::move(arg));
    }
  }
  IListDeclaration* ast_args = new ASTArgumentsList(list, n->location);
  this->list_pointer = ast_args;
}

void ASTBuilder::visit(const MethodDeclaration* n) {
  n->type->Accept(this);
  IType* type = this->type_pointer;
  n->id->Accept(this);
  IIdentifier* id = this->id_pointer;
  n->args->Accept(this);
  IListDeclaration* args = this->list_pointer;
  n->vars->Accept(this);
  IListDeclaration* vars = this->list_pointer;
  n->statements->Accept(this);
  IListDeclaration* statements = this->list_pointer;
  n->exp->Accept(this);
  IStatement* exp = this->statement_pointer;
  IMethodDeclaration* method = new ASTMethodDeclaration(type, id, args, vars, statements, exp, n->location);
  this->meth_pointer = method;
}

void ASTBuilder::visit(const MethodDeclarationsList* n) {
  std::vector<std::unique_ptr<IMethodDeclaration>>* list = new std::vector<std::unique_ptr<IMethodDeclaration>>();
  const MethodDeclarationsList* curr_node = n;
  curr_node->method_val->Accept(this);
  std::unique_ptr<IMethodDeclaration> method(this->meth_pointer);
  list->push_back(std::move(method));
  while(curr_node->method_next != nullptr) {
    const MethodDeclarationsList* old = curr_node;
    curr_node = curr_node->method_next;
//    delete(old);
    if (curr_node->method_val != nullptr) {
      curr_node->method_val->Accept(this);
      std::unique_ptr<IMethodDeclaration> method(this->meth_pointer);
      list->push_back(std::move(method));
    }
  }
  IListDeclaration* methods = new ASTMethodsList(list, n->location);
  this->list_pointer = methods;
}

void ASTBuilder::visit(const ASTMethodDeclaration *n) {}

void ASTBuilder::visit(const ASTArgumentsList *n) {}

void ASTBuilder::visit(const ASTMethodsList* n) {}

// for Goal.h

void ASTBuilder::visit(std::unique_ptr<Goal>& n) {
  n->mainClass->Accept(this);
  IClass* mainClass = this->class_pointer;
  n->classes->Accept(this);
  IListDeclaration* classes = this->list_pointer;
  std::unique_ptr<Goal> ast_goal = std::make_unique<Goal>(mainClass, classes, n->location);
  this->goal_pointer = std::move(ast_goal);
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
  Extends* ast_class = new Extends(id, n->location);
  this->class_pointer = ast_class;
}

void ASTBuilder::visit(const ClassDeclaration* n)  {
  n->i1->Accept(this);
  IIdentifier* i1 = this->id_pointer;
  n->ext->Accept(this);
  IClass* ext = this->class_pointer;
  n->vars->Accept(this);
  IListDeclaration* ast_vars = this->list_pointer;
  n->methods->Accept(this);
  IListDeclaration* ast_list = this->list_pointer;
  ClassDeclaration* ast_class = new ClassDeclaration(i1, ext, ast_vars, ast_list, n->location);
  this->class_pointer = ast_class;
}

void ASTBuilder::visit(const MainClass* n)  {
  n->id1->Accept(this);
  IIdentifier* i1 = this->id_pointer;
  n->id2->Accept(this);
  IIdentifier* i2 = this->id_pointer;
  n->statement->Accept(this);
  IStatement* statement = this->statement_pointer;
  MainClass* ast_class = new MainClass(i1, i2, statement, n->location);
  this->class_pointer = ast_class;
}

void ASTBuilder::visit(const ClassDeclarationsList* n)  {
  const ClassDeclarationsList* curr_node = n;
  std::vector<std::unique_ptr<IClass>>* list = new std::vector<std::unique_ptr<IClass>>();
  curr_node->class_val->Accept(this);
  std::unique_ptr<IClass> class_val(this->class_pointer);
  list->push_back(std::move(class_val));
  while(curr_node->class_next != nullptr) {
    const ClassDeclarationsList* old = curr_node;
    curr_node = curr_node->class_next;
//    delete(old);
    if (curr_node->class_val != nullptr) {
      curr_node->class_val->Accept(this);
      std::unique_ptr<IClass> class_val1(this->class_pointer);
      list->push_back(std::move(class_val1));
    }
  }
  IListDeclaration* ast_classes = new ASTClassDeclarations(list, n->location);
  this->list_pointer = ast_classes;
}

void ASTBuilder::visit(const ASTClassDeclarations* n) {}
