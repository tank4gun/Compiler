#include "ClassDeclaration.h"

ClassDeclaration::ClassDeclaration(IIdentifier *i1,
                                   Extends *ext,
                                   VarDeclarationsList *v1,
                                   MethodDeclarationsList *m1) :
    i1(i1), ext(ext), vars(v1), methods(m1)
{}

void ClassDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}

char* ClassDeclaration::Name() const {
    char *name = new char[16];
    strcpy(name, "ClassDeclaration");
    return name;
}

MainClass::MainClass(IIdentifier *id1, IIdentifier *id2, IStatement *statement): id1(id1), id2(id2), statement(statement) {}

void MainClass::Accept(IVisitor *v) const {
    v->visit(this);
}

char* MainClass::Name() const {
    char *name = new char[9];
    strcpy(name, "MainClass");
    return name;
}
ClassDeclarationsList::ClassDeclarationsList() = default;
ClassDeclarationsList::ClassDeclarationsList(ClassDeclaration *class_val): class_val(class_val) {}
ClassDeclarationsList::ClassDeclarationsList(ClassDeclaration *class_val, ClassDeclarationsList *class_next): class_val(class_val), class_next(class_next) {}
void ClassDeclarationsList::Accept(IVisitor *v) const {
    v->visit(this);
}
char *ClassDeclarationsList::Name() const {
    char *name = new char[21];
    strcpy(name, "ClassDeclarationsList");
    return name;
}
Extends::Extends(IIdentifier *id): id(id) {}
void Extends::Accept(IVisitor *v) const {
    v->visit(this);
}
char *Extends::Name() const {
    char *name = new char[7];
    strcpy(name, "Extends");
    return name;
}
Extends::Extends(): id(nullptr) {}
