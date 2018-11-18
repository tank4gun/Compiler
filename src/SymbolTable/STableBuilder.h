#pragma once
#include "IVisitor.h"
#include "ClassInfo.h"
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "Table.h"
#include <vector>
#include <string>
class STableBuilder: public IVisitor {
  private:
    std::unique_ptr<Table> table;
    ClassInfo* classInfo;
    MethodInfo* methodInfo;
    VariableInfo* variableInfo;

    std::vector<std::string> errors;
  public:
    explicit STableBuilder();
    ~STableBuilder();


    void visit(const IndexExp* n) override;
    void visit(const LengthExp* n) override;
    void visit(const ExpList* n) override = 0;
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
    void visit(const StatementsList* n) override = 0;
    void visit(const BraceStatement* n) override = 0;
    void visit(const ASTStatementsList* n) override;
    void visit(const ASTBraceStatement* n) override;
    void visit(const ReturnStatement *n) override;

    void visit(const IntArrayType* n) override;
    void visit(const BooleanType* n) override;
    void visit(const IntType* n) override;
    void visit(const IdentifierType* n) override;


    void visit(const VarDeclaration* n) override;
    void visit(const VarDeclarationsList* n) override = 0;
    void visit(const ASTVarDeclarations *n) override;


    void visit(const Argument* n) override;
    void visit(const ArgumentsList* n) override = 0;
    void visit(const MethodDeclaration* n) override = 0;
    void visit(const MethodDeclarationsList* n) override = 0;
    void visit(const ASTMethodDeclaration* n) override;
    void visit(const ASTArgumentsList* n) override = 0;
    void visit(const ASTMethodsList* n) override = 0;

    void visit(std::unique_ptr<Goal>& n) override;


    void visit(const Extends* n) override;
    void visit(const ClassDeclaration* n) override;
    void visit(const MainClass* n) override;
    void visit(const ClassDeclarationsList* n) override = 0;
    void visit(const ASTClassDeclarations *n) override;
};
