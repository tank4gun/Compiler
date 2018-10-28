#pragma once
#include "IVisitor.h"
#include "ClassDeclaration.h"

class IClass;
class IVisitor;
class MainClass;
class ClassDeclarationsList;

class Goal {
  public:
    Goal(IClass* mainClass, IClass* classes);
    void Accept(IVisitor* v) const;
    char* Name() const;

    IClass *mainClass;
    IClass *classes;
};

