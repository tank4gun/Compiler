#include "PrettyPrinter.h"

PrettyPrinter::PrettyPrinter(FILE *output) : node_num(0) {
    f = output;
    fprintf(f, "%s", "strict graph G{\n");
}

PrettyPrinter::~PrettyPrinter() {
    fprintf(f, "%s", "}");
    fclose(f);
}

void PrettyPrinter::add_node(int &node, const char *name) {
    fprintf(f, "%d [label=\"%s\"];\n", node, name);
}

void PrettyPrinter::add_edge(int &from_node_num) {
    fprintf(f, "%d -- %d;\n", from_node_num, ++node_num);
}


// for Expressions.h

void PrettyPrinter::visit(const IndexExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->e1->Accept(this);
    add_edge(cur_node_num);
    n->e2->Accept(this);
}
void PrettyPrinter::visit(const LengthExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->e1->Accept(this);
}
void PrettyPrinter::visit(const CallMethodExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->e1->Accept(this);
    add_edge(cur_node_num);
    n->i1->Accept(this);
    add_edge(cur_node_num);
    n->e3->Accept(this);
}
void PrettyPrinter::visit(const IntExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    fprintf(f, "%d [label=\"%d\"];\n", node_num, n->num);
    // здесь не нужно инкрементировать node_num, так как после этого никто не будет вызывать сразу ->Accept
    // после  того, как эта функция закончится и свернется будет дальше по порядку вызван add_edge(); ->Accept;
    // и add_edge уже инкрементирует node_num внутри себя
}
void PrettyPrinter::visit(const BooleanExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, "BooleanExp");
    add_edge(cur_node_num);

    fprintf(f, "%d [label=\"%d\"];\n", node_num, n->value);
    // add_node(node_num, n->Name());
}
void PrettyPrinter::visit(const IdExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->i1->Accept(this);
}
void PrettyPrinter::visit(const ThisExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    add_node(node_num, "this");
}
void PrettyPrinter::visit(const NewIntExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->e1->Accept(this);
}
void PrettyPrinter::visit(const NewIdExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->i1->Accept(this);
}
void PrettyPrinter::visit(const NotExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->e1->Accept(this);
}
void PrettyPrinter::visit(const ExpList *n) {
    int cur_node_num = node_num;
    if (n->exp_val == nullptr) {
        add_node(cur_node_num, "Empty Expressions list");
        return;
    }
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->exp_val->Accept(this);
    if (n->exp_next == nullptr) {
        return;
    }
    add_edge(cur_node_num);
    n->exp_next->Accept(this);
}

void PrettyPrinter::visit(const ASTCallMethodExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->e1->Accept(this);
    add_edge(cur_node_num);
    n->i1->Accept(this);
    add_edge(cur_node_num);
    n->e2->Accept(this);
}

void PrettyPrinter::visit(const ASTExpressionDeclarations *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    for (auto & expression : *(n->expressions)) {
        add_edge(cur_node_num);
        expression->Accept(this);
    }
}


void PrettyPrinter::visit(const NewExp *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->id->Accept(this);
}
void PrettyPrinter::visit(const BinOp* n) {
  int cur_node_num = node_num;
  add_node(cur_node_num, n->Name());
  add_edge(cur_node_num);
  n->e1->Accept(this);
  add_edge(cur_node_num);
  switch(n->operation){
      case(BinaryOps::ANDOP) : {
          add_node(node_num, "&&");
          break;
      }
      case(BinaryOps::PLUSOP) : {
          add_node(node_num, "+");
          break;
      }
      case(BinaryOps::MINUSOP) : {
          add_node(node_num, "-");
          break;
      }
      case(BinaryOps::MULTOP) : {
          add_node(node_num, "*");
          break;
      }
      case(BinaryOps::LESSOP) : {
          add_node(node_num, "<");
          break;
      }
  }
  add_edge(cur_node_num);
  n->e2->Accept(this);
}

// for Identifiers.h

void PrettyPrinter::visit(const Identifier *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    add_node(node_num, n->id.c_str());
}


// for Statements.h

void PrettyPrinter::visit(const IfStatement *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->exp->Accept(this);
    add_edge(cur_node_num);
    n->statement1->Accept(this);
    add_edge(cur_node_num);
    n->statement2->Accept(this);
}
void PrettyPrinter::visit(const WhileStatement *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->exp->Accept(this);
    add_edge(cur_node_num);
    n->statement->Accept(this);
}
void PrettyPrinter::visit(const OutputStatement *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->exp->Accept(this);
}
void PrettyPrinter::visit(const AssignStatement *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->identifier->Accept(this);
    add_edge(cur_node_num);
    n->exp->Accept(this);
}
void PrettyPrinter::visit(const ArrayAssignStatement *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->identifier->Accept(this);
    add_edge(cur_node_num);
    n->exp1->Accept(this);
    add_edge(cur_node_num);
    n->exp2->Accept(this);
}
void PrettyPrinter::visit(const StatementsList *n) {
    int cur_node_num = node_num;
    if (n->statement_val == nullptr) {
        add_node(cur_node_num, "Empty Statements list");
        return;
    }
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->statement_val->Accept(this);
    if (n->statement_next == nullptr) {
        return;
    }
    add_edge(cur_node_num);
    n->statement_next->Accept(this);
}
void PrettyPrinter::visit(const BraceStatement *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->statements->Accept(this);
}

