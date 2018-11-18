//
// Created by daniil on 18.11.18.
//
#pragma once
#include "Symbol.h"

Symbol::Symbol(const std::string& str) : symb(str) {}

const std::string& Symbol::String() const {
  return symb;
}