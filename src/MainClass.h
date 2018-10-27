//
// Created by daniil on 22.10.18.
//
#include "Identifiers.h"
#include "Statements.h"
#include "IVisitor.h"

class MainClass {
    MainClass(IIdentifier* i1, IIdentifier* i2, IStatement* s1);
    virtual void Accept(IVisitor* v) const = 0;
    virtual char* Name() const = 0;

    IIdentifier* i1;
    IIdentifier* i2;
    IStatement* s1;
};

#ifndef MINIJAVA_MAILCLASS_H
#define MINIJAVA_MAILCLASS_H

#endif //MINIJAVA_MAILCLASS_H
