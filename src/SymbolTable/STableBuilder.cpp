//
// Created by elena on 18.11.18.
//

#include "STableBuilder.h"

STableBuilder::STableBuilder(): table(new Table()), classInfo(nullptr), variableInfo(nullptr), methodInfo(nullptr) {
}

void STableBuilder::visit(std::unique_ptr<Goal> &n) {
    n->mainClass->Accept(this);
    n->classes->Accept(this);
}

void STableBuilder::visit(const ASTClassDeclarations *n) {
    for (auto & classe : *(n->classes)) {
        classe->Accept(this);
    }
}

void STableBuilder::visit(const ASTMethodsList *n) {
    for (auto & method : *(n->methods)) {
        method->Accept(this);
    }
}

void STableBuilder::visit(const ASTMethodDeclaration *n) {
    methodInfo = new MethodInfo();
    methodInfo->return_type = n->type;
    methodInfo->name = Symbol(n->id->id);

    n->args->Accept(this);
    n->vars->Accept(this);

    // Check return type

    classInfo[methodInfo->name] = methodInfo;
    methodInfo = 0;
}

void STableBuilder::visit(const ASTArgumentsList *n) {
    for (auto & arg_decl : *(n->arguments)) {
        arg_decl->Accept(this);
    }
}

void STableBuilder::visit(const ASTVarDeclarations *n) {
    for (auto & var_decl : *(n->vars)) {
        var_decl->Accept(this);
    }
}

void STableBuilder::visit(const Argument *n) {
    variableInfo = new VariableInfo();
    variableInfo->type = n->type;
    variableInfo->symbol = n->id->Name();
    // Check that this arg is already exist in current method
    methodInfo->args[variableInfo->symbol] = variableInfo;
}

void STableBuilder::visit(const VarDeclaration *n) {
    variableInfo = new VariableInfo();
    variableInfo->type = n->type;
    variableInfo->symbol = n->id->Name();
    // Check
    if (methodInfo != 0) {
        methodInfo[variableInfo->symbol] = variableInfo;
    } else {
        classInfo[variableInfo->symbol] = variableInfo;
    }
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

void STableBuilder::visit(const Identifier *n) {}


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

void STableBuilder::visit(const Argument *n) {}
void STableBuilder::visit(const ArgumentsList *n) {}
void STableBuilder::visit(const MethodDeclaration *n) {}
void STableBuilder::visit(const MethodDeclarationsList *n) {}


// for VarDeclaration.h

void STableBuilder::visit(const VarDeclaration *n) {}
void STableBuilder::visit(const VarDeclarationsList *n) {}


// for ClassDeclaration.h

void STableBuilder::visit(const ClassDeclaration *n) {}
void STableBuilder::visit(const MainClass *n) {}
void STableBuilder::visit(const ClassDeclarationsList *n) {}
void STableBuilder::visit(const Extends *n) {}

// for ASTClasses.h

void STableBuilder::visit(const ASTStatementsList* n) {}
void STableBuilder::visit(const ASTExpressionDeclarations* n) {}
void STableBuilder::visit(const ASTCallMethodExp* n) {}
void STableBuilder::visit(const ASTBraceStatement* n) {}
