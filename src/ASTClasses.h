//
// Created by daniil on 27.10.18.
//
#include <vector>
#include "ClassDeclaration.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "Statements.h"
#include "Expressions.h"

class ASTClassDeclarations {
    ASTClassDeclarations(std::vector<ClassDeclaration*> classes);
    virtual void Accept(IVisitor* v) const = 0;
    virtual char* Name() const = 0;

    std::vector<ClassDeclaration*> classes;
};


class ASTVarDeclarations {
    ASTVarDeclarations(std::vector<VarDeclaration*> vars);
    virtual void Accept(IVisitor* v) const = 0;
    virtual char* Name() const = 0;

    std::vector<VarDeclaration*> vars;
};


class ASTMethodDeclarations {
    ASTMethodDeclarations(std::vector<MethodDeclaration*> methods);
    virtual void Accept(IVisitor* v) const = 0;
    virtual char* Name() const = 0;

    std::vector<MethodDeclaration*> methods;
};


class ASTStatementDeclarations {
    ASTStatementDeclarations(std::vector<IStatement*> statements);
    virtual void Accept(IVisitor* v) const = 0;
    virtual char* Name() const = 0;

    std::vector<IStatement*> statements;
};


class ASTExpressionDeclarations {
    ASTExpressionDeclarations(std::vector<IExp*> expressions);
    virtual void Accept(IVisitor* v) const = 0;
    virtual char* Name() const = 0;

    std::vector<IExp*> expressions;
};





#ifndef MINIJAVA_ASTCLASSDECLARATION_H
#define MINIJAVA_ASTCLASSDECLARATION_H

#endif //MINIJAVA_ASTCLASSDECLARATION_H
