#pragma once
#include "IVisitor.h"
#include "ClassDeclaration.h"
#include <memory>
#include "ListDeclaration.h"
#include "IBase.h"
#include "LocStruct.h"

class IClass;
class IVisitor;
class IListDeclaration;

class Goal : public IBase {
  public:
    Goal(IClass* mainClass, IListDeclaration* classes, LocStruct location);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::unique_ptr<IClass> mainClass;
    std::unique_ptr<IListDeclaration> classes;
};

