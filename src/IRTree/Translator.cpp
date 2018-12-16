//
// Created by elena on 09.12.18.
//

#include <SymbolTable/TypeInfo.h>
#include "Translator.h"

// for Expressions.h

void Translator::visit(const IndexExp *n) {
    n->e1->Accept(this);
    auto e1_wrapper = curr_wrapper->ToExp();

    n->e2->Accept(this);
    auto e2_wrapper = curr_wrapper->ToExp();

    curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(new MemoryExp(new BinaryExp(BinaryOps::PLUSOP,
                        e1_wrapper, new BinaryExp(BinaryOps::MULTOP, new BinaryExp(BinaryOps::PLUSOP, e2_wrapper, new ConstExp(1)),
                            new ConstExp(curr_frame->WordSize()))))));

}

void Translator::visit(const LengthExp *n){
  n->e1->Accept(this);
  curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(curr_wrapper->ToExp()));
}

void Translator::visit(const ASTCallMethodExp *n){
  n->e1->Accept( this );
  std::unique_ptr<ISubtreeWrapper> callerWrapper = std::move(curr_wrapper);

  ClassInfo* callerClassInfo = table->classes[curr_caller];
  const MethodInfo* methodInfo = callerClassInfo->methods[n->i1->id];
  const TypeInfo retType = TypeInfo(methodInfo->returnType);
  if(retType.type == "custom") {
    curr_caller = retType.name;
  }

  IRExpList* tmpList = new IRExpList(callerWrapper->ToExp());
  for(auto& arg : *n->e2->expressions) {
    arg->Accept( this );
    tmpList->expressions.emplace_back(curr_wrapper->ToExp());
  }
  std::string name = curr_caller->String() + "::" + n->i1->id->String();
  curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(new CallExp(
                  new NameExp(Label(name)),
                  tmpList)));

}

void Translator::visit(const IntExp *n){
  curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(new ConstExp(n->num)));
}

void Translator::visit(const BooleanExp *n) {
  curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(new ConstExp(n->value ? 1 : 0)));
}

void Translator::visit(const IdExp *n){
  const IAccess* address = curr_frame->GetAccess(n->i1->id->String());

  if(address) {
    VariableInfo* type;
    if(!curr_method->VarInBlock(n->i1->id)) {
      curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(address->GetExp()));
      type = curr_class->getVar(n->i1->id);
    } else {
      curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(address->GetExp()));

      if (curr_method->vars.find(n->i1->id) == curr_method->vars.end()) {
          type = curr_method->args[n->i1->id];
      } else {
          type = curr_method->vars[n->i1->id];
      }
    }

    if(type->type == "custom") {
      curr_caller = type->custom_type;
    }
  }


}

void Translator::visit(const ThisExp *n){
  curr_wrapper =
      std::unique_ptr<ISubtreeWrapper>(new ExpConverter(curr_frame->GetAccess("THIS")->GetExp()));
  curr_caller = curr_class->name;
}

void Translator::visit(const NewIntExp *n){
  n->e1->Accept(this);
  auto lengthExpr = curr_wrapper->ToExp();

  curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(curr_frame->CallFunction("malloc",
                  new BinaryExp(BinaryOps::MULTOP, new BinaryExp(BinaryOps::PLUSOP, lengthExpr, new ConstExp(1)),
                      new ConstExp(curr_frame->WordSize())))));
}

void Translator::visit(const NewIdExp *n){
  const ClassInfo* curClassInfo = table->classes[n->i1->id];
  int fieldCount = curClassInfo->Size();

  curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(curr_frame->CallFunction("malloc",
                  new BinaryExp(BinaryOps::MULTOP, new ConstExp(fieldCount), new ConstExp(curr_frame->WordSize())))));

  curr_caller = n->i1->id;
}

void Translator::visit(const NotExp *n){
  n->e1->Accept(this);
  curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new LogicNegCondConverter(curr_wrapper.release()));
}

void Translator::visit(const ExpList *n){}

void Translator::visit(const BinOp* n){
  n->e1->Accept(this);
  auto leftWrapper = std::move(curr_wrapper);

  n->e2->Accept(this);
  auto rightWrapper = std::move(curr_wrapper);

  if(n->operation == BinaryOps::LESSOP) {
    curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new RelCondConverter(RelType::LT, leftWrapper->ToExp(), rightWrapper->ToExp()));
  } else if(n->operation == BinaryOps::ANDOP) {
    curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new LogicAndCondConverter(leftWrapper.release(), rightWrapper.release()));
  } else {
    BinaryOps operatorType = n->operation;
    curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(new BinaryExp(operatorType, leftWrapper->ToExp(), rightWrapper->ToExp())));
  }
}

