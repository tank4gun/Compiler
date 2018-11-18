//
// Created by elena on 18.11.18.
//

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
    variableInfo = new VariableInfo();
    variableInfo->type = n->type.get();
    n->id->Accept(this);
    variableInfo->symbol = curr_symbol;
    /// TODO Check that this arg is already exist in current method
    methodInfo->args[variableInfo->symbol] = variableInfo;
}
void STableBuilder::visit(const ArgumentsList *n) {}

void STableBuilder::visit(const ASTMethodDeclaration *n) {
    methodInfo = new MethodInfo();
    methodInfo->returnType = n->type.get();
    n->id->Accept(this);
    methodInfo->name = curr_symbol;

    n->args->Accept(this);
    n->vars->Accept(this);

    // Check return type

    classInfo->methods[methodInfo->name] = methodInfo;
    methodInfo = nullptr;
}
void STableBuilder::visit(const MethodDeclaration *n) {

}
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
    variableInfo = new VariableInfo();
    variableInfo->type = n->type.get();
    n->id->Accept(this);
    variableInfo->symbol = curr_symbol;
    // Check
    if (methodInfo != nullptr) {
        methodInfo->vars[variableInfo->symbol] = variableInfo;
    } else {
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
void STableBuilder::visit(std::unique_ptr<Goal> &n) {
    n->mainClass->Accept(this);
    n->classes->Accept(this);
}


// for ClassDeclaration.h

void STableBuilder::visit(const ASTClassDeclarations *n) {
    for (auto & classe : *(n->classes)) {
        classe->Accept(this);
    }
}
void STableBuilder::visit(const ClassDeclaration *n) {
    n->i1->Accept(this);
    if (table->classes.find(curr_symbol) != table->classes.end()) {
        std::string exc = "Class already exists"; ///TODO COORDS
        errors.push_back(exc);
        return;
    }
    classInfo = new ClassInfo();
    classInfo->name = curr_symbol;
    n->ext->Accept(this);
    if (isParentExists) {
        classInfo->par_name = curr_symbol;
        isParentExists = false;
    }
    table->classes[classInfo->name] = classInfo;

    n->vars->Accept(this);
    n->methods->Accept(this);
}
void STableBuilder::visit(const MainClass *n) {}
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

