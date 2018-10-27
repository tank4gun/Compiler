#pragma once
#include "Expressions.h"
#include "Identifiers.h"
#include "Statements.h"
#include "Types.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "ClassDeclaration.h"
#include "Goal.h"

// for Expressions.h

class PlusExp;
class MinusExp;
class TimesExp;
class DivideExp;
class AddExp;
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


// for Identifiers.h

class Identifier;


// for Statements.h

class IfStatement;
class WhileStatement;
class OutputStatement;
class AssignStatement;
class ArrayAssignStatement;
class StatementsList;

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

// for Goal.h

class Goal;

class IVisitor {
  public:


    // for Expressions.h

    virtual void visit(const PlusExp *n) = 0;
    virtual void visit(const MinusExp *n) = 0;
    virtual void visit(const TimesExp *n) = 0;
    virtual void visit(const DivideExp *n) = 0;
    virtual void visit(const AddExp *n) = 0;
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


    // for Identifiers.h

    virtual void visit(const Identifier *n) = 0;


    // for Statements.h

    virtual void visit(const IfStatement *n) = 0;
    virtual void visit(const WhileStatement *n) = 0;
    virtual void visit(const OutputStatement *n) = 0;
    virtual void visit(const AssignStatement *n) = 0;
    virtual void visit(const ArrayAssignStatement *n) = 0;
    virtual void visit(const StatementsList *n) = 0;

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

    // for Goal.h

    virtual void visit(const Goal *n) = 0;

};