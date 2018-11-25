//
// Created by daniil on 18.11.18.
//
#pragma once
#include <vector>
#include "TypeInfo.h"
#include "Table.h"

class TypeChecker : public IVisitor {
  public:
    Table* table;
    ClassInfo* classInfo;
    MethodInfo* methodInfo;
    TypeInfo typeInfo;
    Symbol* symbol;
    std::vector<std::string> errors;

    explicit TypeChecker(Table *table) : table(table), classInfo(nullptr), methodInfo(nullptr), errors(),
        typeInfo(""), symbol(nullptr) {}

    VariableInfo* FindVar(Symbol *symbol);

    void printErrors() {
      for (const auto &err : errors) {
        printf("%s\n", err.c_str());
      }
    }

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
    void visit(const MethodDeclaration* n) override ;
    void visit(const MethodDeclarationsList* n) override;
    void visit(const ASTMethodDeclaration* n) override;
    void visit(const ASTArgumentsList* n) override;
    void visit(const ASTMethodsList* n) override;

    void visit(std::unique_ptr<Goal>& n) override;
    void visit(std::unique_ptr<ASTGoal>& n) override;


    void visit(const Extends* n) override;
    void visit(const ClassDeclaration* n) override;
    void visit(const ASTClassDeclaration* n) override;
    void visit(const MainClass* n) override;
    void visit(const ClassDeclarationsList* n) override;
    void visit(const ASTClassDeclarations *n) override;
};

