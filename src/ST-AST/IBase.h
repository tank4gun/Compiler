#pragma once

#include "IVisitor.h"
#include "LocStruct.h"

class IVisitor;

class IBase {
  public:
    IBase() = default;
    explicit IBase(LocStruct location) : location(location) {}

    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;

    LocStruct location;
};