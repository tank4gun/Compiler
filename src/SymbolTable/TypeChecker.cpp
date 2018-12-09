#include <cstdio>
#include <string>
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
  if (classInfo != nullptr) {
    return classInfo->getVar(symbol);
  }
    return nullptr;
}

void TypeChecker::visit(const BinOp *n) {
  n->e1->Accept(this);
  TypeInfo e1 = typeInfo;
  n->e2->Accept(this);
  TypeInfo e2 = typeInfo;
  if(n->operation == BinaryOps::ANDOP) {
    if (e1.type != "BooleanType" || e2.type != "BooleanType") {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Arguments must be booleans";
      errors.push_back(err);
    }
    typeInfo = TypeInfo("BooleanType");
  } else {
    if ((e1.type != "IntExp" && e1.type != "IntType") || (e2.type != "IntExp" && e2.type != "IntType")) {
        std::string err = "Line " + std::to_string(n->location.first_line)
            + ", column " + std::to_string(n->location.first_column) +
            ": Arguments must be integers";
        errors.push_back(err);
    }
    if (n->operation == BinaryOps::LESSOP) {
        typeInfo = TypeInfo("BooleanType");
    } else {
        typeInfo = TypeInfo("IntType");
    }
  }
}

void TypeChecker::visit(const IndexExp *n) {
  n->e2->Accept(this);
  TypeInfo e2 = typeInfo;
  if (e2.type != "IntType") {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Index must be integer";
      errors.push_back(err);
  }
  n->e1->Accept(this);
  TypeInfo e1 = typeInfo;
  if (e1.type != "IntArrayType") {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Object must be integer array";
      errors.push_back(err);
  }
  typeInfo = TypeInfo("IntType");
}

void TypeChecker::visit(const LengthExp *n) {
  n->e1->Accept(this);
  TypeInfo e1 = typeInfo;
  if (e1.type != "IntArrayType") {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Object must be integer array";
      errors.push_back(err);
  }
  typeInfo = TypeInfo("IntType");
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
          std::string err = "Line " + std::to_string(n->location.first_line)
              + ", column " + std::to_string(n->location.first_column) +
              ": Number of arguments is different from declaration in line " + std::to_string(method_info->location.first_line);
          errors.push_back(err);
      }
      for (int i = 0; i < arguments->size(); i++) {
        (*arguments)[i]->Accept(this);
        TypeInfo curr_e = typeInfo;
        // Somehow check types
      }
      typeInfo = TypeInfo(method_info->returnType, method_info->customReturnType);
      return;
    }
    else {
        std::string err = "Line " + std::to_string(n->location.first_line)
            + ", column " + std::to_string(n->location.first_column) +
            ": Method wasn't declared";
        errors.push_back(err);
      typeInfo = TypeInfo("Err");
      return;
    }
  }
  else if (typeInfo.type == "custom") {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Class " +  e1.name->String() + " wasn't declared";
      errors.push_back(err);
    typeInfo = TypeInfo("Err");
    return;
  } else {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Value is not a class";
      errors.push_back(err);
  }
}

void TypeChecker::visit(const BooleanExp *n) {
  typeInfo = TypeInfo("BooleanType");
}

void TypeChecker::visit(const ThisExp *n) {
  typeInfo = TypeInfo("custom", classInfo->name);
}

void TypeChecker::visit(const NewIntExp *n) {
  n->e1->Accept(this);
  TypeInfo e1 = typeInfo;
  if (e1.type != "IntType") {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Array length must be integer";
      errors.push_back(err);
  }
  typeInfo = TypeInfo("IntArrayType");
}

void TypeChecker::visit(const ExpList* n) {}
void TypeChecker::visit(const CallMethodExp* n) {}
void TypeChecker::visit(const NewIdExp* n) {
    n->i1->Accept(this);
}
void TypeChecker::visit(const ASTExpressionDeclarations* n) {}
void TypeChecker::visit(const NewExp *n) {
    n->id->Accept(this);
}



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
}

void TypeChecker::visit(const Identifier *n) {
    VariableInfo* aa = FindVar(n->id);
    if (aa == nullptr) {
        typeInfo = TypeInfo("custom", n->id);
    } else {
        typeInfo = TypeInfo(aa->type, n->id);
    }

}

void TypeChecker::visit(const IntExp *n) {
  typeInfo = TypeInfo("IntType");
}

void TypeChecker::visit(const NotExp *n) {
  n->e1->Accept(this);
  TypeInfo t = typeInfo;
  if (t.type != "BooleanType") {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Expression type must be boolean, found " + t.type;
      errors.push_back(err);
  }
  typeInfo = TypeInfo("BooleanType");
}


