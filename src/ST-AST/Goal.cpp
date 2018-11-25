#include "Goal.h"
#include <cassert>

Goal::Goal(IClass *mainClass, IListDeclaration *classes, LocStruct location): IBase(location), mainClass(mainClass), classes(classes) {
    assert(mainClass != nullptr);
    assert(classes != nullptr);
}

void Goal::Accept(IVisitor *v) const {
//    v->visit(this);
}

char* Goal::Name() const {
    return const_cast<char *>("Goal");
}

ASTGoal::ASTGoal(IClass *mainClass, ASTClassDeclarations *classes, LocStruct location): IBase(location), mainClass(mainClass), classes(classes) {
    assert(mainClass != nullptr);
    assert(classes != nullptr);
}

void ASTGoal::Accept(IVisitor *v) const {
//    v->visit(this);
}

char* ASTGoal::Name() const {
    return const_cast<char *>("ASTGoal");
}