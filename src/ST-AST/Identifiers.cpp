//
// Created by daniil on 21.10.18.
//
#include "Identifiers.h"

Identifier::Identifier(Symbol* str): id(str){}

void Identifier::Accept(IVisitor* v) const {
    v->visit(this);
}

char* Identifier::Name() const {
    return const_cast<char *>("Identifier");
}