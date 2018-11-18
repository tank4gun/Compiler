//
// Created by daniil on 28.10.18.
//
#pragma once
#include "IVisitor.h"
#include <cstdio>
#include "ASTBuilder.h"
#include "ClassDeclaration.h"
#include "Expressions.h"
#include "Goal.h"
#include "Identifiers.h"
#include "MethodDeclaration.h"
#include "Statements.h"
#include "Types.h"
#include "VarDeclaration.h"
#include "ListDeclaration.h"

class ASTBuilder : public IVisitor {
  private:

    IExp* exp_pointer;
    IIdentifier* id_pointer;
    IStatement* statement_pointer;
    IVarDeclaration* var_pointer;
    IType* type_pointer;
    IArgument* arg_pointer;
    IMethodDeclaration* meth_pointer;
    IClass* class_pointer;
    IListDeclaration* list_pointer;

  public:
    explicit ASTBuilder();
    ~ASTBuilder();

    std::unique_ptr<Goal> goal_pointer;


    void visit(const IndexExp* n) override;
    void visit(const LengthExp* n) override;
    void visit(const ExpList* n) override;
    void visit(const CallMethodExp* n) override;
    void visit(const IntExp* n) override;
    void visit(const BooleanExp* n) override;
    void visit(const IdExp* n) override;
    void visit(const ThisExp* n) override;
    void visit(const NewIntExp* n) override;
    void visit(const NewIdExp* n) override;
    void visit(const NotExp* n) override;
    void visit(const ASTCallMethodExp* n) override;
    void visit(const ASTExpressionDeclarations* n) override;
    void visit(const BinOp* n) override ;

    void visit(const NewExp *n) override;

    void visit(const Identifier* n) override;


    void visit(const IfStatement* n) override;
    void visit(const WhileStatement* n) override;
    void visit(const OutputStatement* n) override;
    void visit(const AssignStatement* n) override;
    void visit(const ArrayAssignStatement* n) override;
    void visit(const StatementsList* n) override;
    void visit(const BraceStatement* n) override;
    void visit(const ASTStatementsList* n) override;
    void visit(const ASTBraceStatement* n) override;
    void visit(const ReturnStatement *n) override;

    void visit(const IntArrayType* n) override;
    void visit(const BooleanType* n) override;
    void visit(const IntType* n) override;
    void visit(const IdentifierType* n) override;


    void visit(const VarDeclaration* n) override;
    void visit(const VarDeclarationsList* n) override;
    void visit(const ASTVarDeclarations *n) override;


    void visit(const Argument* n) override;
    void visit(const ArgumentsList* n) override;
    void visit(const MethodDeclaration* n) override;
    void visit(const MethodDeclarationsList* n) override;
    void visit(const ASTMethodDeclaration* n) override;
    void visit(const ASTArgumentsList* n) override;
    void visit(const ASTMethodsList* n) override;

    void visit(std::unique_ptr<Goal>& n) override;


    void visit(const Extends* n) override;
    void visit(const ClassDeclaration* n) override;
    void visit(const MainClass* n) override;
    void visit(const ClassDeclarationsList* n) override;
    void visit(const ASTClassDeclarations *n) override;
};

