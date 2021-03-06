#include <cassert>
#include "VarDeclaration.h"

VarDeclaration::VarDeclaration(IType *type, Identifier *id, LocStruct location) : type(type), id(id), IVarDeclaration(location) {
    assert(type != nullptr);
    assert(id!= nullptr);
}

void VarDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}

char* VarDeclaration::Name() const {
    return const_cast<char *>("VarDeclaration");
}

VarDeclarationsList::VarDeclarationsList(LocStruct location) : var_val(nullptr), var_next(nullptr), IListDeclaration(location) {}
VarDeclarationsList::VarDeclarationsList(IVarDeclaration *var_val, LocStruct location): var_val(var_val), IListDeclaration(location) {}
VarDeclarationsList::VarDeclarationsList(IVarDeclaration *var_val, VarDeclarationsList *var_next, LocStruct location): var_val(var_val), var_next(var_next), IListDeclaration(location) {}

void VarDeclarationsList::Accept(IVisitor *v) const {
    v->visit(this);
}

char* VarDeclarationsList::Name() const {
    return const_cast<char *>("VarDeclarationsList");
}

ASTVarDeclarations::ASTVarDeclarations(std::vector<std::unique_ptr<IVarDeclaration>>* vars, LocStruct location) : vars(vars), IListDeclaration(location) {}

char* ASTVarDeclarations::Name() const {
    return const_cast<char *>("ASTVarDeclarations");
}

void ASTVarDeclarations::Accept(IVisitor *v) const {
    v->visit(this);
}
