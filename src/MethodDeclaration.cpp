//
// Created by daniil on 22.10.18.
//

#include "MethodDeclaration.h"

Argument::Argument(IType *type, IIdentifier *id): type(type), id(id) {}
void Argument::Accept(IVisitor *v) const {
    v->visit(this);
}
char *Argument::Name() const {
    return const_cast<char *>("Argument");
}

ArgumentsList::ArgumentsList(IArgument *var_val): var_val(var_val) {}
ArgumentsList::ArgumentsList(IArgument *var_val, ArgumentsList *var_next): var_val(var_val), var_next(var_next) {}
void ArgumentsList::Accept(IVisitor *v) const {
    v->visit(this);
}
char *ArgumentsList::Name() const {
    return const_cast<char *>("ArgumentsList");
}
ArgumentsList::ArgumentsList() : var_val(nullptr), var_next(nullptr) {}
MethodDeclaration::MethodDeclaration(IType *type,
                                     IIdentifier *id,
                                     ArgumentsList *args,
                                     VarDeclarationsList *vars,
                                     StatementsList *statements,
                                     ReturnStatement *exp): type(type), id(id), args(args), vars(vars), statements(statements), exp(exp) {

}
void MethodDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}
char *MethodDeclaration::Name() const {
    return const_cast<char *>("MethodDeclaration");
}
MethodDeclarationsList::MethodDeclarationsList() : method_val(nullptr), method_next(nullptr) {}
MethodDeclarationsList::MethodDeclarationsList(IMethodDeclaration *method_val): method_val(method_val) {}
MethodDeclarationsList::MethodDeclarationsList(IMethodDeclaration *method_val, MethodDeclarationsList *method_next): method_val(method_val), method_next(method_next) {}
void MethodDeclarationsList::Accept(IVisitor *v) const {
    v->visit(this);
}
char *MethodDeclarationsList::Name() const {
    return const_cast<char *>("MethodDeclarationsList");
}

ASTMethodsList::ASTMethodsList(std::vector<std::unique_ptr<IMethodDeclaration>>* methods) : methods(methods) {}

char* ASTMethodsList::Name() const {
    return const_cast<char *>("ASTMethodsList");
}

void ASTMethodsList::Accept(IVisitor *v) const {
    v->visit(this);
}


ASTMethodDeclaration::ASTMethodDeclaration(IType *type,
                                           IIdentifier *id,
                                           IListDeclaration *args,
                                           IListDeclaration *vars,
                                           IListDeclaration *statements,
                                           IStatement *exp) :
    type(type), id(id), args(args), vars(vars), statements(statements), exp(exp)
{}

void ASTMethodDeclaration::Accept(IVisitor *v) const {
    v->visit(this);
}

char* ASTMethodDeclaration::Name() const {
    return const_cast<char *>("ASTMethodDeclaration");
}


ASTArgumentsList::ASTArgumentsList(std::vector<std::unique_ptr<IArgument>>* arguments) : arguments(arguments) {}

char* ASTArgumentsList::Name() const {
    return const_cast<char *>("ASTArgumentsList");
}

void ASTArgumentsList::Accept(IVisitor *v) const {
    v->visit(this);
}
