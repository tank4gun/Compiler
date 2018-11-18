#include <utility>

#include "ClassDeclaration.h"

ClassDeclaration::ClassDeclaration(IIdentifier *i1,
                                   IClass *ext,
                                   IListDeclaration *v1,
                                   IListDeclaration *m1) :
    i1(i1), ext(ext), vars(v1), methods(m1)
{}

void ClassDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}

char* ClassDeclaration::Name() const {
    return const_cast<char *>("ClassDeclaration");
}

MainClass::MainClass(IIdentifier *id1, IIdentifier *id2, IStatement *statement): id1(id1), id2(id2), statement(statement) {}

void MainClass::Accept(IVisitor *v) const {
    v->visit(this);
}

char* MainClass::Name() const {
    return const_cast<char *>("MainClass");
}
ClassDeclarationsList::ClassDeclarationsList() = default;
ClassDeclarationsList::ClassDeclarationsList(IClass *class_val): class_val(class_val) {}
ClassDeclarationsList::ClassDeclarationsList(IClass *class_val, ClassDeclarationsList *class_next): class_val(class_val), class_next(class_next) {}
void ClassDeclarationsList::Accept(IVisitor *v) const {
    v->visit(this);
}
char *ClassDeclarationsList::Name() const {
    return const_cast<char *>("ClassDeclarationsList");
}
Extends::Extends(IIdentifier *id): id(id) {}
void Extends::Accept(IVisitor *v) const {
    v->visit(this);
}
char *Extends::Name() const {
    return const_cast<char *>("Extends");
}
Extends::Extends(): id(nullptr) {}

ASTClassDeclarations::ASTClassDeclarations(std::vector<std::unique_ptr<IClass>>* classes) : classes(classes) {}

char* ASTClassDeclarations::Name() const {
    return const_cast<char *>("ASTClassDeclarations");
}

void ASTClassDeclarations::Accept(IVisitor *v) const {
    v->visit(this);
}
