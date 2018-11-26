#pragma once
#include <string>
#include "Symbol.h"
#include "ST-AST/Types.h"

class TypeInfo {
  public:
    explicit TypeInfo(std::string type, Symbol* name = nullptr): type(type), name(name) {}

    std::string type;
    Symbol* name;
};