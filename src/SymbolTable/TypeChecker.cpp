//
// Created by daniil on 18.11.18.
//
#pragma once
#include <cstdio>
#include <string>
#include <boost/format.hpp>
#include <curand.h>
#include "TypeChecker.h"

VariableInfo* TypeChecker::FindVar(Symbol* symbol) {
  if(methodInfo != nullptr) {
    auto field = methodInfo->args.find(symbol);
    if (field != methodInfo->args.end()) {
      return field->second;
    }
    field = methodInfo->vars.find(symbol);
    if (field != methodInfo->vars.end()) {
      return field->second;
    }
  }
  return classInfo->getVar(symbol);
}

void TypeChecker::visit(const BinOp *n) {
  n->e1->Accept(this);
  TypeInfo e1 = typeInfo;
  n->e2->Accept(this);
  TypeInfo e2 = typeInfo;
  if(n->operation == BinaryOps::ANDOP) {
    if (e1.type != "BooleanExp" || e2.type != "BooleanExp") {
      std::string err = "One or more types in ANDOP are not boolean";
      errors.push_back(err);
    }
    typeInfo = TypeInfo("BooleanType");
  } else {
    if (e1.type != "IntExp" || e2.type != "IntExp") {
      std::string err = (boost::format("One or more types in %s are not int") % n->operation).str();
      errors.push_back(err);
    }
    typeInfo = TypeInfo("IntType");
  }
}

void TypeChecker::visit(const IndexExp *n) {
  n->e2->Accept(this);
  TypeInfo e2 = typeInfo;
  if (e2.type != "Int") {
    std::string err = "Index is not integer";
    errors.push_back(err);
  }
  n->e1->Accept(this);
  TypeInfo e1 = typeInfo;
  if (e1.type != "IntArrayType") {
    std::string err = "Object is not an integer array";
    errors.push_back((err));
  }
  std::string int_type = "Int";
  typeInfo = TypeInfo(int_type);
}

void TypeChecker::visit(const LengthExp *n) {
  n->e1->Accept(this);
  TypeInfo e1 = typeInfo;
  if (e1.type != "IntArrayType") {
    std::string err = "Object to get length from is not an integer array";
    errors.push_back((err));
  }
  std::string int_type = "Int";
  typeInfo = TypeInfo(int_type);
}

void TypeChecker::visit(const ASTCallMethodExp *n) {
  n->e1->Accept(this);
  TypeInfo e1 = typeInfo;
  if (table->classes.find(e1.name) != table->classes.end()) {
    ClassInfo* class_info = table->classes[e1.name];
    if (class_info->methods.find(n->i1->id) != class_info->methods.end()) {
      MethodInfo* method_info = class_info->methods[n->i1->id];
      std::unique_ptr<std::vector<std::unique_ptr<IExp>>>& arguments = n->e2->expressions;
      if (arguments->size() != method_info->args.size()) {
        std::string err = "Num of arguments in method declaration and method call are different";
        errors.push_back((err));
      }
      for (int i = 0; i < arguments->size(); i++) {
        (*arguments)[i]->Accept(this);
        TypeInfo curr_e = typeInfo;
        // Somehow check types
      }
      typeInfo = TypeInfo(method_info->returnType->Name());
      return;
    }
    else {
      std::string err = "Can't find this method in class";
      errors.push_back((err));
      typeInfo = TypeInfo("Err");
      return;
    }
  }
  else {
    std::string err = "Can't find this class";
    errors.push_back((err));
    typeInfo = TypeInfo("Err");
    return;
  }
}

void TypeChecker::visit(const BooleanExp *n) {
  typeInfo = TypeInfo("BooleanType");
}

void TypeChecker::visit(const ThisExp *n) {
  typeInfo = TypeInfo("Custom", classInfo->name);
}

void TypeChecker::visit(const NewIntExp *n) {
  n->e1->Accept(this);
  TypeInfo e1 = typeInfo;
  if (e1.type == "Int") {
    std::string err = "Array length isn't integer";
    errors.push_back((err));
  }
  typeInfo = TypeInfo("IntArrayType");
}

void TypeChecker::visit(const ExpList* n) {}
void TypeChecker::visit(const CallMethodExp* n) {}
void TypeChecker::visit(const NewIdExp* n) {}
void TypeChecker::visit(const ASTExpressionDeclarations* n) {}
void TypeChecker::visit(const NewExp *n) {}



void TypeChecker::visit(const BooleanType *n) {
  typeInfo = TypeInfo(n->Name());
}

void TypeChecker::visit(const IntArrayType *n) {
  typeInfo = TypeInfo(n->Name());
}

void TypeChecker::visit(const IntType *n) {
  typeInfo = TypeInfo(n->Name());
}

void TypeChecker::visit(const IdentifierType *n) {
  n->id->Accept(this);
  typeInfo = TypeInfo(n->id->id->String());
}