void Translator::visit(const NewExp *n){
    const ClassInfo* curClassInfo = table->classes[n->id->id];
    int fieldCount = curClassInfo->Size();

    curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(curr_frame->CallFunction("malloc",
                    new BinaryExp(BinaryOps::MULTOP, new ConstExp(fieldCount), new ConstExp(curr_frame->WordSize())))));

    curr_caller = n->id->id;
}

// for Identifiers.h

void Translator::visit(const Identifier *n) {
    const IAccess* address = curr_frame->GetAccess(n->id->String());

    if(address) {
        VariableInfo* type;
        if(!curr_method->VarInBlock(n->id)) {
            curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(address->GetExp()));
            type = curr_class->getVar(n->id);
        } else {
            curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(address->GetExp()));

            if (curr_method->vars.find(n->id) == curr_method->vars.end()) {
                type = curr_method->args[n->id];
            } else {
                type = curr_method->vars[n->id];
            }
        }

        if(type->type == "custom") {
            curr_caller = type->custom_type;
        }
    }
}


// for Statements.h

void Translator::visit(const IfStatement *n){
  n->exp->Accept( this );
  std::unique_ptr<const ISubtreeWrapper> condWrapper = std::move(curr_wrapper);

  n->statement1->Accept( this );
  std::unique_ptr<const ISubtreeWrapper> trueWrapper = std::move(curr_wrapper);

  n->statement2->Accept( this );
  std::unique_ptr<const ISubtreeWrapper> falseWrapper = std::move(curr_wrapper);

  Label labelTrue("if_true");
  Label labelFalse("if_false");
  Label labelJoin("if");
  auto resultLabelFalse = labelJoin;
  auto resultLabelTrue = labelJoin;

  IIRStm* suffix = new LabelStm(labelJoin);
  if(falseWrapper) {
    resultLabelFalse = Label(labelFalse.label);

    suffix = new SeqStm(new LabelStm(labelFalse), new SeqStm(falseWrapper->ToStm(), suffix));
    if(trueWrapper) {
      suffix = new SeqStm(new JumpStm(labelJoin), suffix);
    }
  }

  if(trueWrapper) {
    resultLabelTrue = labelTrue;

    suffix = new SeqStm(new LabelStm(labelTrue), new SeqStm(trueWrapper->ToStm(), suffix));
  }

  curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(
              new SeqStm(condWrapper->ToConditional(resultLabelTrue, resultLabelFalse), suffix)));
}

void Translator::visit(const WhileStatement *n){
  n->exp->Accept(this);
  std::unique_ptr<const ISubtreeWrapper> expWrapper = std::move(curr_wrapper);

  n->statement->Accept(this);
  std::unique_ptr<const ISubtreeWrapper> stmWrapper = std::move(curr_wrapper);

  Label labelLoop("while_loop");
  Label labelBody("while_body");
  Label labelDone("while_end");

  IIRStm* suffix = new SeqStm(new JumpStm(labelLoop), new LabelStm(labelDone));
  if(stmWrapper) {
    suffix = new SeqStm(stmWrapper->ToStm(), suffix);
  }

  curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new SeqStm(new LabelStm(labelLoop),
                  new SeqStm(expWrapper->ToConditional(labelBody, labelDone), new SeqStm(new LabelStm(labelBody),suffix)))));
}
void Translator::visit(const OutputStatement *n) {
    n->exp->Accept(this);
    curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new ExpConverter(curr_frame->CallFunction("print", curr_wrapper->ToExp())));
}
void Translator::visit(const AssignStatement *n){
  n->exp->Accept( this );
  IIRExp* src = curr_wrapper->ToExp();

  n->identifier->Accept( this );
  IIRExp* dst = curr_wrapper->ToExp();

  curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new MoveStm(dst, src)));
}

