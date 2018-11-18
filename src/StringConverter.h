#pragma once
#include "SymbolTable/Symbol.h"
#include <unordered_map>

class StringConverter {
  public:
    StringConverter() {
        allStrings = std::unordered_map<std::string, Symbol*>();
    }
    Symbol* getIntern(std::string src) {
        auto cached = allStrings.find(src);
        if(cached != allStrings.end()) {
            return cached->second;
        }
        Symbol* newVal = new Symbol(src);
        allStrings.insert({src, newVal});
        return newVal;
    }
    std::unordered_map<std::string, Symbol*> allStrings;

};