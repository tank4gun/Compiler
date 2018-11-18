#include <cassert>
#include "VarDeclaration.h"

VarDeclaration::VarDeclaration(IType *type, IIdentifier *id): type(type), id(id) {
    assert(type != nullptr);
    assert(id!= nullptr);
}

void VarDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}

char* VarDeclaration::Name() const {
    return const_cast<char *>("VarDeclaration");
}

VarDeclarationsList::VarDeclarationsList() : var_val(nullptr), var_next(nullptr) {}
VarDeclarationsList::VarDeclarationsList(IVarDeclaration *var_val): var_val(var_val) {}
VarDeclarationsList::VarDeclarationsList(IVarDeclaration *var_val, VarDeclarationsList *var_next): var_val(var_val), var_next(var_next) {}

void VarDeclarationsList::Accept(IVisitor *v) const {
    v->visit(this);
}

char* VarDeclarationsList::Name() const {
    return const_cast<char *>("VarDeclarationsList");
}

ASTVarDeclarations::ASTVarDeclarations(std::vector<IVarDeclaration *> vars) : vars(std::move(vars)) {}

char* ASTVarDeclarations::Name() const {
    return const_cast<char *>("ASTVarDeclarations");
}

void ASTVarDeclarations::Accept(IVisitor *v) const {
    v->visit(this);
}
