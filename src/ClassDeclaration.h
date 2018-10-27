//
// Created by daniil on 22.10.18.
//
#include "Identifiers.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "IVisitor.h"

class ClassDeclaration {
    ClassDeclaration(IIdentifier* i1, IIdentifier* i2, VarDeclarationList* v1, MethodDeclarationList* m1);
    virtual void Accept(IVisitor* v) const = 0;
    virtual char* Name() const = 0;

    IIdentifier* i1;
    IIdentifier* i2;
    VarDeclarationList* v1;
    MethodDeclarationList* m1;
};

#ifndef MINIJAVA_CLASSDECLARATION_H
#define MINIJAVA_CLASSDECLARATION_H

#endif //MINIJAVA_CLASSDECLARATION_H
