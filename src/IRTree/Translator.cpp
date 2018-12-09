//
// Created by elena on 09.12.18.
//

#include <SymbolTable/TypeInfo.h>
#include "Translator.h"

// for Expressions.h

void Translator::visit(const IndexExp *n) {
    n->e1->Accept(this);
    auto e1_wrapper = curWrapper->ToExp();

    n->e2->Accept(this);
    auto e2_wrapper = curWrapper->ToExp();

    curWrapper =
        std::unique_ptr<ISubtreeWrapper>(
            new ExpConverter(
                new MemoryExp(
                    new BinaryExp(
                        BinaryOps::PLUSOP,
                        e1_wrapper,
                        new BinaryExp(
                            BinaryOps::MULTOP,
                            new BinaryExp(
                                BinaryOps::PLUSOP,
                                e2_wrapper,
                                new ConstExp(1)
                            ),
                            new ConstExp(curFrame->WordSize())
                        )
                    )
                )
            )
        );

}

void Translator::visit(const LengthExp *n){
  n->e1->Accept(this);
  curWrapper =
      std::unique_ptr<ISubtreeWrapper>(
          new ExpConverter(curWrapper->ToExp())
      );
}

void Translator::visit(const ASTCallMethodExp *n){
  n->e1->Accept( this );
  std::unique_ptr<ISubtreeWrapper> callerWrapper = std::move(curWrapper);

  ClassInfo* callerClassInfo = table->classes[callerClassSymbol];
  const MethodInfo* methodInfo = callerClassInfo->methods[n->i1->id];
  const TypeInfo retType = TypeInfo(methodInfo->returnType);
  if(retType.type == "custom") {
    callerClassSymbol = retType.name;
  }

  IRExpList* listOfCallerAndArguments = new IRExpList(callerWrapper->ToExp());
  for(auto& arg : *n->e2->expressions) {
    arg->Accept( this );
    listOfCallerAndArguments->expressions.emplace_back(curWrapper->ToExp());
  }
  curWrapper =
      std::unique_ptr<ISubtreeWrapper>(
          new ExpConverter(
              new CallExp(
                  new NameExp(
                      Label(makeMethodFullName( callerClassSymbol->String(), n->i1->id->String()))
                  ),
                  listOfCallerAndArguments
              )
          )
      );

}

void Translator::visit(const IntExp *n){
  curWrapper =
      std::unique_ptr<ISubtreeWrapper>(
          new ExpConverter(
              new ConstExp(n->num)
          )
      );

}

void Translator::visit(const BooleanExp *n) {
  curWrapper =
      std::unique_ptr<ISubtreeWrapper>(
          new ExpConverter(
              new ConstExp(n->value ? 1 : 0)
          )
      );
}

void Translator::visit(const IdExp *n){
  const IAccess* address = curFrame->GetAccess(n->i1->id->String());

  if(address) {
    VariableInfo* type;
    if(!curMethod->VarInBlock(n->i1->id)) {

      // expression is a name of field
      curWrapper =
          std::unique_ptr<ISubtreeWrapper>(
              new ExpConverter(address->GetExp())
          );
      type = curClass->getVar(n->i1->id);
    } else {
      // expression is a name of local var / argument
      curWrapper =
          std::unique_ptr<ISubtreeWrapper>(
              new ExpConverter(address->GetExp())
          );
      type = curMethod->vars[n->i1->id];
    }

    if(type->type == "custom") {
      callerClassSymbol = type->custom_type;
    }
  }


}

void Translator::visit(const ThisExp *n){
  curWrapper =
      std::unique_ptr<ISubtreeWrapper>(
          new ExpConverter(
              curFrame->GetAccess("THIS")->GetExp()
          )
      );
  callerClassSymbol = curClass->name;
}

void Translator::visit(const NewIntExp *n){
  n->e1->Accept(this);
  auto lengthExpr = curWrapper->ToExp();

  curWrapper =
      std::unique_ptr<ISubtreeWrapper>(
          new ExpConverter(
              curFrame->CallFunction(
                  "malloc",
                  new BinaryExp(
                      BinaryOps::MULTOP,
                      new BinaryExp(
                          BinaryOps::PLUSOP,
                          lengthExpr,
                          new ConstExp( 1 )
                      ),
                      new ConstExp(
                          curFrame->WordSize()
                      )
                  )
              )
          )
      );

}

void Translator::visit(const NewIdExp *n){
  const ClassInfo* curClassInfo = table->classes[n->i1->id];
  int fieldCount = curClassInfo->Size();

  curWrapper =
      std::unique_ptr<ISubtreeWrapper>(
          new ExpConverter(
              curFrame->CallFunction(
                  "malloc",
                  new BinaryExp(
                      BinaryOps::MULTOP,
                      new ConstExp( fieldCount ),
                      new ConstExp( curFrame->WordSize() )
                  )
              )
          )
      );

  callerClassSymbol = n->i1->id;
}

void Translator::visit(const NotExp *n){
  n->e1->Accept(this);

  curWrapper =
      std::unique_ptr<ISubtreeWrapper>(
          new LogicNegCondConverter(
              curWrapper.release()
          )
      );
}

