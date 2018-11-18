#include <utility>
#include <cassert>
#include "ClassDeclaration.h"

ClassDeclaration::ClassDeclaration(IIdentifier *i1,
                                   IClass *ext,
                                   IListDeclaration *v1,
                                   IListDeclaration *m1) :
    i1(i1), ext(ext), vars(v1), methods(m1)
{
    assert(i1 != nullptr);
    assert(ext != nullptr);
    assert(v1 != nullptr);
    assert(m1 != nullptr);
}

void ClassDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}

char* ClassDeclaration::Name() const {
    return const_cast<char *>("ClassDeclaration");
}

MainClass::MainClass(IIdentifier *id1, IIdentifier *id2, IStatement *statement): id1(id1), id2(id2), statement(statement) {
    assert(id1 != nullptr);
    assert(id2 != nullptr);
    assert(statement != nullptr);
}

void MainClass::Accept(IVisitor *v) const {
    v->visit(this);
}

char* MainClass::Name() const {
    return const_cast<char *>("MainClass");
}
ClassDeclarationsList::ClassDeclarationsList() = default;
ClassDeclarationsList::ClassDeclarationsList(IClass *class_val): class_val(class_val) {
    assert(class_val != nullptr);
}
ClassDeclarationsList::ClassDeclarationsList(IClass *class_val, ClassDeclarationsList *class_next): class_val(class_val), class_next(class_next) {
    assert(class_val != nullptr);
    assert(class_next!= nullptr);
}
void ClassDeclarationsList::Accept(IVisitor *v) const {
    v->visit(this);
}
char *ClassDeclarationsList::Name() const {
    return const_cast<char *>("ClassDeclarationsList");
}

Extends::Extends(IIdentifier *id): id(id) {}  // 'id' can be nullptr, so no assertion check

Extends::Extends(): id(nullptr) {}

void Extends::Accept(IVisitor *v) const {
    v->visit(this);
}
char *Extends::Name() const {
    return const_cast<char *>("Extends");
}

ASTClassDeclarations::ASTClassDeclarations(std::vector<IClass*>& classes) : classes(classes) {}

char* ASTClassDeclarations::Name() const {
    return const_cast<char *>("ASTClassDeclarations");
}

void ASTClassDeclarations::Accept(IVisitor *v) const {
    v->visit(this);
}
