#pragma once
#include "IVisitor.h"
#include "ClassDeclaration.h"
#include <memory>

class IClass;
class IVisitor;

class Goal {
  public:
    Goal(IClass* mainClass, IClass* classes);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::unique_ptr<IClass> mainClass;
    std::unique_ptr<IClass> classes;
};

