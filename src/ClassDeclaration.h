#pragma once
#include "Identifiers.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "IVisitor.h"

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
    void Accept(IVisitor *v) const;
    char *Name() const;

    IIdentifier *id;
};

class ClassDeclaration : public IClass {
  public:
    ClassDeclaration(IIdentifier* i1, IClass* ext, IVarDeclaration* v1, IMethodDeclaration* m1);
    void Accept(IVisitor* v) const;
    char* Name() const;

    IIdentifier* i1;
    IClass* ext;
    IVarDeclaration* vars;
    IMethodDeclaration* methods;
};

class MainClass : public IClass {
  public:
    MainClass(IIdentifier *id1, IIdentifier *id2, IStatement *statement);
    void Accept(IVisitor* v) const;
    char* Name() const;

    IIdentifier *id1;
    IIdentifier *id2;
    IStatement *statement;
};

class ClassDeclarationsList : public IClass {
  public:
    ClassDeclarationsList();
    explicit ClassDeclarationsList(IClass *class_val);
    ClassDeclarationsList(IClass *class_val, ClassDeclarationsList *class_next);

    void Accept(IVisitor *v) const;

    char *Name() const;

    const IClass *class_val;
    const ClassDeclarationsList *class_next;
};

class ASTClassDeclarations : public IClass {
  public:
    ASTClassDeclarations(std::vector<IClass*> classes);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::vector<IClass*> classes;
};