void Translator::visit(const ArrayAssignStatement *n){
    n->identifier->Accept(this);
    auto arrExpr = curr_wrapper->ToExp();

    n->exp1->Accept(this);
    auto indexExpr = curr_wrapper->ToExp();

    n->exp2->Accept(this);
    auto valExpr = curr_wrapper->ToExp();

    curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new MoveStm(new MemoryExp(new BinaryExp(
        BinaryOps::PLUSOP, arrExpr, new BinaryExp(BinaryOps::MULTOP, new BinaryExp(BinaryOps::PLUSOP, indexExpr,
                                    new ConstExp(1)), new ConstExp(curr_frame->WordSize())))), valExpr)));
}
void Translator::visit(const StatementsList *n){}
void Translator::visit(const BraceStatement *n){}
void Translator::visit(const ReturnStatement *n){
    n->exp->Accept(this);
}


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
    curr_class = table->classes[n->id1->id];
    frameFromName(curr_class->methods.begin()->second->name);
    n->statement->Accept(this);
    std::unique_ptr<const ISubtreeWrapper> stmtWrapper = std::move( curr_wrapper );
    curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new SeqStm(new LabelStm(Label(curr_frame->Name())),
                    stmtWrapper->ToStm())));

    CodeFragment codeFragment(curr_frame, curr_wrapper->ToStm());
    codeFragments.emplace(curr_frame->Name(), std::move(codeFragment));
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
    curr_class = table->classes[n->i1->id];
    for(auto& method : *n->methods->methods ) {
        method->Accept(this);
    }
    curr_class = nullptr;
}
void Translator::visit(const ASTVarDeclarations *n) {}
void Translator::visit(const ASTMethodsList* n) {}
void Translator::visit(const ASTStatementsList* n) {}
void Translator::visit(const ASTExpressionDeclarations* n) {}
void Translator::visit(const ASTArgumentsList* n) {}
void Translator::visit(const ASTMethodDeclaration* n) {
    curr_method = curr_class->methods[n->id->id];
    frameFromName(n->id->id);

    std::unique_ptr<ISubtreeWrapper> tail = nullptr;

    if (!n->statements->statements->empty()) {
        n->statements->statements->back()->Accept(this);
        tail = std::move(curr_wrapper);
        for (auto stmt = n->statements->statements->rbegin(); stmt != n->statements->statements->rend(); ++stmt) {
            if (stmt == n->statements->statements->rbegin()) {
              continue;
            }
            (*stmt)->Accept(this);
            std::unique_ptr<ISubtreeWrapper> curResult = std::move(curr_wrapper);
            tail = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new SeqStm(
                            curResult->ToStm(),
                            tail->ToStm())));
        }
    }
    std::unique_ptr<ISubtreeWrapper> statementsWrapper = std::move(tail);

    n->exp->Accept(this);
    IIRExp* returnExpression = curr_wrapper->ToExp();

    if(statementsWrapper) {
        curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new SeqStm(new LabelStm(Label(curr_frame->Name())),
                        new SeqStm(statementsWrapper->ToStm(), new MoveStm(curr_frame->GetAccess("RETURN_VALUE")->GetExp(),
                                returnExpression)))));
    } else {
        curr_wrapper = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new SeqStm(new LabelStm(Label(curr_frame->Name())),
                        new MoveStm(curr_frame->GetAccess("RETURN_VALUE")->GetExp(), returnExpression))));
    }
    CodeFragment codeFragment(curr_frame, curr_wrapper->ToStm());
    codeFragments.emplace(curr_frame->Name(), std::move(codeFragment));
    curr_method = nullptr;

}
void Translator::visit(const CallMethodExp* n) {}
void Translator::visit(const ASTBraceStatement* n) {
  std::unique_ptr<ISubtreeWrapper> tail = nullptr;

  if (!n->statements->statements->empty()) {
    n->statements->statements->back()->Accept(this);
    tail = std::move(curr_wrapper);
    for (auto stmt = n->statements->statements->rbegin(); stmt != n->statements->statements->rend(); ++stmt) {
      if (stmt == n->statements->statements->rbegin()) {
        continue;
      }
      (*stmt)->Accept(this);
      std::unique_ptr<ISubtreeWrapper> curResult = std::move(curr_wrapper);
      tail = std::unique_ptr<ISubtreeWrapper>(new StmtConverter(new SeqStm(
          curResult->ToStm(),
          tail->ToStm())));
    }
  }
  std::unique_ptr<ISubtreeWrapper> statementsWrapper = std::move(tail);
  curr_wrapper = std::move(statementsWrapper);
}