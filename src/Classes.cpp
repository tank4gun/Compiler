//
// Created by daniil on 21.10.18.
//
#include <stdio.h>
#include <string.h>
#include "Classes.h"

class PlusExp : IExp {
    void Accept( IVisitor* v) const {
        return v->visit(this);
    }

    char* Name() {
        char* name = new char[7];
        strcpy(name, "PlusExp");
        return name;
    }

    const IExp* e1;
    const IExp* e2;
};


class MinusExp : IExp {
    void Accept( IVisitor* v) const {
        return v->visit(this);
    }

    char* Name() {
        char* name = new char[8];
        strcpy(name, "MinusExp");
        return name;
    }

    const IExp* e1;
    const IExp* e2;
};


class TimesExp : IExp {
    void Accept( IVisitor* v) const {
        return v->visit(this);
    }

    char* Name() {
        char* name = new char[8];
        strcpy(name, "TimesExp");
        return name;
    }

    const IExp* e1;
    const IExp* e2;
};


class DivideExp : IExp {
    void Accept( IVisitor* v) const {
        return v->visit(this);
    }

    char* Name() {
        char* name = new char[9];
        strcpy(name, "DivideExp");
        return name;
    }

    const IExp* e1;
    const IExp* e2;
};


class AddExp : IExp {
    void Accept( IVisitor* v) const {
        return v->visit(this);
    }

    char* Name() {
        char* name = new char[6];
        strcpy(name, "AddExp");
        return name;
    }

    const IExp* e1;
    const IExp* e2;
};


class LessExp : IExp {
    void Accept( IVisitor* v) const {
        return v->visit(this);
    }

    char* Name() {
        char* name = new char[7];
        strcpy(name, "LessExp");
        return name;
    }

    const IExp* e1;
    const IExp* e2;
};


class IndexExp : IExp {
    void Accept( IVisitor* v) const {
        return v->visit(this);
    }

    char* Name() {
        char* name = new char[8];
        strcpy(name, "IndexExp");
        return name;
    }

    const IExp* e1;
    const IExp* e2;
};


class TrueExp : IExp {
    void Accept( IVisitor* v) const {
        return v->visit(this);
    }

    char* Name() {
        char* name = new char[7];
        strcpy(name, "TrueExp");
        return name;
    }
};


class FalseExp : IExp {
    void Accept( IVisitor* v) const {
        return v->visit(this);
    }

    char* Name() {
        char* name = new char[8];
        strcpy(name, "FalseExp");
        return name;
    }
};
