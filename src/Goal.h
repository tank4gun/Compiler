//
// Created by daniil on 22.10.18.
//
#include "IVisitor.h"

class IVisitor;

class Goal {
  public:
    Goal();
    virtual void Accept(IVisitor* v) const = 0;
    virtual char* Name() const = 0;
};

#ifndef MINIJAVA_GOAL_H
#define MINIJAVA_GOAL_H

#endif //MINIJAVA_GOAL_H
