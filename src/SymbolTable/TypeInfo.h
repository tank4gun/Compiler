#pragma once
#include <string>
#include "Symbol.h"
#include "ST-AST/Types.h"

class TypeInfo {
  public:
    TypeInfo(const IType& type, Symbol* name = nullptr): type(type.Name()), name(name) {}

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

  private:
    std::string type;
    std::unique_ptr<Symbol> name;
};