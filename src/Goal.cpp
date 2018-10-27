#include "Goal.h"

Goal::Goal(MainClass *mainClass, ClassDeclarationsList *classes): mainClass(mainClass), classes(classes) {}

void Goal::Accept(IVisitor *v) const {
    v->visit(this);
}

char* Goal::Name() const {
    char* name = new char[4];
    strcpy(name, "Goal");
    return name;
}