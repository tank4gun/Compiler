//
// Created by daniil on 18.11.18.
//
#pragma once
#include <string>

class Symbol {
  private:
    const std::string& symb;

  public:
    explicit Symbol(const std::string& str);
    const std::string& String() const;

    Symbol(const Symbol&) = delete;
    void operator=(const Symbol&) = delete;
};
