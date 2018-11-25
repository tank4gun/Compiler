//
// Created by elena on 18.11.18.
//

#include <iostream>
#include "STableBuilder.h"

STableBuilder::STableBuilder(): table(new Table()), classInfo(nullptr), variableInfo(nullptr), methodInfo(nullptr) {
    curr_symbol = nullptr;
    isParentExists = false;
}

void STableBuilder::visit(const IndexExp *n) {}
void STableBuilder::visit(const LengthExp *n) {}
void STableBuilder::visit(const CallMethodExp *n) {}
void STableBuilder::visit(const IntExp *n) {}
void STableBuilder::visit(const BooleanExp *n) {}
void STableBuilder::visit(const IdExp *n) {}
void STableBuilder::visit(const ThisExp *n) {}
void STableBuilder::visit(const NewIntExp *n) {}
void STableBuilder::visit(const NewIdExp *n) {}
void STableBuilder::visit(const NotExp *n) {}
void STableBuilder::visit(const ExpList *n) {}
void STableBuilder::visit(const BinOp* n) {}
void STableBuilder::visit(const NewExp *n) {}

// for Identifiers.h

void STableBuilder::visit(const Identifier *n) {
    curr_symbol = n->id;
}

// for Statements.h

void STableBuilder::visit(const IfStatement *n) {}
void STableBuilder::visit(const WhileStatement *n) {}
void STableBuilder::visit(const OutputStatement *n) {}
void STableBuilder::visit(const AssignStatement *n) {}
void STableBuilder::visit(const ArrayAssignStatement *n) {}
void STableBuilder::visit(const StatementsList *n) {}
void STableBuilder::visit(const BraceStatement *n) {}
void STableBuilder::visit(const ReturnStatement *n) {}


// for Types.h

void STableBuilder::visit(const IntArrayType *n) {}
void STableBuilder::visit(const IntType *n) {}
void STableBuilder::visit(const BooleanType *n) {}
void STableBuilder::visit(const IdentifierType *n) {}


// for MethodDeclaration.h

void STableBuilder::visit(const Argument *n) {
    n->id->Accept(this);
    if(methodInfo->args.find(curr_symbol) != methodInfo->args.end()) {
        std::string err = "Line " + std::to_string(n->location.first_line)
            + ", column " + std::to_string(n->location.first_column) +
            ": Argument already exists at line " + std::to_string(n->location.first_line);
        errors.push_back(err);
    }
    variableInfo = new VariableInfo(n->location);
    variableInfo->symbol = curr_symbol;
    variableInfo->type = n->type->Name();
    methodInfo->args[variableInfo->symbol] = variableInfo;
}
void STableBuilder::visit(const ArgumentsList *n) {}

void STableBuilder::visit(const ASTMethodDeclaration *n) {
    n->id->Accept(this);
    methodInfo = new MethodInfo(curr_symbol, n->type.get(), n->location);
    n->args->Accept(this);
    n->vars->Accept(this);

    if (classInfo->methods.find(methodInfo->name) != classInfo->methods.end()) {
        MethodInfo* other = classInfo->methods.find(methodInfo->name)->second;
        if (methodInfo->args.size() == other->args.size()) {
            bool areEqual = true;
            for (auto & arg : methodInfo->args) {
                if (other->args.find(arg.first) == other->args.end()) {
                    areEqual = false;
                    break;
                }
            }
            if (areEqual) {
                std::string err = "Line " + std::to_string(methodInfo->location.first_line) +
                    ", column " + std::to_string(methodInfo->location.first_column) +
                    ": Method has already been declared at line " + std::to_string(other->location.first_line);
                errors.push_back(err);
            }
        }
    }

    classInfo->methods[methodInfo->name] = methodInfo;
    methodInfo = nullptr;
}
void STableBuilder::visit(const MethodDeclaration *n) {}
void STableBuilder::visit(const MethodDeclarationsList *n) {}
void STableBuilder::visit(const ASTMethodsList *n) {
    for (auto & method : *(n->methods)) {
        method->Accept(this);
    }
}
void STableBuilder::visit(const ASTArgumentsList *n) {
    for (auto & arg_decl : *(n->arguments)) {
        arg_decl->Accept(this);
    }
}


// for VarDeclaration.h

void STableBuilder::visit(const VarDeclaration *n) {
    variableInfo = new VariableInfo(n->location);
    variableInfo->type = n->type->Name();
    n->id->Accept(this);
    variableInfo->symbol = curr_symbol;
    if (methodInfo != nullptr) {
        auto dup_in_args = methodInfo->args.find(curr_symbol);
        auto dup_in_vars = methodInfo->vars.find(curr_symbol);
        if (dup_in_args != methodInfo->args.end()) {
            std::string err = "Line " + std::to_string(n->location.first_line) +
                ", column " + std::to_string(n->location.first_column) +
                ": Variable has already been declared in line " + std::to_string(dup_in_args->second->location.first_line);
            errors.push_back(err);
        } else if (dup_in_vars != methodInfo->vars.end()) {
            std::string err = "Line " + std::to_string(n->location.first_line) +
                ", column " + std::to_string(n->location.first_column) +
                ": Variable has already been declared in line " + std::to_string(dup_in_vars->second->location.first_line);
            errors.push_back(err);
        }

        methodInfo->vars[variableInfo->symbol] = variableInfo;
    } else {
        auto dup_in_fields = classInfo->fields.find(variableInfo->symbol);
        if (dup_in_fields != classInfo->fields.end()) {
            std::string err = "Line " + std::to_string(n->location.first_line) +
                ", column " + std::to_string(n->location.first_column) +
                ": Variable has already been declared in line " + std::to_string(dup_in_fields->second->location.first_line);
            errors.push_back(err);
        }
        classInfo->fields[variableInfo->symbol] = variableInfo;
    }
}
void STableBuilder::visit(const VarDeclarationsList *n) {}
void STableBuilder::visit(const ASTVarDeclarations *n) {
    for (auto & var_decl : *(n->vars)) {
        var_decl->Accept(this);
    }
}

