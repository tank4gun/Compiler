//
// Created by daniil on 22.10.18.
//
#include <stdio.h>
#include <string.h>
#include "MainClass.h"

MainClass::MainClass(IIdentifier *i1, IIdentifier *i2, IStatement *s1) : i1(i1), i2(i2), s1(s1) {}

void MainClass::Accept(IVisitor *v) const {
    v->visit(this);
}

char* MainClass::Name() const {
    char* name = new char[9];
    strcpy(name, "MainClass");
    return name;
}