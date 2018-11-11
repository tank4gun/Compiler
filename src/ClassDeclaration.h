#pragma once
#include "Identifiers.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "IVisitor.h"
#include "ListDeclaration.h"

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

    IIdentifier *id;
};

class ClassDeclaration : public IClass {
  public:
    ClassDeclaration(IIdentifier* i1, IClass* ext, IListDeclaration* v1, IListDeclaration* m1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    IIdentifier* i1;
    IClass* ext;
    IListDeclaration* vars;
    IListDeclaration* methods;
};

class MainClass : public IClass {
  public:
    MainClass(IIdentifier *id1, IIdentifier *id2, IStatement *statement);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    IIdentifier *id1;
    IIdentifier *id2;
    IStatement *statement;
};

class ClassDeclarationsList : public IListDeclaration {
  public:
    ClassDeclarationsList();
    explicit ClassDeclarationsList(IClass *class_val);
    ClassDeclarationsList(IClass *class_val, ClassDeclarationsList *class_next);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    const IClass *class_val;
    const ClassDeclarationsList *class_next;
};

class ASTClassDeclarations : public IListDeclaration {
  public:
    explicit ASTClassDeclarations(std::vector<IClass*>& classes);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::vector<IClass*> classes;
};
