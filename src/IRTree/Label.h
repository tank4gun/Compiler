#pragma once

#include <string>

class Label {
  public:
    Label() = default;
    explicit Label(std::string label): label(std::move(label)) {}

    std::string label;
};

class Temp {
  public:
    explicit Temp(std::string label): label(std::move(label)) {}

    const std::string label;
};