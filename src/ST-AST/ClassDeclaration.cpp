#include <utility>
#include <cassert>
#include "ClassDeclaration.h"
#include "StringConverter.h"

ClassDeclaration::ClassDeclaration(IIdentifier *i1,
                                   IClass *ext,
                                   IListDeclaration *v1,
                                   IListDeclaration *m1,
                                   LocStruct location) :
    IClass(location), i1(i1), ext(ext), vars(v1), methods(m1) {
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

MainClass::MainClass(IIdentifier *id1, IIdentifier *id2, IStatement *statement, LocStruct location)
    : IClass(location), id1(id1), id2(new Identifier(StringConverter::getIntern(std::string("main")), location)), statement(statement) {
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
ClassDeclarationsList::ClassDeclarationsList(LocStruct location) : IListDeclaration(location) {}
ClassDeclarationsList::ClassDeclarationsList(IClass *class_val, LocStruct location): IListDeclaration(location), class_val(class_val) {}
ClassDeclarationsList::ClassDeclarationsList(IClass *class_val, ClassDeclarationsList *class_next, LocStruct location): IListDeclaration(location), class_val(class_val), class_next(class_next) {}

void ClassDeclarationsList::Accept(IVisitor *v) const {
    v->visit(this);
}
char *ClassDeclarationsList::Name() const {
    return const_cast<char *>("ClassDeclarationsList");
}

Extends::Extends(IIdentifier *id, LocStruct location): IClass(location), id(id) {}  // 'id' can be nullptr, so no assertion check

Extends::Extends(LocStruct location): IClass(location), id(nullptr) {}

void Extends::Accept(IVisitor *v) const {
    v->visit(this);
}
char *Extends::Name() const {
    return const_cast<char *>("Extends");
}

ASTClassDeclarations::ASTClassDeclarations(std::vector<std::unique_ptr<IClass>>* classes, LocStruct location) : IListDeclaration(location), classes(classes) {}

char* ASTClassDeclarations::Name() const {
    return const_cast<char *>("ASTClassDeclarations");
}

void ASTClassDeclarations::Accept(IVisitor *v) const {
    v->visit(this);
}
