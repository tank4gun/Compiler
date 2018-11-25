#pragma once
#include <string>
#include "Symbol.h"
#include "ST-AST/Types.h"

class TypeInfo {
  public:
    TypeInfo(std::string type, Symbol* name = nullptr): type(type), name(name) {}
//    std::string GetString() {
//        switch ( type ) {
//            case Type::TYPE::INT_ARR:
//                return "int[]";
//            case Type::TYPE::INT:
//                return "int";
//            case Type::TYPE::BOOLEAN:
//                return "boolean";
//            case Type::TYPE::CUSTOM:
//                return name->String();
//            case Type::TYPE::UNKNOWN:
//                return "UNKNOWN";
//            default:
//                assert(false);
//        }
//    }

    bool operator==(const TypeInfo& other) const {
        return type == other.type && name == other.name;
    }

    bool operator!=(const TypeInfo& other) const {
        return !operator==(other);
    }

    std::string type;
    Symbol* name;
};