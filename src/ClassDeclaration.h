#pragma once
#include "Identifiers.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "IVisitor.h"

class VarDeclarationsList;
class MethodDeclarationsList;
class IStatement;

class Extends {
  public:
    Extends();
    explicit Extends(IIdentifier *id);
    void Accept(IVisitor *v) const;
    char *Name() const;

    IIdentifier *id;
};

class ClassDeclaration {
  public:
    ClassDeclaration(IIdentifier* i1, Extends* ext, VarDeclarationsList* v1, MethodDeclarationsList* m1);
    void Accept(IVisitor* v) const;
    char* Name() const;

    IIdentifier* i1;
    Extends* ext;
    VarDeclarationsList* vars;
    MethodDeclarationsList* methods;
};

class MainClass {
  public:
    MainClass(IIdentifier *id1, IIdentifier *id2, IStatement *statement);
    void Accept(IVisitor* v) const;
    char* Name() const;

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
