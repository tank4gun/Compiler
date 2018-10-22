//
// Created by daniil on 21.10.18.
//
#include <stdio.h>
#include <string.h>
#include "Identifiers.h"


Identifier::Identifier(char* id) : id(id) {}

void Identifier::Accept(IVisitor* v) const override {
    v->visit(this);
}

char* Identifier::Name() const override {
    char* name = new char[10];
    strcpy(name, "Identifier");
    return name;
}