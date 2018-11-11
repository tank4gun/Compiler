#pragma once
#include "Identifiers.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "IVisitor.h"
#include <memory>

class VarDeclarationsList;
class MethodDeclarationsList;
class IStatement;
class IMethodDeclaration;

class IClass {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class Extends : public IClass {
  public:
    Extends();
    explicit Extends(IIdentifier *id);
    void Accept(IVisitor *v) const override;
    char *Name() const override;

    std::unique_ptr<IIdentifier> id;
};

class ClassDeclaration : public IClass {
  public:
    ClassDeclaration(IIdentifier* i1, IClass* ext, IVarDeclaration* v1, IMethodDeclaration* m1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<IIdentifier> i1;
    std::unique_ptr<IClass> ext;
    std::unique_ptr<IVarDeclaration> vars;
    std::unique_ptr<IMethodDeclaration> methods;
};

class MainClass : public IClass {
  public:
    MainClass(IIdentifier *id1, IIdentifier *id2, IStatement *statement);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<IIdentifier> id1;
    std::unique_ptr<IIdentifier> id2;
    std::unique_ptr<IStatement> statement;
};

class ClassDeclarationsList : public IClass {
  public:
    ClassDeclarationsList();
    explicit ClassDeclarationsList(IClass *class_val);
    ClassDeclarationsList(IClass *class_val, ClassDeclarationsList *class_next);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    IClass* class_val;
    ClassDeclarationsList* class_next;
};

class ASTClassDeclarations : public IClass {
  public:
    explicit ASTClassDeclarations(std::vector<IClass*>& classes);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::vector<IClass*> classes;
};
