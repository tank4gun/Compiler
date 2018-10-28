#include "VarDeclaration.h"

VarDeclaration::VarDeclaration(IType *type, IIdentifier *id): type(type), id(id) {}

void VarDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}

char* VarDeclaration::Name() const {
    char * name = new char[14];
    strcpy(name, "VarDeclaration");
    return name;
}

VarDeclarationsList::VarDeclarationsList() {}
VarDeclarationsList::VarDeclarationsList(IVarDeclaration *var_val): var_val(var_val) {}
VarDeclarationsList::VarDeclarationsList(IVarDeclaration *var_val, VarDeclarationsList *var_next): var_val(var_val), var_next(var_next) {}

void VarDeclarationsList::Accept(IVisitor *v) const {
    v->visit(this);
}

char* VarDeclarationsList::Name() const {
    char *name = new char[18];
    strcpy(name, "VarDeclarationsList");
    return name;
}

ASTVarDeclarations::ASTVarDeclarations(std::vector<IVarDeclaration *> vars) : vars(vars) {}

char* ASTVarDeclarations::Name() const {
    char* name = new char[18];
    strcpy(name, "ASTVarDeclarations");
    return name;
}

void ASTVarDeclarations::Accept(IVisitor *v) const {
    v->visit(this);
}
