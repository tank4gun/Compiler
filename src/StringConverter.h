#pragma once
#include "SymbolTable/Symbol.h"
#include <unordered_map>

class StringConverter {
  public:
    static Symbol* getIntern(const std::string& src) {
        static std::unordered_map<std::string, Symbol*> allStrings;
        auto cached = allStrings.find(src);
        if(cached != allStrings.end()) {
            return cached->second;
        }
        Symbol* newVal = new Symbol(src);
        allStrings.insert({src, newVal});
        return newVal;
    }
};
