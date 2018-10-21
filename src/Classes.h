//
// Created by daniil on 21.10.18.
//

class IExp {
    virtual int Accept( IVisitor* v) const = 0;
    virtual bool Accept( IVisitor* v) const = 0;
    virtual char* Name() const = 0;
};



#ifndef MINIJAVA_CLASSES_H
#define MINIJAVA_CLASSES_H

#endif //MINIJAVA_CLASSES_H
