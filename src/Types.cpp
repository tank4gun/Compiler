//
// Created by elena on 27.10.18.
//
#include "Types.h"

IntArrayType::IntArrayType() = default;

void IntArrayType::Accept(IVisitor *v) const {
    v->visit(this);
}

char *IntArrayType::Name() const{
    return const_cast<char *>("IntArrayType");
}
BooleanType::BooleanType() = default;
void BooleanType::Accept(IVisitor *v) const {
    v->visit(this);
}
char *BooleanType::Name() const{
    return const_cast<char *>("BooleanType");
}
IntType::IntType() = default;
void IntType::Accept(IVisitor *v) const {
    v->visit(this);
}

char *IntType::Name() const{
    return const_cast<char *>("IntType");
}
IdentifierType::IdentifierType(IIdentifier* id): id(id) {}

void IdentifierType::Accept(IVisitor *v) const {
    v->visit(this);
}
char *IdentifierType::Name() const {
    return const_cast<char *>("IdentifierType");
}
