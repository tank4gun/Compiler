#include "Goal.h"

Goal::Goal(IClass *mainClass, IClass *classes): mainClass(mainClass), classes(classes) {}

void Goal::Accept(IVisitor *v) const {
    v->visit(this);
}

char* Goal::Name() const {
    return const_cast<char *>("Goal");
}
