#pragma once
#include "IVisitor.h"
#include "Identifiers.h"
#include "ListDeclaration.h"
#include "IBase.h"
#include "LocStruct.h"
#include <vector>
#include <memory>

class IVisitor;
class Identifier;
class ASTExpressionDeclarations;

enum BinaryOps {ANDOP, PLUSOP, MINUSOP, MULTOP, LESSOP};

class IExp : public IBase {
  public:
    explicit IExp(LocStruct location) : IBase(location) {}
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class IndexExp : public IExp {
  public:
    IndexExp(IExp *e1, IExp *e2, LocStruct location);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    std::unique_ptr<IExp> e1;
    std::unique_ptr<IExp> e2;
};

class LengthExp : public IExp {
  public:
    LengthExp(IExp* e1, LocStruct location);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    std::unique_ptr<IExp> e1;
};

class ExpList : public IExp {
  public:
    explicit ExpList(LocStruct location);
    ExpList(IExp *exp_val, LocStruct location);
    ExpList(IExp *exp_val, ExpList *exp_next, LocStruct location);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IExp> exp_val;
    ExpList* exp_next;
};

class CallMethodExp : public IExp {
  public:
    CallMethodExp(IExp* e1, Identifier* i1, ExpList* e3, LocStruct location);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    std::unique_ptr<IExp> e1;
    std::unique_ptr<Identifier> i1;
    std::unique_ptr<ExpList> e3;
};

class IntExp: public IExp {
  public:
    IntExp(int num, LocStruct location);
    void Accept(IVisitor* v) const override;
    char *Name() const override;
    int num;
};

class BooleanExp : public IExp {
  public:
    BooleanExp(bool value, LocStruct location);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    bool value;
};

class IdExp : public IExp {
  public:
    IdExp(Identifier* i1, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    std::unique_ptr<Identifier> i1;
};

class ThisExp : public IExp {
  public:
    explicit ThisExp(LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
};

class NewIntExp : public IExp {
  public:
    NewIntExp(IExp* e1, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    std::unique_ptr<IExp> e1;
};

class NewIdExp : public IExp {
  public:
    NewIdExp(Identifier* i1, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    std::unique_ptr<Identifier> i1;
};

class NotExp : public IExp {
  public:
    NotExp(IExp* e1, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    std::unique_ptr<IExp> e1;
};

class ASTCallMethodExp : public IExp {
  public:
    ASTCallMethodExp(IExp* e1, Identifier* i1, IListDeclaration* e2, LocStruct location);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    std::unique_ptr<IExp> e1;
    std::unique_ptr<Identifier> i1;
    std::unique_ptr<IListDeclaration> e2;
};


class ASTExpressionDeclarations: public IListDeclaration {
  public:
    ASTExpressionDeclarations(std::vector<std::unique_ptr<IExp>>* expressions, LocStruct location);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::unique_ptr<std::vector<std::unique_ptr<IExp>>> expressions;
};

class NewExp : public IExp {
  public:
    NewExp(Identifier* id, LocStruct location);
    void Accept(IVisitor* v) const override;
    char *Name() const override;

    std::unique_ptr<Identifier> id;
};

class BinOp : public IExp {
  public:
    BinOp(BinaryOps operation, IExp* e1, IExp* e2, LocStruct location);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    const BinaryOps operation;
    std::unique_ptr<IExp> e1;
    std::unique_ptr<IExp> e2;
};
