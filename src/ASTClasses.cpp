//
// Created by daniil on 27.10.18.
//
#include <stdio.h>
#include <string.h>
#include <vector>
#include "ASTClasses.h"
#include "IVisitor.h"
#include "Statements.h"
#include "Expressions.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "Statements.h"
#include "Expressions.h"


ASTClassDeclarations::ASTClassDeclarations(std::vector<ClassDeclaration *> classes) : classes(classes) {}

char* ASTClassDeclarations::Name() const {
    char* name = new char[19];
    strcpy(name, "ASTClassDeclarations");
    return name;
}

void ASTClassDeclarations::Accept(IVisitor *v) const {
    v->visit(this);
}


ASTVarDeclarations::ASTVarDeclarations(std::vector<VarDeclaration *> vars) : vars(vars) {}

char* ASTVarDeclarations::Name() const {
    char* name = new char[18];
    strcpy(name, "ASTVarDeclarations");
    return name;
}

void ASTVarDeclarations::Accept(IVisitor *v) const {
    v->visit(this);
}


ASTMethodDeclarations::ASTMethodDeclarations(std::vector<MethodDeclaration *> methods) : methods(methods) {}

char* ASTMethodDeclarations::Name() const {
    char* name = new char[21];
    strcpy(name, "ASTMethodDeclarations");
    return name;
}

void ASTMethodDeclarations::Accept(IVisitor *v) const {
    v->visit(this);
}


ASTStatementDeclarations::ASTStatementDeclarations(std::vector<IStatement *> statements) : statements(statements) {}

char* ASTStatementDeclarations::Name() const {
    char* name = new char[24];
    strcpy(name, "ASTStatementDeclarations");
    return name;
}

void ASTStatementDeclarations::Accept(IVisitor *v) const {
    v->visit(this);
}


ASTExpressionDeclarations::ASTExpressionDeclarations(std::vector<IExp *> expressions) : expressions(expressions) {}

char* ASTExpressionDeclarations::Name() const {
    char* name = new char[25];
    strcpy(name, "ASTExpressionDeclarations");
    return name;
}

void ASTExpressionDeclarations::Accept(IVisitor *v) const {
    v->visit(this);
}