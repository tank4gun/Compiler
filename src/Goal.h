#pragma once
#include "IVisitor.h"
#include "ClassDeclaration.h"

class IVisitor;
class MainClass;
class ClassDeclarationsList;

class Goal {
  public:
    Goal(MainClass* mainClass, ClassDeclarationsList *classes);
    void Accept(IVisitor* v) const;
    char* Name() const;

    MainClass *mainClass;
    ClassDeclarationsList *classes;
};

