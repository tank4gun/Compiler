//
// Created by daniil on 22.10.18.
//
#include <stdio.h>
#include <string.h>
#include "Goal.h"

Goal::Goal() {}

void Goal::Accept(IVisitor *v) const {
    v->visit(this);
}

char* Goal::Name() const {
    char* name = new char[4];
    strcpy(name, "Goal");
    return name;
}
