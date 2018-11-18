//
// Created by daniil on 18.11.18.
//
#pragma once
#include <vector>
#include <memory>
#include "VisibilityBlock.h"

class Table {
  public:
    std::vector<std::unique_ptr<VisibilityBlock>> classes;
};

