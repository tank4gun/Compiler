#pragma once

#include "../IVisitor.h"
#include "LocStruct.h"

class IBase {
  public:
    IBase() = default;
    explicit IBase(LocStruct location) : location(location) {}

    LocStruct location;
};