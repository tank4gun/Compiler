#pragma once

#include "IVisitor.h"
#include <cstdio>

class PrettyPrinter : public IVisitor {
  private:
    FILE *f;
    int cur_node_num;
    int node_num;

    void add_edge();
    void add_node(const char *name);
  public:
    explicit PrettyPrinter(FILE *output);
    ~PrettyPrinter();

    // for Expressions.h

    void visit(const PlusExp *n) override;
    void visit(const MinusExp *n) override;
    void visit(const TimesExp *n) override;
    void visit(const DivideExp *n) override;
    void visit(const AddExp *n) override;
    void visit(const LessExp *n) override;
    void visit(const IndexExp *n) override;
    void visit(const LengthExp *n) override;
    void visit(const CallMethodExp *n) override;
    void visit(const IntExp *n) override;
    void visit(const TrueExp *n) override;
    void visit(const FalseExp *n) override;
    void visit(const IdExp *n) override;
    void visit(const ThisExp *n) override;
    void visit(const NewIntExp *n) override;
    void visit(const NewIdExp *n) override;
    void visit(const NotExp *n) override;


    // for Identifiers.h

    void visit(const Identifier *n) override;


    // for Statements.h

    void visit(const IfStatement *n) override;
    void visit(const WhileStatement *n) override;
    void visit(const OutputStatement *n) override;
    void visit(const AssignStatement *n) override;
    void visit(const ArrayAssignStatement *n) override;
    void visit(const StatementsList *n) override;
};