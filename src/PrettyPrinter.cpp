#include "PrettyPrinter.h"

PrettyPrinter::PrettyPrinter(FILE *output) : node_num(0), cur_node_num(0) {
  f = output;
  fprintf(f, "%s", "strict graph G{\n");
}

PrettyPrinter::~PrettyPrinter() {
  fprintf(f, "%s", "}");
  fclose(f);
}

void PrettyPrinter::add_edge() {
  fprintf(f, "%d -- %d;\n", cur_node_num, node_num++);}

void PrettyPrinter::add_node(const char *name) {
  cur_node_num = node_num;
  fprintf(f, "%d [label=\"%s\"];\n", cur_node_num, name);

}

// for Expressions.h

void PrettyPrinter::visit(const PlusExp *n) {
  add_node(n->Name());
  add_edge();
  n->e1->Accept(this);
  add_edge();
  n->e2->Accept(this);
}
void PrettyPrinter::visit(const MinusExp *n) {
  add_node(n->Name());
  add_edge();
  n->e1->Accept(this);
  add_edge();
  n->e2->Accept(this);
}
void PrettyPrinter::visit(const TimesExp *n) {
  add_node(n->Name());
  add_edge();
  n->e1->Accept(this);
  add_edge();
  n->e2->Accept(this);
}
void PrettyPrinter::visit(const DivideExp *n) {
  add_node(n->Name());
  add_edge();
  n->e1->Accept(this);
  add_edge();
  n->e2->Accept(this);
}
void PrettyPrinter::visit(const AddExp *n) {
  add_node(n->Name());
  add_edge();
  n->e1->Accept(this);
  add_edge();
  n->e2->Accept(this);
}
void PrettyPrinter::visit(const LessExp *n) {
  add_node(n->Name());
  add_edge();
  n->e1->Accept(this);
  add_edge();
  n->e2->Accept(this);
}
void PrettyPrinter::visit(const IndexExp *n) {
  add_node(n->Name());
  add_edge();
  n->e1->Accept(this);
  add_edge();
  n->e2->Accept(this);
}
void PrettyPrinter::visit(const LengthExp *n) {
  add_node(n->Name());
  add_edge();
  n->e1->Accept(this);
}
void PrettyPrinter::visit(const CallMethodExp *n) {
  add_node(n->Name());
  add_edge();
  n->e1->Accept(this);
  add_edge();
  n->i1->Accept(this);
  add_edge();
  n->e2->Accept(this);
  add_edge();
  n->e3->Accept(this);
  add_edge();
  //
  //
  //
  //
  //   PEREDELAT!  PEREDELAT!  PEREDELAT!  PEREDELAT!  PEREDELAT!  PEREDELAT!  PEREDELAT!
  //
  //
  //
}
void PrettyPrinter::visit(const IntExp *n) {
  add_node(n->Name());
  add_edge();
  fprintf(f, "%d [label=\"%d\"];\n", node_num, n->num);
}
void PrettyPrinter::visit(const TrueExp *n) {
  add_node("BoolExp");
  add_edge();
  fprintf(f, "%d [label=\"%s\"];\n", node_num, n->Name());
}

void PrettyPrinter::visit(const FalseExp *n) {
  add_node("BoolExp");
  add_edge();
  fprintf(f, "%d [label=\"%s\"];\n", node_num, n->Name());
}

void PrettyPrinter::visit(const IdExp *n) {
  add_node(n->Name());
  add_edge();
  n->i1->Accept(this);
}

void PrettyPrinter::visit(const ThisExp *n) {
  add_node(n->Name());
  add_edge();
  fprintf(f, "%d [label=\"this\"];\n", node_num);
}

void PrettyPrinter::visit(const NewIntExp *n) {
  add_node(n->Name());
  add_edge();
  n->e1->Accept(this);
}

void PrettyPrinter::visit(const NewIdExp *n) {
  add_node(n->Name());
  add_edge();
  n->i1->Accept(this);
}

void PrettyPrinter::visit(const NotExp *n) {
  add_node(n->Name());
  add_edge();
  n->e1->Accept(this);
}


// for Identifiers.h

void PrettyPrinter::visit(const Identifier *n) {
  add_node(n->Name());
  add_edge();
  fprintf(f, "%d [label=\"%s\"];\n", node_num, n->id);
}


// for Statements.h

void PrettyPrinter::visit(const IfStatement *n) {
  add_node(n->Name());
  add_edge();
  n->exp->Accept(this);
  add_edge();
  n->statement1->Accept(this);
  add_edge();
  n->statement2->Accept(this);
}
void PrettyPrinter::visit(const WhileStatement *n) {
  add_node(n->Name());
  add_edge();
  n->exp->Accept(this);
  add_edge();
  n->statement->Accept(this);
}
void PrettyPrinter::visit(const OutputStatement *n) {
  add_node(n->Name());
  add_edge();
  n->exp->Accept(this);
}
void PrettyPrinter::visit(const AssignStatement *n) {
  add_node(n->Name());
  add_edge();
  n->identifier->Accept(this);
  add_edge();
  n->exp->Accept(this);
}
void PrettyPrinter::visit(const ArrayAssignStatement *n) {
  add_node(n->Name());
  add_edge();
  n->identifier->Accept(this);
  add_edge();
  n->exp1->Accept(this);
  add_edge();
  n->exp2->Accept(this);
}
void PrettyPrinter::visit(const StatementsList *n) {
  add_node(n->Name());
  add_edge();
  n->statement_val->Accept(this);
  add_edge();
  n->statement_next->Accept(this);
}