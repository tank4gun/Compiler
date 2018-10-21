//
// Created by daniil on 21.10.18.
//
#include <stdio.h>
#include <string.h>
#include "Expressions.h"


class PlusExp : IExp {
    PlusExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

    void Accept( IVisitor* v) const {
        v->visit(this);
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
    MinusExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

    void Accept( IVisitor* v) const {
        v->visit(this);
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
    TimesExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

    void Accept( IVisitor* v) const {
        v->visit(this);
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
    DivideExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

    void Accept( IVisitor* v) const {
        v->visit(this);
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
    AddExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

    void Accept( IVisitor* v) const {
        v->visit(this);
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
    LessExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

    void Accept( IVisitor* v) const {
        v->visit(this);
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
    IndexExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

    void Accept( IVisitor* v) const {
        v->visit(this);
    }

    char* Name() {
        char* name = new char[8];
        strcpy(name, "IndexExp");
        return name;
    }

    const IExp* e1;
    const IExp* e2;
};


class LengthExp : IExp {
    LengthExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

    void Accept( IVisitor* v) const {
        v->visit(this);
    }

    char* Name() {
        char* name = new char[9];
        strcpy(name, "LengthExp");
        return name;
    }

    const IExp* e1;
};


class CallMethodExp : IExp {
    CallMethodExp(IExp* e1, IExp* e2) : e1(e1), e2(e2) {}

    void Accept( IVisitor* v) const {
        v->visit(this);
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
    TrueExp() {}

    void Accept( IVisitor* v) const {
        v->visit(this);
    }

    char* Name() {
        char* name = new char[7];
        strcpy(name, "TrueExp");
        return name;
    }
};


class FalseExp : IExp {
    FalseExp() {}

    void Accept( IVisitor* v) const {
        v->visit(this);
    }

    char* Name() {
        char* name = new char[8];
        strcpy(name, "FalseExp");
        return name;
    }
};
