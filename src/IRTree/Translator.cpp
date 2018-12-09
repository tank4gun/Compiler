//
// Created by elena on 09.12.18.
//

#include "Translator.h"

// for Expressions.h

void Translator::visit(const IndexExp *n) {
    ///TODO
}
void Translator::visit(const LengthExp *n){
    ///TODO
}
void Translator::visit(const CallMethodExp *n){
    ///TODO
}
void Translator::visit(const IntExp *n){
    ///TODO
}
void Translator::visit(const BooleanExp *n){
    ///TODO
}
void Translator::visit(const IdExp *n){
    ///TODO
}
void Translator::visit(const ThisExp *n){
    ///TODO
}
void Translator::visit(const NewIntExp *n){
    ///TODO
}
void Translator::visit(const NewIdExp *n){
    ///TODO
}
void Translator::visit(const NotExp *n){
    ///TODO
}
void Translator::visit(const ExpList *n){}
void Translator::visit(const BinOp* n){
    ///TODO
}
void Translator::visit(const NewExp *n){}

// for Identifiers.h

void Translator::visit(const Identifier *n) {}


// for Statements.h

void Translator::visit(const IfStatement *n){
    ///TODO
}
void Translator::visit(const WhileStatement *n){
    ///TODO
}
void Translator::visit(const OutputStatement *n) {
    n->exp->Accept(this);
    curWrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(curFrame->CallFunction("print", curWrapper->ToExp())));
}
void Translator::visit(const AssignStatement *n){
    ///TODO
}
void Translator::visit(const ArrayAssignStatement *n){
    n->identifier->Accept(this);
    auto leftExpr = curWrapper->ToExp();

    n->exp1->Accept(this);
    auto indexExpr = curWrapper->ToExp();

    n->exp2->Accept(this);
    auto resultExpr = curWrapper->ToExp();

    curWrapper = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new MoveStm(new MemoryExp(new BinaryExp(
        BinaryOps::PLUSOP, leftExpr, new BinaryExp(BinaryOps::MULTOP, new BinaryExp(BinaryOps::PLUSOP, indexExpr,
                                    new ConstExp(1)), new ConstExp(curFrame->WordSize())))), resultExpr)));
}
void Translator::visit(const StatementsList *n){}
void Translator::visit(const BraceStatement *n){}
void Translator::visit(const ReturnStatement *n){}


// for Types.h

void Translator::visit(const IntArrayType *n) {}
void Translator::visit(const IntType *n){}
void Translator::visit(const BooleanType *n) {}
void Translator::visit(const IdentifierType *n) {}


// for MethodDeclaration.h

void Translator::visit(const Argument *n) {}
void Translator::visit(const ArgumentsList *n) {}
void Translator::visit(const MethodDeclaration *n) {}
void Translator::visit(const MethodDeclarationsList *n) {}


// for VarDeclaration.h

void Translator::visit(const VarDeclaration *n) {}
void Translator::visit(const VarDeclarationsList *n) {}


// for ClassDeclaration.h

void Translator::visit(const ClassDeclaration *n) {}
void Translator::visit(const MainClass *n) { ///REFACTOR
    curClass = table->classes.find(n->id1->id)->second;
    buildNewFrame(curClass->methods.begin()->second->name);

    n->statement->Accept(this);
    std::unique_ptr<const ISubtreeWrapper> stmtWrapper = std::move( curWrapper );
    curWrapper = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new SeqStm(new LabelStm(Label(curFrame->Name())),
                    stmtWrapper->ToStm())));

    CodeFragment codeFragment(curFrame, curWrapper->ToStm());
    codeFragments.emplace(curFrame->Name(), std::move(codeFragment));

}
void Translator::visit(const ClassDeclarationsList *n) {}
void Translator::visit(const Extends *n) {}


// for Goal.h
void Translator::visit(std::unique_ptr<Goal>& n) {}
void Translator::visit(std::unique_ptr<ASTGoal>& n) {
    n->mainClass->Accept(this);
    for(const auto& classe : *n->classes->classes) {
        classe->Accept(this);
    }

}

// for ASTClasses.h

void Translator::visit(const ASTClassDeclarations *n) {}
void Translator::visit(const ASTClassDeclaration *n) {
    curClass = table->classes[n->i1->id];
    for(auto& method : *n->methods->methods ) {
        method->Accept(this);
    }
    curClass = nullptr;

}
void Translator::visit(const ASTVarDeclarations *n) {}
void Translator::visit(const ASTMethodsList* n) {}
void Translator::visit(const ASTStatementsList* n) {}
void Translator::visit(const ASTExpressionDeclarations* n) {}
void Translator::visit(const ASTArgumentsList* n) {}
void Translator::visit(const ASTMethodDeclaration* n) {
    curMethod = curClass->methods[n->id->id];
    buildNewFrame( n->id->id );

    std::unique_ptr<ISubtreeWrapper> rightTail; ///TODO refactor name

    if (!n->statements->statements->empty()) {
        n->statements->statements->back()->Accept(this);
        rightTail = std::move(curWrapper);
        for (auto stmt = n->statements->statements->rbegin(); stmt != n->statements->statements->rend(); ++stmt) {
            if (stmt == n->statements->statements->rbegin()) continue;

            (*stmt)->Accept(this);
//            std::unique_ptr<ISubtreeWrapper> curResult = std::move(curWrapper);
            rightTail = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new SeqStm(
                            curWrapper->ToStm(), ///TODO may not work, was curResult
                            rightTail->ToStm())));
        }
    }
    std::unique_ptr<ISubtreeWrapper> statementsWrapper = std::move(rightTail);

    n->exp->Accept(this);
    IIRExp* returnExpression = curWrapper->ToExp();

    if(statementsWrapper) {
        curWrapper = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new SeqStm(new LabelStm(Label(curFrame->Name())),
                        new SeqStm(statementsWrapper->ToStm(), new MoveStm(curFrame->GetAccess("RETURN_VALUE")->GetExp(),
                                returnExpression)))));
    } else {
        curWrapper = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new SeqStm(new LabelStm(Label(curFrame->Name())),
                        new MoveStm(curFrame->GetAccess("RETURN_VALUE")->GetExp(), returnExpression))));
    }
    CodeFragment codeFragment(curFrame, curWrapper->ToStm());
    codeFragments.emplace(curFrame->Name(), std::move(codeFragment));
    curMethod = nullptr;

}
void Translator::visit(const ASTCallMethodExp* n) {}
void Translator::visit(const ASTBraceStatement* n) {}