void PrettyPrinter::visit(const ASTStatementsList *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    for (auto & statement : *(n->statements)) {
        add_edge(cur_node_num);
        statement->Accept(this);
    }
}
void PrettyPrinter::visit(const ASTBraceStatement *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->statements->Accept(this);
}
void PrettyPrinter::visit(const ReturnStatement *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->exp->Accept(this);
}

// for Types.h

void PrettyPrinter::visit(const IntArrayType *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
}
void PrettyPrinter::visit(const IntType *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
}
void PrettyPrinter::visit(const BooleanType *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
}
void PrettyPrinter::visit(const IdentifierType *n) { ///////// возможно это странно, что она за собой ничего не вызывет
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
}


// for MethodDeclaration.h

void PrettyPrinter::visit(const Argument *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->id->Accept(this);
    add_edge(cur_node_num);
    n->type->Accept(this);
}
void PrettyPrinter::visit(const ArgumentsList *n) {
    int cur_node_num = node_num;
    if (n->var_val == nullptr) {
        add_node(cur_node_num, "Empty Arguments list");
        return;
    }
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->var_val->Accept(this);
    if (n->var_next == nullptr) {
        return;
    }
    add_edge(cur_node_num);
    n->var_next->Accept(this);
}
void PrettyPrinter::visit(const MethodDeclaration *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->type->Accept(this);
    add_edge(cur_node_num);
    n->id->Accept(this);
    add_edge(cur_node_num);
    n->exp->Accept(this);
    add_edge(cur_node_num);
    n->statements->Accept(this);
    add_edge(cur_node_num);
    n->args->Accept(this);
    add_edge(cur_node_num);
    n->vars->Accept(this);
}
void PrettyPrinter::visit(const MethodDeclarationsList *n) {
    int cur_node_num = node_num;
    if (n->method_val == nullptr) {
        add_node(cur_node_num, "Empty MethodDeclarations list");
        return;
    }
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->method_val->Accept(this);
    if (n->method_next == nullptr) {
        return;
    }
    add_edge(cur_node_num);
    n->method_next->Accept(this);
}

void PrettyPrinter::visit(const ASTMethodDeclaration *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->type->Accept(this);
    add_edge(cur_node_num);
    n->id->Accept(this);
    add_edge(cur_node_num);
    n->args->Accept(this);
    add_edge(cur_node_num);
    n->vars->Accept(this);
    add_edge(cur_node_num);
    n->statements->Accept(this);
    add_edge(cur_node_num);
    n->exp->Accept(this);
}

void PrettyPrinter::visit(const ASTArgumentsList *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    for (auto & argument : *(n->arguments)) {
        add_edge(cur_node_num);
        argument->Accept(this);
    }
}

void PrettyPrinter::visit(const ASTMethodsList *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    for (auto & method : *(n->methods)) {
        add_edge(cur_node_num);
        method->Accept(this);
    }
}

// for VarDeclaration.h

void PrettyPrinter::visit(const VarDeclaration *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->id->Accept(this);
    add_edge(cur_node_num);
    n->type->Accept(this);
}
void PrettyPrinter::visit(const VarDeclarationsList *n) {
    int cur_node_num = node_num;
    if (n->var_val == nullptr) {
        add_node(cur_node_num, "Empty VarDeclarations list");
        return;
    }
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->var_val->Accept(this);
    if (n->var_next == nullptr) {
        return;
    }
    add_edge(cur_node_num);
    n->var_next->Accept(this);
}

void PrettyPrinter::visit(const ASTVarDeclarations *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    for (auto & var : *(n->vars)) {
        add_edge(cur_node_num);
        var->Accept(this);
    }
}


// for ClassDeclaration.h

void PrettyPrinter::visit(const ClassDeclaration *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->i1->Accept(this);
    add_edge(cur_node_num);
    n->ext->Accept(this);
    add_edge(cur_node_num);
    n->methods->Accept(this);
    add_edge(cur_node_num);
    n->vars->Accept(this);
}
void PrettyPrinter::visit(const MainClass *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->id1->Accept(this);
    add_edge(cur_node_num);
    n->id2->Accept(this);
    add_edge(cur_node_num);
    n->statement->Accept(this);
}
void PrettyPrinter::visit(const ClassDeclarationsList *n) {
    int cur_node_num = node_num;
    if (n->class_val == nullptr) {
        add_node(cur_node_num, "Empty ClassDeclarations list");
        return;
    }
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->class_val->Accept(this);
    if (n->class_next == nullptr) {
        return;
    }
    add_edge(cur_node_num);
    n->class_next->Accept(this);
}
void PrettyPrinter::visit(const Extends *n) {
    int cur_node_num = node_num;
    if (n->id == nullptr) {
        add_node(cur_node_num, "No inheritance");
        return;
    }
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->id->Accept(this);
}

void PrettyPrinter::visit(const ASTClassDeclarations *n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    for (auto & classe : *(n->classes)) {
        add_edge(cur_node_num);
        classe->Accept(this);
    }
}

// for Goal.h

void PrettyPrinter::visit(std::unique_ptr<Goal>& n) {
    int cur_node_num = node_num;
    add_node(cur_node_num, n->Name());
    add_edge(cur_node_num);
    n->mainClass->Accept(this);
    add_edge(cur_node_num);
    n->classes->Accept(this);
}
