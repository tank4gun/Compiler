#pragma once
#include <string>

class Symbol {
  private:
    const std::string symb;

  public:
    explicit Symbol(const std::string& str) : symb(str) {
    }
    const std::string& String() const {
        return symb;
    }

    Symbol(const Symbol&) = delete;
    void operator=(const Symbol&) = delete;
};
