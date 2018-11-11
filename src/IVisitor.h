#pragma once
#include "Expressions.h"
#include "Identifiers.h"
#include "Statements.h"
#include "Types.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "ClassDeclaration.h"
#include "Goal.h"
#include <memory>
// for Expressions.h

class PlusExp;
class MinusExp;
class TimesExp;
class DivideExp;
class AndExp;
class LessExp;
class IndexExp;
class LengthExp;
class CallMethodExp;
class IntExp;
class TrueExp;
class FalseExp;
class IdExp;
class ThisExp;
class NewIntExp;
class NewIdExp;
class NotExp;
class ParenExp;
class ExpList;
class ReturnExp;
class NewExp;
class BinOp;

// for Identifiers.h

class Identifier;


// for Statements.h

class IfStatement;
class WhileStatement;
class OutputStatement;
class AssignStatement;
class ArrayAssignStatement;
class StatementsList;
class BraceStatement;

// for Types.h

class IntArrayType;
class BooleanType;
class IntType;
class IdentifierType;

// for MethodDeclaration.h

class Argument;
class ArgumentsList;
class MethodDeclaration;
class MethodDeclarationsList;

// for VarDeclaration.h

class VarDeclaration;
class VarDeclarationsList;

// for ClassDeclaration.h

class ClassDeclaration;
class MainClass;
class ClassDeclarationsList;
class Extends;

// for Goal.h

class Goal;


// for ASTClasses.h

class ASTClassDeclarations;
class ASTVarDeclarations;
class ASTMethodsList;
class ASTStatementsList;
class ASTExpressionDeclarations;
class ASTArgumentsList;
class ASTMethodDeclaration;
class ASTCallMethodExp;


class IVisitor {
  public:


    // for Expressions.h

    virtual void visit(const PlusExp *n) = 0;
    virtual void visit(const MinusExp *n) = 0;
    virtual void visit(const TimesExp *n) = 0;
    virtual void visit(const DivideExp *n) = 0;
    virtual void visit(const AndExp *n) = 0;
    virtual void visit(const LessExp *n) = 0;
    virtual void visit(const IndexExp *n) = 0;
    virtual void visit(const LengthExp *n) = 0;
    virtual void visit(const CallMethodExp *n) = 0;
    virtual void visit(const IntExp *n) = 0;
    virtual void visit(const TrueExp *n) = 0;
    virtual void visit(const FalseExp *n) = 0;
    virtual void visit(const IdExp *n) = 0;
    virtual void visit(const ThisExp *n) = 0;
    virtual void visit(const NewIntExp *n) = 0;
    virtual void visit(const NewIdExp *n) = 0;
    virtual void visit(const NotExp *n) = 0;
    virtual void visit(const ParenExp *n) = 0;
    virtual void visit(const ExpList *n) = 0;
    virtual void visit(const BinOp* n) = 0;
    virtual void visit(const ReturnExp *n) = 0;
    virtual void visit(const NewExp *n) = 0;

    // for Identifiers.h

    virtual void visit(const Identifier *n) = 0;


    // for Statements.h

    virtual void visit(const IfStatement *n) = 0;
    virtual void visit(const WhileStatement *n) = 0;
    virtual void visit(const OutputStatement *n) = 0;
    virtual void visit(const AssignStatement *n) = 0;
    virtual void visit(const ArrayAssignStatement *n) = 0;
    virtual void visit(const StatementsList *n) = 0;
    virtual void visit(const BraceStatement *n) = 0;


    // for Types.h

    virtual void visit(const IntArrayType *n) = 0;
    virtual void visit(const IntType *n) = 0;
    virtual void visit(const BooleanType *n) = 0;
    virtual void visit(const IdentifierType *n) = 0;


    // for MethodDeclaration.h

    virtual void visit(const Argument *n) = 0;
    virtual void visit(const ArgumentsList *n) = 0;
    virtual void visit(const MethodDeclaration *n) = 0;
    virtual void visit(const MethodDeclarationsList *n) = 0;


    // for VarDeclaration.h

    virtual void visit(const VarDeclaration *n) = 0;
    virtual void visit(const VarDeclarationsList *n) = 0;


    // for ClassDeclaration.h

    virtual void visit(const ClassDeclaration *n) = 0;
    virtual void visit(const MainClass *n) = 0;
    virtual void visit(const ClassDeclarationsList *n) = 0;
    virtual void visit(const Extends *n) = 0;


    // for Goal.h

    virtual void visit(std::unique_ptr<Goal>& n) = 0;


    // for ASTClasses.h

    virtual void visit(const ASTClassDeclarations *n) = 0;
    virtual void visit(const ASTVarDeclarations *n) = 0;
    virtual void visit(const ASTMethodsList* n) = 0;
    virtual void visit(const ASTStatementsList* n) = 0;
    virtual void visit(const ASTExpressionDeclarations* n) = 0;
    virtual void visit(const ASTArgumentsList* n) = 0;
    virtual void visit(const ASTMethodDeclaration* n) = 0;
    virtual void visit(const ASTCallMethodExp* n) = 0;
};