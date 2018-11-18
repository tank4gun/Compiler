#pragma once
#include "IVisitor.h"
#include "Identifiers.h"
#include "ListDeclaration.h"
#include <vector>
#include <memory>

class IVisitor;
class IIdentifier;
class ASTExpressionDeclarations;

enum BinaryOps {ANDOP, PLUSOP, MINUSOP, MULTOP, LESSOP};

class IExp {
  public:
    virtual void Accept(IVisitor *v) const = 0;
    virtual char *Name() const = 0;
};

class IndexExp : public IExp {
  public:
    IndexExp(IExp *e1, IExp *e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    std::unique_ptr<IExp> e1;
    std::unique_ptr<IExp> e2;
};

class LengthExp : public IExp {
  public:
    explicit LengthExp(IExp* e1);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    std::unique_ptr<IExp> e1;
};

class ExpList : public IExp {
  public:
    ExpList();
    explicit ExpList(IExp *exp_val);
    ExpList(IExp *exp_val, ExpList *exp_next);

    void Accept(IVisitor *v) const override;

    char *Name() const override;

    std::unique_ptr<IExp> exp_val;
    ExpList* exp_next;
};

class CallMethodExp : public IExp {
  public:
    CallMethodExp(IExp* e1, IIdentifier* i1, ExpList* e3);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    std::unique_ptr<IExp> e1;
    std::unique_ptr<IIdentifier> i1;
    std::unique_ptr<ExpList> e3;
};

class IntExp: public IExp {
  public:
    explicit IntExp(int num);
    void Accept(IVisitor* v) const override;
    char *Name() const override;
    int num;
};

class BooleanExp : public IExp {
  public:
    BooleanExp(bool value);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    bool value;
};

class IdExp : public IExp {
  public:
    explicit IdExp(IIdentifier* i1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    std::unique_ptr<IIdentifier> i1;
};

class ThisExp : public IExp {
  public:
    ThisExp();
    void Accept(IVisitor* v) const override;
    char* Name() const override;
};

class NewIntExp : public IExp {
  public:
    explicit NewIntExp(IExp* e1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    IExp* e1;
};

class NewIdExp : public IExp {
  public:
    explicit NewIdExp(IIdentifier* i1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    std::unique_ptr<IIdentifier> i1;
};

class NotExp : public IExp {
  public:
    explicit NotExp(IExp* e1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    std::unique_ptr<IExp> e1;
};

class ParenExp: public IExp {
  public:
    explicit ParenExp(IExp* e1);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    std::unique_ptr<IExp> e1;
};

class ASTCallMethodExp : public IExp {
  public:
    ASTCallMethodExp(IExp* e1, IIdentifier* i1, IListDeclaration* e2);
    void Accept(IVisitor *v) const override;
    char *Name() const override;
    std::unique_ptr<IExp> e1;
    std::unique_ptr<IIdentifier> i1;
    std::unique_ptr<IListDeclaration> e2;
};


class ASTExpressionDeclarations: public IListDeclaration {
  public:
    explicit ASTExpressionDeclarations(std::vector<std::unique_ptr<IExp>>* expressions);
    void Accept(IVisitor* v) const;
    char* Name() const;

    std::unique_ptr<std::vector<std::unique_ptr<IExp>>> expressions;
};

class NewExp : public IExp {
  public:
    explicit NewExp(IIdentifier* id);
    void Accept(IVisitor* v) const override;
    char *Name() const override;

    std::unique_ptr<IIdentifier> id;
};

class BinOp : public IExp {
  public:
    BinOp(BinaryOps operation, IExp* e1, IExp* e2);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    const BinaryOps operation;
    std::unique_ptr<IExp> e1;
    std::unique_ptr<IExp> e2;
};
