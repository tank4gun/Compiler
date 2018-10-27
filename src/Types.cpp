//
// Created by elena on 27.10.18.
//

#include "Types.h"
IntArrayType::IntArrayType() = default;

void IntArrayType::Accept(IVisitor *v) const {
    v->visit(this);
}

char *IntArrayType::Name() const{
    char* name = new char[12];
    strcpy(name, "IntArrayType");
    return name;
}
BooleanType::BooleanType() = default;
void BooleanType::Accept(IVisitor *v) const {
    v->visit(this);
}
char *BooleanType::Name() const{
    char* name = new char[11];
    strcpy(name, "BooleanType");
    return name;
}
IntType::IntType() = default;
void IntType::Accept(IVisitor *v) const {
    v->visit(this);
}

char *IntType::Name() const{
    char* name = new char[7];
    strcpy(name, "IntType");
    return name;
}
IdentifierType::IdentifierType(IIdentifier* id): id(id) {}

void IdentifierType::Accept(IVisitor *v) const {
    v->visit(this);
}
char *IdentifierType::Name() const {
    char *name = new char[14];
    strcpy(name, "IdentifierType");
    return name;
}