void TypeChecker::visit(const IdExp *n) {
    VariableInfo* varInfo = FindVar(n->i1->id);
    if (varInfo == nullptr) {
        std::string err = "Line " + std::to_string(n->location.first_line)
            + ", column " + std::to_string(n->location.first_column) +
            ": Variable wasn't declared";
        errors.push_back(err);
        typeInfo = TypeInfo("custom", n->i1->id);
    } else {
        typeInfo = TypeInfo(varInfo->type, varInfo->custom_type);
    }
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
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Expression type must be boolean, found " + typeInfo.type;
      errors.push_back(err);
  }
  n->statement1->Accept(this);
  n->statement2->Accept(this);
}

void TypeChecker::visit(const WhileStatement *n) {
  n->exp->Accept(this);
  TypeInfo e1 = typeInfo;
  if (typeInfo.type != "BooleanType") {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Expression type must be boolean, found " + typeInfo.type;
      errors.push_back(err);
  }
  n->statement->Accept(this);
}

void TypeChecker::visit(const OutputStatement *n) {
  n->exp->Accept(this);
  if (typeInfo.name != nullptr) {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Can not print custom class";
      errors.push_back(err);
  }
}

void TypeChecker::visit(const AssignStatement *n) {
  n->exp->Accept(this);
  TypeInfo e1 = typeInfo;
  VariableInfo* aa = FindVar(n->identifier->id);
  if ((e1.type != FindVar(n->identifier->id)->type) ||
  (e1.name != nullptr && FindVar(n->identifier->id)->custom_type != nullptr && e1.name != FindVar(n->identifier->id)->custom_type)) {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Found different types";
      errors.push_back(err);
      if (n->location.first_line == 54) {
          if (e1.name != nullptr) {
              errors.push_back(e1.type + " -- type and " + e1.name->String());
          } else {
              errors.push_back(e1.type + " -- type and nothing here");
          }
          if (aa->custom_type != nullptr) {
              errors.push_back(aa->type + " -- type for left " + aa->custom_type->String());
          } else {
              errors.push_back(aa->type + " -- type for left and nothing heer");
          }
      }
  }
}

void TypeChecker::visit(const ArrayAssignStatement *n) {
  if (FindVar(n->identifier->id)->type != "IntArrayType") {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Variable must be integer array";
      errors.push_back(err);
  }
  n->exp1->Accept(this);
  TypeInfo e1 = typeInfo;
  if (e1.type != "IntType") {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Expression type must be integer";
      errors.push_back(err);
  }
  n->exp2->Accept(this);
  TypeInfo e2 = typeInfo;
  if (e2.type != "IntType") {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Expression type must be integer";
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
void TypeChecker::visit(const Argument* n) {
    Symbol* arg_class = methodInfo->args.find(n->id->id)->second->custom_type;
    if (arg_class != nullptr) {
        if (table->classes.find(arg_class) == table->classes.end()) {
            std::string err = "Line " + std::to_string(n->location.first_line)
                + ", column " + std::to_string(n->location.first_column) +
                ": Class " + arg_class->String() + " wasn't declared";
            errors.push_back(err);
        }
    }
}
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
    methodInfo = table->classes.find(classInfo->name)->second->methods.find(n->id->id)->second;
    for (auto & arg : *n->args->arguments) {
        arg->Accept(this);
    }
  for (auto & statement : *n->statements->statements) {
    statement->Accept(this);
  }

  n->exp->Accept(this);
  TypeInfo exp = typeInfo;
  if (methodInfo->returnType == "custom" && table->classes.find(methodInfo->customReturnType) == table->classes.end()) {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Class " + methodInfo->customReturnType->String() + " wasn't declared";
      errors.push_back(err);
  }
  if ((exp.type.compare(methodInfo->returnType)) ||
    (exp.name != nullptr && methodInfo->customReturnType != nullptr && exp.name != methodInfo->customReturnType)) {
      std::string err = "Line " + std::to_string(n->location.first_line)
          + ", column " + std::to_string(n->location.first_column) +
          ": Methods must return declared type";
      errors.push_back(err);
  }
}

void TypeChecker::visit(const ClassDeclaration *n) {}

void TypeChecker::visit(const ASTClassDeclaration *n) {
    classInfo = table->classes.find(n->i1->id)->second;
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

  for (auto & class_ : table->classes) {
      Symbol* curr_parent_name = class_.second->par_name;
      while (curr_parent_name != nullptr) {
          if (curr_parent_name == class_.first) {
              std::string err = "Line " + std::to_string(class_.second->location.first_line)
                  + ", column " + std::to_string(class_.second->location.first_column) +
                  ": Class has cyclic inheritance with base defined at line "
                  + std::to_string(table->classes.find(curr_parent_name)->second->location.first_line);
              errors.push_back(err);
              break;
          }
          curr_parent_name = table->classes.find(curr_parent_name)->second->par_name;
      }
  }
}
