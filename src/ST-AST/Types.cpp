//
// Created by elena on 27.10.18.
//
#include <cassert>
#include "Types.h"

IntArrayType::IntArrayType(YYLTYPE location) : IType(location) {}

void IntArrayType::Accept(IVisitor *v) const {
    v->visit(this);
}

char *IntArrayType::Name() const {
    return const_cast<char *>("IntArrayType");
}
BooleanType::BooleanType(YYLTYPE location) : IType(location) {}

void BooleanType::Accept(IVisitor *v) const {
    v->visit(this);
}
char *BooleanType::Name() const {
    return const_cast<char *>("BooleanType");
}
IntType::IntType(YYLTYPE location) : IType(location) {}

void IntType::Accept(IVisitor *v) const {
    v->visit(this);
}

char *IntType::Name() const{
    return const_cast<char *>("IntType");
}
IdentifierType::IdentifierType(IIdentifier* id, YYLTYPE location): id(id), IType(location) {
    assert(id != nullptr);
}
void IdentifierType::Accept(IVisitor *v) const {
    v->visit(this);
}
char *IdentifierType::Name() const {
    return const_cast<char *>("IdentifierType");
}
