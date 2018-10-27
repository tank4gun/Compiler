//
// Created by daniil on 27.10.18.
//
#pragma once
#include <vector>
#include "ClassDeclaration.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "Statements.h"
#include "Expressions.h"

class ClassDeclaration;

class ASTClassDeclarations {
  public:
    ASTClassDeclarations(std::vector<ClassDeclaration*> classes);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::vector<ClassDeclaration*> classes;
};


class ASTVarDeclarations {
  public:
    ASTVarDeclarations(std::vector<IVarDeclaration*> vars);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::vector<IVarDeclaration*> vars;
};


class ASTMethodDeclarations {
  public:
    ASTMethodDeclarations(std::vector<IMethodDeclaration*> methods);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::vector<IMethodDeclaration*> methods;
};


class ASTStatementDeclarations {
  public:
    ASTStatementDeclarations(std::vector<IStatement*> statements);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::vector<IStatement*> statements;
};


class ASTExpressionDeclarations {
  public:
    ASTExpressionDeclarations(std::vector<IExp*> expressions);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::vector<IExp*> expressions;
};


class ASTArgumentDeclarations {
  public:
    ASTArgumentDeclarations(std::vector<IArgument*> arguments);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::vector<IArgument*> arguments;
};


class ASTMethodDeclaration : IMethodDeclaration{
  public:
    ASTMethodDeclaration(IType* type, IIdentifier* id, ASTArgumentDeclarations* args, ASTVarDeclarations* vars, ASTStatementDeclarations* statements, IExp* exp);
    void Accept(IVisitor *v) const;
    char* Name() const;

    IType *type;
    IIdentifier *id;
    ASTArgumentDeclarations *args;
    ASTVarDeclarations *vars;
    ASTStatementDeclarations *statements;
    IExp *exp;
};

#ifndef MINIJAVA_ASTCLASSDECLARATION_H
#define MINIJAVA_ASTCLASSDECLARATION_H

#endif //MINIJAVA_ASTCLASSDECLARATION_H
