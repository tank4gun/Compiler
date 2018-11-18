//
// Created by daniil on 18.11.18.
//
#pragma once
#include <vector>
#include <map>
#include <memory>
#include "VisibilityBlock.h"
#include "ClassInfo.h"

class Table {
  public:
    std::vector<VisibilityBlock*> class_blocks;
    std::map<Symbol*, ClassInfo*> classes;
};