void Translator::visit(const ExpList *n){}

void Translator::visit(const BinOp* n){
  n->e1->Accept(this);
  auto leftWrapper = std::move(curWrapper);

  n->e2->Accept(this);
  auto rightWrapper = std::move(curWrapper);

  if(n->operation == BinaryOps::LESSOP) {
    curWrapper =
        std::unique_ptr<ISubtreeWrapper>(
            new RelCondConverter(
                RelType::LT,
                leftWrapper->ToExp(),
                rightWrapper->ToExp()
            )
        );
  } else if(n->operation == BinaryOps::ANDOP) {
    curWrapper =
        std::unique_ptr<ISubtreeWrapper>(
            new LogicAndCondConverter(
                leftWrapper.release(),
                rightWrapper.release()
            )
        );
  } else {
    BinaryOps operatorType = n->operation;

    curWrapper =
        std::unique_ptr<ISubtreeWrapper>(
            new ExpConverter(
                new BinaryExp(
                    operatorType,
                    leftWrapper->ToExp(),
                    rightWrapper->ToExp()
                )
            )
        );
  }
}

void Translator::visit(const NewExp *n){}

// for Identifiers.h

void Translator::visit(const Identifier *n){}


// for Statements.h

void Translator::visit(const IfStatement *n){
  n->exp->Accept( this );
  std::unique_ptr<const ISubtreeWrapper> condWrapper = std::move(curWrapper);

  n->statement1->Accept( this );
  std::unique_ptr<const ISubtreeWrapper> trueWrapper = std::move(curWrapper);

  n->statement2->Accept( this );
  std::unique_ptr<const ISubtreeWrapper> falseWrapper = std::move(curWrapper);

  Label labelTrue("IFTRUE");
  Label labelFalse("IFFALSE");
  Label labelJoin("IF");
  auto resultLabelFalse = labelJoin;
  auto resultLabelTrue = labelJoin;

  IIRStm* suffix = new LabelStm(labelJoin);
  if(falseWrapper) {
    resultLabelFalse = Label(labelFalse.label);

    suffix =
        new SeqStm(
            new LabelStm( labelFalse ),
            new SeqStm(
                falseWrapper->ToStm(),
                suffix
            )
        );
    if(trueWrapper) {
      suffix =
          new SeqStm(
              new JumpStm(labelJoin),
              suffix
          );
    }
  }

  if(trueWrapper) {
    resultLabelTrue = labelTrue;

    suffix =
        new SeqStm(
            new LabelStm(labelTrue),
            new SeqStm(
                trueWrapper->ToStm(), suffix
            )
        );
  }

  curWrapper =
      std::unique_ptr<ISubtreeWrapper>(
          new StmtConverter(
              new SeqStm(
                  condWrapper->ToConditional(resultLabelTrue, resultLabelFalse),
                  suffix
              )
          )
      );
}

void Translator::visit(const WhileStatement *n){
  n->exp->Accept( this );
  std::unique_ptr<const ISubtreeWrapper> expWrapper = std::move(curWrapper);

  n->statement->Accept( this );
  std::unique_ptr<const ISubtreeWrapper> stmWrapper = std::move(curWrapper);

  Label labelLoop("WHILELOOP");
  Label labelBody("WHILEBODY");
  Label labelDone("WHILEDONE");

  IIRStm* suffix = new SeqStm(new JumpStm(labelLoop),
                              new LabelStm(labelDone));
  if(stmWrapper) {
    suffix = new SeqStm(stmWrapper->ToStm(), suffix);
  }

  curWrapper =
      std::unique_ptr<ISubtreeWrapper>(
          new StmtConverter(
              new SeqStm(
                  new LabelStm(labelLoop),
                  new SeqStm(
                      expWrapper->ToConditional(labelBody, labelDone),
                      new SeqStm(
                          new LabelStm(labelBody),
                          suffix
                      )
                  )
              )
          )
      );
}

void Translator::visit(const OutputStatement *n){
    ///TODO
}
void Translator::visit(const AssignStatement *n){
  n->exp->Accept( this );
  IIRExp* dst = curWrapper->ToExp();

  n->identifier->Accept( this );
  IIRExp* src = curWrapper->ToExp();

  curWrapper =
      std::unique_ptr<ISubtreeWrapper>(
          new StmtConverter(
              new MoveStm(dst, src)
          )
      );
}

void Translator::visit(const ArrayAssignStatement *n){
    ///TODO
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
void Translator::visit(const MainClass *n) {
    ///TODO
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
    ///TODO
}
void Translator::visit(const ASTVarDeclarations *n) {}
void Translator::visit(const ASTMethodsList* n) {}
void Translator::visit(const ASTStatementsList* n) {}
void Translator::visit(const ASTExpressionDeclarations* n) {}
void Translator::visit(const ASTArgumentsList* n) {}
void Translator::visit(const ASTMethodDeclaration* n) {
    ///TODO
}
void Translator::visit(const CallMethodExp* n) {}
void Translator::visit(const ASTBraceStatement* n) {}