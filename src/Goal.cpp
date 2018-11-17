#include "Goal.h"

Goal::Goal(IClass *mainClass, IListDeclaration *classes): mainClass(mainClass), classes(classes) {
    assert(mainClass != nullptr);
    assert(classes != nullptr);
}

void Goal::Accept(IVisitor *v) const {
//    v->visit(this);
}

char* Goal::Name() const {
    return const_cast<char *>("Goal");
}
