#pragma once
#include "Identifiers.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "IVisitor.h"
#include "ListDeclaration.h"
#include "IBase.h"
#include "YYLTYPE_struct.h"
#include <memory>

class VarDeclarationsList;
class MethodDeclarationsList;
class IStatement;
class IMethodDeclaration;

class IClass : public IBase {
  public:
    explicit IClass(YYLTYPE location) : IBase(location) {}
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class Extends : public IClass {
  public:
    Extends(YYLTYPE location);
    Extends(IIdentifier *id, YYLTYPE location);
    void Accept(IVisitor *v) const override;
    char *Name() const override;

    std::unique_ptr<IIdentifier> id;
};

class ClassDeclaration : public IClass {
  public:
    ClassDeclaration(IIdentifier* i1, IClass* ext, IListDeclaration* v1, IListDeclaration* m1, YYLTYPE location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<IIdentifier> i1;
    std::unique_ptr<IClass> ext;
    std::unique_ptr<IListDeclaration> vars;
    std::unique_ptr<IListDeclaration> methods;
};

class MainClass : public IClass {
  public:
    MainClass(IIdentifier *id1, IIdentifier *id2, IStatement *statement, YYLTYPE location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<IIdentifier> id1;
    std::unique_ptr<IIdentifier> id2;
    std::unique_ptr<IStatement> statement;
};

class ClassDeclarationsList : public IListDeclaration {
  public:
    explicit ClassDeclarationsList(YYLTYPE location);
    ClassDeclarationsList(IClass *class_val, YYLTYPE location);
    ClassDeclarationsList(IClass *class_val, ClassDeclarationsList *class_next, YYLTYPE location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IClass> class_val;
    ClassDeclarationsList* class_next;
};

class ASTClassDeclarations : public IListDeclaration {
  public:
    ASTClassDeclarations(std::vector<std::unique_ptr<IClass>>* classes, YYLTYPE location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<std::vector<std::unique_ptr<IClass>>> classes;
};
