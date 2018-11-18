#include <utility>

//
// Created by daniil on 18.11.18.
//
#pragma once
#include <string>

class Symbol {
  private:
    const std::string& symb;

  public:
    explicit Symbol(const std::string& str) : symb(str) {
        printf("STRING IN CLASS CONSTRUCTOR %s\n", str.c_str());
    }
    const std::string& String() const {
        printf("STRING IN STRING %s\n", symb.c_str());
        return symb;
    }

    Symbol(const Symbol&) = delete;
    void operator=(const Symbol&) = delete;
};
