#pragma once
#include "Identifiers.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "IVisitor.h"

class VarDeclarationsList;
class MethodDeclarationsList;
class IStatement;

class ClassDeclaration {
  public:
    ClassDeclaration(IIdentifier* i1, IIdentifier* i2, VarDeclarationsList* v1, MethodDeclarationsList* m1);
    virtual void Accept(IVisitor* v) const = 0;
    virtual char* Name() const = 0;

    IIdentifier* i1;
    IIdentifier* i2;
    VarDeclarationsList* vars;
    MethodDeclarationsList* methods;
};

class MainClass {
  public:
    MainClass(IIdentifier *id1, IIdentifier *id2, IStatement *statement);
    virtual void Accept(IVisitor* v) const = 0;
    virtual char* Name() const = 0;

    IIdentifier *id1;
    IIdentifier *id2;
    IStatement *statement;
};

class ClassDeclarationsList {
  public:
    ClassDeclarationsList();
    explicit ClassDeclarationsList(ClassDeclaration *class_val);
    ClassDeclarationsList(ClassDeclaration *class_val, ClassDeclarationsList *class_next);

    void Accept(IVisitor *v) const;

    char *Name() const;

    const ClassDeclaration *class_val;
    const ClassDeclarationsList *class_next;
};