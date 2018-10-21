//
// Created by daniil on 21.10.18.
//
#include "IVisitor.h"

class IVisitor;

class IIdentifier {
    virtual void Accept( IVisitor* v ) const = 0;
    virtual char* Name() const = 0;
};


#ifndef MINIJAVA_IDENTIFIERS_H
#define MINIJAVA_IDENTIFIERS_H

#endif //MINIJAVA_IDENTIFIERS_H
