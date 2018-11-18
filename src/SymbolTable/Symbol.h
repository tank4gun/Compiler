#include <utility>

//
// Created by daniil on 18.11.18.
//
#pragma once
#include <string>

class Symbol {
  private:
    std::string symb;

  public:
    explicit Symbol(std::string str) : symb(std::move(str)) {}
    const std::string& String() const {
        return symb;
    }

    Symbol(const Symbol&) = delete;
    void operator=(const Symbol&) = delete;
};