//for Goal.h
void STableBuilder::visit(std::unique_ptr<ASTGoal> &n) {
    n->mainClass->Accept(this);
    n->classes->Accept(this);
    for (auto & classe : table->classes) {
        if (classe.second->par_name == nullptr) {
            continue;
        }
        if (classe.second->par_name == classe.second->name) {
            std::string err = "Line " + std::to_string(classe.second->location.first_line) +
                ", column " + std::to_string(classe.second->location.first_column) +
                ": Class was inherited from itself";
            errors.push_back(err);
        }
        bool parentFound = false;
        for (auto & sec_classe : table->classes) {
            if (classe.second->par_name == sec_classe.first) {
                for (auto & var : classe.second->fields) {
                    auto dup_in_fields = sec_classe.second->fields.find(var.first);
                    if (dup_in_fields != sec_classe.second->fields.end()) {
                        std::string err = "Line " + std::to_string(var.second->location.first_line) +
                            ", column " + std::to_string(var.second->location.first_column) +
                            ": Variable has already been declared in line " + std::to_string(dup_in_fields->second->location.first_line);
                        errors.push_back(err);
                    }
                }
                for (auto & method : classe.second->methods) {
                    auto dup_in_methods = sec_classe.second->methods.find(method.first);
                    if (dup_in_methods != sec_classe.second->methods.end()) {
                        std::string err = "Line " + std::to_string(method.second->location.first_line) +
                            ", column " + std::to_string(method.second->location.first_column) +
                            ": Method has already been declared in line " + std::to_string(dup_in_methods->second->location.first_line);
                        errors.push_back(err);
                    }
                }
                parentFound = true;
            }
        }
        if (!parentFound) {
            std::string err = "Line " + std::to_string(classe.second->location.first_line) +
                ", column " + std::to_string(classe.second->location.first_column) +
                ": Base class " + classe.second->par_name->String() + " has not been declared";
            errors.push_back(err);
        }
    }
}

void STableBuilder::visit(std::unique_ptr<Goal> &n) {}

// for ClassDeclaration.h

void STableBuilder::visit(const ASTClassDeclarations *n) {
    for (auto &classe : *(n->classes)) {
        classe->Accept(this);
    }
}
void STableBuilder::visit(const ASTClassDeclaration *n) {
    n->i1->Accept(this);
    auto dup_class = table->classes.find(curr_symbol);
    if (dup_class != table->classes.end()) {
        std::string err = "Line " + std::to_string(n->location.first_line) +
            ", column " + std::to_string(n->location.first_column) +
            ": Class has already been declared at line " + std::to_string(dup_class->second->location.first_line);
        errors.push_back(err);
    }
    classInfo = new ClassInfo(n->location);
    classInfo->name = curr_symbol;
    n->ext->Accept(this);
    if (isParentExists) {
        classInfo->par_name = curr_symbol;
        isParentExists = false;
    } else {
        classInfo->par_name = nullptr;
    }
    table->classes[classInfo->name] = classInfo;

    n->vars->Accept(this);
    n->methods->Accept(this);
}
void STableBuilder::visit(const ClassDeclaration *n) {}
void STableBuilder::visit(const MainClass *n) {
    n->id1->Accept(this);
    auto dup_class = table->classes.find(curr_symbol);
    if (dup_class != table->classes.end()) {
        std::string err = "Line " + std::to_string(n->location.first_line) +
            ", column " + std::to_string(n->location.first_column) +
            ": Class has already been declared at line " + std::to_string(dup_class->second->location.first_line);
        errors.push_back(err);
    }
    classInfo = new ClassInfo(n->location);
    classInfo->name = curr_symbol;
    classInfo->par_name = nullptr;
    table->classes[classInfo->name] = classInfo;
    n->id2->Accept(this);
    methodInfo = new MethodInfo(curr_symbol, nullptr, n->location);
    classInfo->methods[curr_symbol] = methodInfo;
    table->classes[classInfo->name] = classInfo;
}
void STableBuilder::visit(const ClassDeclarationsList *n) {}
void STableBuilder::visit(const Extends *n) {
    if (n->id != nullptr) {
        n->id->Accept(this);
        isParentExists = true;
    }
}

// for ASTClasses.h

void STableBuilder::visit(const ASTStatementsList* n) {}
void STableBuilder::visit(const ASTExpressionDeclarations* n) {}
void STableBuilder::visit(const ASTCallMethodExp* n) {}
void STableBuilder::visit(const ASTBraceStatement* n) {}
void STableBuilder::printErrors() {
    if (errors.empty()) {
        std::cout << "No errors found\n";
        return;
    }
    for (const auto &err : errors) {
        std::cout << err << std::endl;
    }
}