void TypeChecker::visit(const Identifier *n) {
  if (FindVar(n->id) == nullptr) {
    std::string err = (boost::format("Can't find %s type in table classes") % n->id->String()).str();
    errors.push_back(err);
    typeInfo = TypeInfo("");
    return;
  }
  symbol = n->id;

}

void TypeChecker::visit(const IntExp *n) {
  typeInfo = TypeInfo(n->Name());
}

void TypeChecker::visit(const NotExp *n) {
  n->e1->Accept(this);
  TypeInfo t = typeInfo;
  if (t.type != "BooleanExp") {
    std::string err = "Expression type is not bool";
    errors.push_back(err);
  }
  typeInfo = TypeInfo("BooleanType");
}


void TypeChecker::visit(const IdExp *n) {
  n->i1->Accept(this);
  typeInfo = TypeInfo("");
}

void TypeChecker::visit(const ASTBraceStatement *n) {
  auto& statements = n->statements->statements;
  for (int i = 0; i < statements->size(); i++) {
    (*statements)[i]->Accept(this);
  }
}

void TypeChecker::visit(const IfStatement *n) {
  n->exp->Accept(this);
  TypeInfo e1 = typeInfo;
  if (typeInfo.type != "BooleanType") {
    std::string err = "Expression type is not bool";
    errors.push_back(err);
  }
  n->statement1->Accept(this);
  n->statement2->Accept(this);
}

void TypeChecker::visit(const WhileStatement *n) {
  n->exp->Accept(this);
  TypeInfo e1 = typeInfo;
  if (typeInfo.type != "BooleanType") {
    std::string err = "Expression type is not bool";
    errors.push_back(err);
  }
  n->statement->Accept(this);
}

void TypeChecker::visit(const OutputStatement *n) {
  n->exp->Accept(this);
}

void TypeChecker::visit(const AssignStatement *n) {
  n->exp->Accept(this);
  TypeInfo e1 = typeInfo;
  if (e1.type != FindVar(n->identifier->id)->type) {
    std::string err = "Identifier type and expression type are different";
    errors.push_back(err);
  }
}

void TypeChecker::visit(const ArrayAssignStatement *n) {
  if (FindVar(n->identifier->id)->type != "IntArrayType") {
    std::string err = "Identifier type is not integer array";
    errors.push_back(err);
  }
  n->exp1->Accept(this);
  TypeInfo e1 = typeInfo;
  if (e1.type != "IntType") {
    std::string err = "Expression type is not integer";
    errors.push_back(err);
  }
  n->exp2->Accept(this);
  TypeInfo e2 = typeInfo;
  if (e2.type != "IntType") {
    std::string err = "Expression type is not integer";
    errors.push_back(err);
  }
}

void TypeChecker::visit(const StatementsList* n) {}
void TypeChecker::visit(const BraceStatement* n) {}
void TypeChecker::visit(const ASTStatementsList* n) {}

void TypeChecker::visit(const ReturnStatement *n) {
  n->exp->Accept(this);
}

void TypeChecker::visit(const VarDeclaration* n) {}
void TypeChecker::visit(const VarDeclarationsList* n) {}
void TypeChecker::visit(const ASTVarDeclarations *n) {}
void TypeChecker::visit(const Argument* n) {}
void TypeChecker::visit(const ArgumentsList* n) {}
void TypeChecker::visit(const MethodDeclaration* n) {}
void TypeChecker::visit(const MethodDeclarationsList* n) {}
void TypeChecker::visit(const ASTArgumentsList* n) {}
void TypeChecker::visit(const ASTMethodsList* n) {}
void TypeChecker::visit(std::unique_ptr<Goal>& n) {}
void TypeChecker::visit(const Extends* n) {}
void TypeChecker::visit(const ClassDeclarationsList* n) {}
void TypeChecker::visit(const ASTClassDeclarations *n) {}


void TypeChecker::visit(const ASTMethodDeclaration *n) {
  for (auto & statement : *n->statements->statements) {
    statement->Accept(this);
  }

  n->exp->Accept(this);
  TypeInfo exp = typeInfo;
  if (exp.type.compare(n->id->id->String())) {
    std::string err = "Method return type is not equal to return expression type";
    errors.push_back(err);
  }
}

void TypeChecker::visit(const ClassDeclaration *n) {}

void TypeChecker::visit(const ASTClassDeclaration *n) {
  for (auto & method : *n->methods->methods) {
    method->Accept(this);
  }
}

void TypeChecker::visit(const MainClass *n) {
  n->statement->Accept(this);
}

void TypeChecker::visit(std::unique_ptr<ASTGoal> &n) {
  n->mainClass->Accept(this);
  for (auto & class_ : *n->classes->classes) {
    class_->Accept(this);
  }
}
