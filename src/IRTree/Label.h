#pragma once

#include <string>
//#include "IIRVisitor.h"
//#include "IIRStm.h"

class Label {
  public:
    Label() = default;
    explicit Label(std::string label): label(std::move(label)) {}
//    void Accept(const IIRVisitor* v);

    const std::string label;
};

class Temp {
  public:
    explicit Temp(std::string label): label(std::move(label)) {}
//    void Accept(const IIRVisitor* v);

    const std::string label;
};