//
// Created by daniil on 22.10.18.
//
#include <stdio.h>
#include <string.h>
#include "ClassDeclaration.h"
#include "IVisitor.h"
#include "Identifiers.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"

ClassDeclaration::ClassDeclaration(IIdentifier *i1,
                                   IIdentifier *i2,
                                   VarDeclarationList *v1,
                                   MethodDeclarationList *m1) :
    i1(i1), i2(i2), v1(v1), m1(m1)
{}

void ClassDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}

char* ClassDeclaration::Name() const {

}