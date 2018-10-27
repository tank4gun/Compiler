//
// Created by daniil on 22.10.18.
//

#include "MethodDeclaration.h"

Argument::Argument(IType *type, IIdentifier *id): type(type), id(id) {}
void Argument::Accept(IVisitor *v) const {
    v->visit(this);
}
char *Argument::Name() const {
    char *name = new char[8];
    strcpy(name, "Argument");
    return name;
}

ArgumentsList::ArgumentsList(IArgument *var_val): var_val(var_val) {}
ArgumentsList::ArgumentsList(IArgument *var_val, ArgumentsList *var_next): var_val(var_val), var_next(var_next) {}
void ArgumentsList::Accept(IVisitor *v) const {
    v->visit(this);
}
char *ArgumentsList::Name() const {
    char *name = new char[13];
    strcpy(name, "ArgumentsList");
    return name;
}
MethodDeclaration::MethodDeclaration(IType *type,
                                     IIdentifier *id,
                                     ArgumentsList *args,
                                     VarDeclarationsList *vars,
                                     StatementsList *statements,
                                     IExp *exp): type(type), id(id), args(args), vars(vars), statements(statements), exp(exp) {

}
void MethodDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}
MethodDeclarationsList::MethodDeclarationsList() = default;
MethodDeclarationsList::MethodDeclarationsList(IMethodDeclaration *method_val): method_val(method_val) {}
MethodDeclarationsList::MethodDeclarationsList(IMethodDeclaration *method_val, MethodDeclarationsList *method_next): method_val(method_val), method_next(method_next) {}
void MethodDeclarationsList::Accept(IVisitor *v) const {
    v->visit(this);
}
char *MethodDeclarationsList::Name() const {
    char *name = new char[22];
    strcpy(name, "MethodDeclarationsList");
    return name;
}