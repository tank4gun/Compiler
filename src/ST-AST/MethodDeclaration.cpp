//
// Created by daniil on 22.10.18.
//
#include <cassert>
#include "MethodDeclaration.h"

Argument::Argument(IType *type, Identifier *id, LocStruct location) : IArgument(location), type(type), id(id) {
    assert(type != nullptr);
    assert(id != nullptr);
}
void Argument::Accept(IVisitor *v) const {
    v->visit(this);
}
char *Argument::Name() const {
    return const_cast<char *>("Argument");
}
ArgumentsList::ArgumentsList(IArgument *var_val, LocStruct location) : IListDeclaration(location), var_val(var_val) {}
ArgumentsList::ArgumentsList(IArgument *var_val, ArgumentsList *var_next, LocStruct location) : IListDeclaration(location), var_val(var_val), var_next(var_next) {}
ArgumentsList::ArgumentsList(LocStruct location) : IListDeclaration(location), var_val(nullptr), var_next(nullptr) {}

void ArgumentsList::Accept(IVisitor *v) const {
    v->visit(this);
}
char *ArgumentsList::Name() const {
    return const_cast<char *>("ArgumentsList");
}

MethodDeclaration::MethodDeclaration(IType *type,
                                     Identifier *id,
                                     ArgumentsList *args,
                                     VarDeclarationsList *vars,
                                     StatementsList *statements,
                                     ReturnStatement *exp,
                                     LocStruct location) :
    IMethodDeclaration(location), type(type), id(id), args(args), vars(vars), statements(statements), exp(exp) {

    assert(type != nullptr);
    assert(id != nullptr);
    assert(args != nullptr);
    assert(vars != nullptr);
    assert(statements != nullptr);
    assert(exp != nullptr);

}
void MethodDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}
char *MethodDeclaration::Name() const {
    return const_cast<char *>("MethodDeclaration");
}
MethodDeclarationsList::MethodDeclarationsList(LocStruct location)
    : IListDeclaration(location), method_val(nullptr), method_next(nullptr) {}
MethodDeclarationsList::MethodDeclarationsList(IMethodDeclaration *method_val, LocStruct location)
    : IListDeclaration(location), method_val(method_val) {}
MethodDeclarationsList::MethodDeclarationsList(IMethodDeclaration *method_val,
                                               MethodDeclarationsList *method_next,
                                               LocStruct location)
    : IListDeclaration(location), method_val(method_val), method_next(method_next) {}

void MethodDeclarationsList::Accept(IVisitor *v) const {
    v->visit(this);
}
char *MethodDeclarationsList::Name() const {
    return const_cast<char *>("MethodDeclarationsList");
}

ASTMethodsList::ASTMethodsList(std::vector<std::unique_ptr<IMethodDeclaration>>* methods, LocStruct location) : IListDeclaration(location), methods(methods) {}

char* ASTMethodsList::Name() const {
    return const_cast<char *>("ASTMethodsList");
}

void ASTMethodsList::Accept(IVisitor *v) const {
    v->visit(this);
}

ASTMethodDeclaration::ASTMethodDeclaration(IType *type,
                                           Identifier *id,
                                           ASTArgumentsList *args,
                                           ASTVarDeclarations *vars,
                                           ASTStatementsList *statements,
                                           IStatement *exp,
                                           LocStruct location) :
    IMethodDeclaration(location), type(type), id(id), args(args), vars(vars), statements(statements), exp(exp) {

    assert(type != nullptr);
    assert(id != nullptr);
    assert(args != nullptr);
    assert(vars != nullptr);
    assert(statements != nullptr);
    assert(exp != nullptr);
}

void ASTMethodDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}

char* ASTMethodDeclaration::Name() const {
    return const_cast<char *>("ASTMethodDeclaration");
}


ASTArgumentsList::ASTArgumentsList(std::vector<std::unique_ptr<IArgument>>* arguments, LocStruct location) : IListDeclaration(location), arguments(arguments) {}

char* ASTArgumentsList::Name() const {
    return const_cast<char *>("ASTArgumentsList");
}

void ASTArgumentsList::Accept(IVisitor *v) const {
    v->visit(this);
}
