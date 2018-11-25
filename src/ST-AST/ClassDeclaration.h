#pragma once
#include "Identifiers.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "IVisitor.h"
#include "ListDeclaration.h"
#include "IBase.h"
#include "LocStruct.h"
#include <memory>

class VarDeclarationsList;
class MethodDeclarationsList;
class ASTMethodsList;
class IStatement;
class IMethodDeclaration;

class IClass : public IBase {
  public:
    explicit IClass(LocStruct location) : IBase(location) {}
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class Extends : public IClass {
  public:
    Extends(LocStruct location);
    Extends(Identifier *id, LocStruct location);
    void Accept(IVisitor *v) const override;
    char *Name() const override;

    std::unique_ptr<Identifier> id;
};

class ClassDeclaration : public IClass {
  public:
    ClassDeclaration(Identifier* i1, IClass* ext, IListDeclaration* v1, IListDeclaration* m1, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<Identifier> i1;
    std::unique_ptr<IClass> ext;
    std::unique_ptr<IListDeclaration> vars;
    std::unique_ptr<IListDeclaration> methods;
};

class ASTClassDeclaration : public IClass {
  public:
    ASTClassDeclaration(Identifier* i1, IClass* ext, ASTVarDeclarations* v1, ASTMethodsList* m1, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<Identifier> i1;
    std::unique_ptr<IClass> ext;
    std::unique_ptr<ASTVarDeclarations> vars;
    std::unique_ptr<ASTMethodsList> methods;
};

class MainClass : public IClass {
  public:
    MainClass(Identifier *id1, Identifier *id2, IStatement *statement, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<Identifier> id1;
    std::unique_ptr<Identifier> id2;
    std::unique_ptr<IStatement> statement;
};

class ClassDeclarationsList : public IListDeclaration {
  public:
    explicit ClassDeclarationsList(LocStruct location);
    ClassDeclarationsList(IClass *class_val, LocStruct location);
    ClassDeclarationsList(IClass *class_val, ClassDeclarationsList *class_next, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IClass> class_val;
    ClassDeclarationsList* class_next;
};

class ASTClassDeclarations : public IListDeclaration {
  public:
    ASTClassDeclarations(std::vector<std::unique_ptr<IClass>>* classes, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;

    std::unique_ptr<std::vector<std::unique_ptr<IClass>>> classes;
};
