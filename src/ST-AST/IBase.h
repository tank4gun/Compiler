#pragma once

#include "YYLTYPE_struct.h"

class IBase {
  public:
    IBase() = default;
    explicit IBase(YYLTYPE location) : location(location) {}

    YYLTYPE location;
};