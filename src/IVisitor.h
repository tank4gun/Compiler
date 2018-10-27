#pragma once
#include "Expressions.h"
#include "Identifiers.h"
#include "Statements.h"
#include "Types.h"

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
};