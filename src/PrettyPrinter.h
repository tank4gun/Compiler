#pragma once

#include "IVisitor.h"
#include "Expressions.h"
#include <cstdio>

class PrettyPrinter : public IVisitor {
  private:
    FILE *f;
    int node_num;

    void add_node(int &node, const char *name);
    void add_edge(int &from_node_num);
  public:
    explicit PrettyPrinter(FILE *output);
    ~PrettyPrinter();

    // for Expressions.h

    void visit(const IndexExp *n) override;
    void visit(const LengthExp *n) override;
    void visit(const CallMethodExp *n) override;
    void visit(const IntExp *n) override;
    void visit(const BooleanExp *n) override;
    void visit(const IdExp *n) override;
    void visit(const ThisExp *n) override;
    void visit(const NewIntExp *n) override;
    void visit(const NewIdExp *n) override;
    void visit(const NotExp *n) override;
    void visit(const ParenExp *n) override;
    void visit(const ExpList *n) override;
    void visit(const ASTCallMethodExp* n) override;
    void visit(const ASTExpressionDeclarations* n) override;
    void visit(const BinOp* n) override;
    void visit(const ReturnExp* n) override;
    void visit(const NewExp *n) override;

    // for Identifiers.h

    void visit(const Identifier *n) override;


    // for Statements.h

    void visit(const IfStatement *n) override;
    void visit(const WhileStatement *n) override;
    void visit(const OutputStatement *n) override;
    void visit(const AssignStatement *n) override;
    void visit(const ArrayAssignStatement *n) override;
    void visit(const StatementsList *n) override;
    void visit(const BraceStatement *n) override;
    void visit(const ASTStatementsList* n) override;
    void visit(const ASTMethodsList* n) override;
    void visit(const ASTBraceStatement* n) override;

    // for Types.h

    void visit(const IntArrayType *n) override;
    void visit(const IntType *n) override;
    void visit(const BooleanType *n) override;
    void visit(const IdentifierType *n) override;


    // for MethodDeclaration.h

    void visit(const Argument *n) override;
    void visit(const ArgumentsList *n) override;
    void visit(const MethodDeclaration *n) override;
    void visit(const MethodDeclarationsList *n) override;
    void visit(const ASTMethodDeclaration* n) override ;
    void visit(const ASTArgumentsList* n) override ;

    // for VarDeclaration.h

    void visit(const VarDeclaration *n) override;
    void visit(const VarDeclarationsList *n) override;
    void visit(const ASTVarDeclarations* n) override;

    // for ClassDeclaration.h

    void visit(const ClassDeclaration *n) override;
    void visit(const MainClass *n) override;
    void visit(const ClassDeclarationsList *n) override;
    void visit(const Extends *n) override;
    void visit(const ASTClassDeclarations* n) override;

    // for Goal.h

    void visit(const Goal *n) override;
};