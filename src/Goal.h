#pragma once
#include "IVisitor.h"
#include "ClassDeclaration.h"
#include "ListDeclaration.h"

class IClass;
class IVisitor;
class IListDeclaration;

class Goal {
  public:
    Goal(IClass* mainClass, IListDeclaration* classes);
    void Accept(IVisitor* v) const;
    char* Name() const;

    IClass *mainClass;
    IListDeclaration *classes;
};

