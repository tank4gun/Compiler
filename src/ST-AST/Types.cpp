//
// Created by elena on 27.10.18.
//
#include <cassert>
#include "Types.h"

IntArrayType::IntArrayType(LocStruct location) : IType(location) {}

void IntArrayType::Accept(IVisitor *v) const {
    v->visit(this);
}

char *IntArrayType::Name() const {
    return const_cast<char *>("IntArrayType");
}
BooleanType::BooleanType(LocStruct location) : IType(location) {}

void BooleanType::Accept(IVisitor *v) const {
    v->visit(this);
}
char *BooleanType::Name() const {
    return const_cast<char *>("BooleanType");
}
IntType::IntType(LocStruct location) : IType(location) {}

void IntType::Accept(IVisitor *v) const {
    v->visit(this);
}

char *IntType::Name() const{
    return const_cast<char *>("IntType");
}
IdentifierType::IdentifierType(Identifier* id, LocStruct location): id(id), IType(location) {
    assert(id != nullptr);
}
void IdentifierType::Accept(IVisitor *v) const {
    v->visit(this);
}
char *IdentifierType::Name() const {
    return const_cast<char *>("IdentifierType");
}
