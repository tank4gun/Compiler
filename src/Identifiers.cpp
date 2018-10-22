//
// Created by daniil on 21.10.18.
//
#include <stdio.h>
#include <string.h>
#include "Identifiers.h"


class Identifier : IIdentifier {
  public:
    Identifier(char* id) : id(id) {}

    void Accept(IVisitor* v) const override {
        v->visit(this);
    }

    char* Name() const override {
        char* name = new char[10];
        strcpy(name, "Identifier");
        return name;
    }

    const char* id;
};