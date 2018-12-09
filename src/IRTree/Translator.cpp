//
// Created by elena on 09.12.18.
//

#include "Translator.h"

// for Expressions.h

void Translator::visit(const IndexExp *n) {
    ///TODO
}
void Translator::visit(const LengthExp *n){
    ///TODO
}
void Translator::visit(const CallMethodExp *n){
    ///TODO
}
void Translator::visit(const IntExp *n){
    ///TODO
}
void Translator::visit(const BooleanExp *n){
    ///TODO
}
void Translator::visit(const IdExp *n){
    ///TODO
}
void Translator::visit(const ThisExp *n){
    ///TODO
}
void Translator::visit(const NewIntExp *n){
    ///TODO
}
void Translator::visit(const NewIdExp *n){
    ///TODO
}
void Translator::visit(const NotExp *n){
    ///TODO
}
void Translator::visit(const ExpList *n){}
void Translator::visit(const BinOp* n){
    ///TODO
}
void Translator::visit(const NewExp *n){}

// for Identifiers.h

void Translator::visit(const Identifier *n){}


// for Statements.h

void Translator::visit(const IfStatement *n){
    ///TODO
}
void Translator::visit(const WhileStatement *n){
    ///TODO
}
void Translator::visit(const OutputStatement *n){
    ///TODO
}
void Translator::visit(const AssignStatement *n){
    ///TODO
}
void Translator::visit(const ArrayAssignStatement *n){
    ///TODO
}
void Translator::visit(const StatementsList *n){}
void Translator::visit(const BraceStatement *n){}
void Translator::visit(const ReturnStatement *n){}


// for Types.h

void Translator::visit(const IntArrayType *n) {}
void Translator::visit(const IntType *n){}
void Translator::visit(const BooleanType *n) {}
void Translator::visit(const IdentifierType *n) {}


// for MethodDeclaration.h

void Translator::visit(const Argument *n) {}
void Translator::visit(const ArgumentsList *n) {}
void Translator::visit(const MethodDeclaration *n) {}
void Translator::visit(const MethodDeclarationsList *n) {}


// for VarDeclaration.h

void Translator::visit(const VarDeclaration *n) {}
void Translator::visit(const VarDeclarationsList *n) {}


// for ClassDeclaration.h

void Translator::visit(const ClassDeclaration *n) {}
void Translator::visit(const MainClass *n) {
    ///TODO
}
void Translator::visit(const ClassDeclarationsList *n) {}
void Translator::visit(const Extends *n) {}


// for Goal.h
void Translator::visit(std::unique_ptr<Goal>& n) {}
void Translator::visit(std::unique_ptr<ASTGoal>& n) {
    n->mainClass->Accept(this);
    for(const auto& classe : *n->classes->classes) {
        classe->Accept(this);
    }

}

// for ASTClasses.h

void Translator::visit(const ASTClassDeclarations *n) {}
void Translator::visit(const ASTClassDeclaration *n) {
    ///TODO
}
void Translator::visit(const ASTVarDeclarations *n) {}
void Translator::visit(const ASTMethodsList* n) {}
void Translator::visit(const ASTStatementsList* n) {}
void Translator::visit(const ASTExpressionDeclarations* n) {}
void Translator::visit(const ASTArgumentsList* n) {}
void Translator::visit(const ASTMethodDeclaration* n) {
    ///TODO
}
void Translator::visit(const ASTCallMethodExp* n) {}
void Translator::visit(const ASTBraceStatement* n) {}