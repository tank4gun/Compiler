//
// Created by daniil on 27.10.18.
//
#pragma once
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


//ASTClassDeclarations::ASTClassDeclarations(std::vector<ClassDeclaration *> classes) : classes(classes) {}
//
//char* ASTClassDeclarations::Name() const {
//    char* name = new char[19];
//    strcpy(name, "ASTClassDeclarations");
//    return name;
//}
//
//void ASTClassDeclarations::Accept(IVisitor *v) const {
//    v->visit(this);
//}


//ASTVarDeclarations::ASTVarDeclarations(std::vector<IVarDeclaration *> vars) : vars(vars) {}
//
//char* ASTVarDeclarations::Name() const {
//    char* name = new char[18];
//    strcpy(name, "ASTVarDeclarations");
//    return name;
//}
//
//void ASTVarDeclarations::Accept(IVisitor *v) const {
//    v->visit(this);
//}


//ASTMethodDeclarations::ASTMethodDeclarations(std::vector<IMethodDeclaration *> methods) : methods(methods) {}
//
//char* ASTMethodDeclarations::Name() const {
//    char* name = new char[21];
//    strcpy(name, "ASTMethodDeclarations");
//    return name;
//}
//
//void ASTMethodDeclarations::Accept(IVisitor *v) const {
//    v->visit(this);
//}


//ASTStatementDeclarations::ASTStatementDeclarations(std::vector<IStatement *> statements) : statements(statements) {}
//
//char* ASTStatementDeclarations::Name() const {
//    char* name = new char[24];
//    strcpy(name, "ASTStatementDeclarations");
//    return name;
//}
//
//void ASTStatementDeclarations::Accept(IVisitor *v) const {
//    v->visit(this);
//}


//ASTExpressionDeclarations::ASTExpressionDeclarations(std::vector<IExp *> expressions) : expressions(expressions) {}
//
//char* ASTExpressionDeclarations::Name() const {
//    char* name = new char[25];
//    strcpy(name, "ASTExpressionDeclarations");
//    return name;
//}
//
//void ASTExpressionDeclarations::Accept(IVisitor *v) const {
//    v->visit(this);
//}
//

//ASTArgumentDeclarations::ASTArgumentDeclarations(std::vector<IArgument *> arguments) : arguments(arguments) {}
//
//char* ASTArgumentDeclarations::Name() const {
//    char* name = new char[23];
//    strcpy(name, "ASTArgumentDeclarations");
//    return name;
//}
//
//void ASTArgumentDeclarations::Accept(IVisitor *v) const {
//    v->visit(this);
//}


//ASTMethodDeclaration::ASTMethodDeclaration(IType *type,
//                                           IIdentifier *id,
//                                           ASTArgumentDeclarations *args,
//                                           ASTVarDeclarations *vars,
//                                           ASTStatementDeclarations *statements,
//                                           IExp *exp) :
//    type(type), id(id), args(args), vars(vars), statements(statements), exp(exp)
//{}
//
//void ASTMethodDeclaration::Accept(IVisitor *v) const {
//    v->visit(this);
//}
//
//char* ASTMethodDeclaration::Name() const {
//    char* name = new char[20];
//    strcpy(name, "ASTMethodDeclarations");
//    return name;
//}

//ASTCallMethodExp::ASTCallMethodExp(IExp* e1, IIdentifier* i1, ASTExpressionDeclarations* e2) : e1(e1), i1(i1), e2(e2) {};
//
//void ASTCallMethodExp::Accept(IVisitor *v) const {
//    v->visit(this);
//}
//
//char* ASTCallMethodExp::Name() const {
//    char* name = new char[15];
//    strcpy(name, "ASTCallMethodExp");
//    return name;
//}
