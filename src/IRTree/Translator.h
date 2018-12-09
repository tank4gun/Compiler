#pragma once
#include <SymbolTable/ClassInfo.h>
#include <SymbolTable/Table.h>
#include "ActivationRecords/IFrame.h"
#include "IIRStm.h"
#include "ISubtreeWrapper.h"

class CodeFragment {
  public:
    CodeFragment(IFrame* frame, IIRStm* body) : frame(frame), body(body)
    {
    }

    std::unique_ptr<IFrame> frame;
    std::unique_ptr<IIRStm> body;
};


class Translator: public IVisitor {
  public:
    std::map<std::string, CodeFragment> codeFragments;

    IFrame *curFrame = nullptr;
    std::unique_ptr<ISubtreeWrapper> curWrapper = nullptr;
    Table *table;
    ClassInfo *curClass = nullptr;
    Symbol *callerClassSymbol = nullptr;
    MethodInfo *curMethod = nullptr;

    explicit Translator(Table* table): table(table) {}

    std::string makeMethodFullName(const std::string &className, const std::string &methodName) {
        return className + "::" + methodName;
    }

    void AddClassFields(ClassInfo *classDefinition) {
        if (classDefinition->par_name != nullptr) {
            AddClassFields(classDefinition->par_class);
        }
        for (auto &it: classDefinition->fields) {
            curFrame->AddFormal(it.first->String());
        }
    }

    void buildNewFrame(Symbol* methodSymbol) { ///TODO refactor name
        ClassInfo *classDefinition = table->classes[curClass->name];
        MethodInfo *methodDefinition = classDefinition->methods[methodSymbol];

        curFrame = new MiniJavaFrame(classDefinition->name, methodDefinition->name);

        AddClassFields(classDefinition);

        for (auto &it: methodDefinition->args) {
            curFrame->AddLocal(it.first->String());
        }
        for (auto &it: methodDefinition->vars) {
            curFrame->AddLocal(it.first->String());
        }
    }

    // for Expressions.h

    void visit(const LengthExp *n) override;
    void visit(const IndexExp *n) override;
    void visit(const CallMethodExp *n) override;
    void visit(const IntExp *n) override;
    void visit(const BooleanExp *n) override;
    void visit(const IdExp *n) override;
    void visit(const ThisExp *n) override;
    void visit(const NewIntExp *n) override;
    void visit(const NewIdExp *n) override;
    void visit(const NotExp *n) override;
    void visit(const ExpList *n) override;
    void visit(const BinOp* n) override;
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
    void visit(const ReturnStatement *n) override;


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


    // for VarDeclaration.h

    void visit(const VarDeclaration *n) override;
    void visit(const VarDeclarationsList *n) override;


    // for ClassDeclaration.h

    void visit(const ClassDeclaration *n) override;
    void visit(const MainClass *n) override;
    void visit(const ClassDeclarationsList *n) override;
    void visit(const Extends *n) override;


    // for Goal.h
    void visit(std::unique_ptr<Goal>& n) override;
    void visit(std::unique_ptr<ASTGoal>& n) override;

    // for ASTClasses.h

    void visit(const ASTClassDeclarations *n) override;
    void visit(const ASTClassDeclaration *n) override;
    void visit(const ASTVarDeclarations *n) override;
    void visit(const ASTMethodsList* n) override;
    void visit(const ASTStatementsList* n) override;
    void visit(const ASTExpressionDeclarations* n) override;
    void visit(const ASTArgumentsList* n) override;
    void visit(const ASTMethodDeclaration* n) override;
    void visit(const ASTCallMethodExp* n) override;
    void visit(const ASTBraceStatement* n) override;

};