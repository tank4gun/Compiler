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
    fprintf(f, "%d -- %d;\n", cur_node_num, node_num++);
}

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
void PrettyPrinter::visit(const AndExp *n) {
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
void PrettyPrinter::visit(const ParenExp *n) {
    add_node(n->Name());
    add_edge();
    n->e1->Accept(this);
}
void PrettyPrinter::visit(const ExpList *n) {
    add_node(n->Name());
    add_edge();
    n->exp_next->Accept(this);
    add_edge();
    n->exp_val->Accept(this);
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
void PrettyPrinter::visit(const BraceStatement *n) {
    add_node(n->Name());
    add_edge();
    n->statements->Accept(this);
}


// for Types.h

void PrettyPrinter::visit(const IntArrayType *n) {
    add_node(n->Name());
}
void PrettyPrinter::visit(const IntType *n) {
    add_node(n->Name());
}
void PrettyPrinter::visit(const BooleanType *n) {
    add_node(n->Name());
}
void PrettyPrinter::visit(const IdentifierType *n) {
    add_node(n->Name());
}


// for MethodDeclaration.h

void PrettyPrinter::visit(const Argument *n) {
    add_node(n->Name());
    add_edge();
    n->id->Accept(this);
    add_edge();
    n->type->Accept(this);
}
void PrettyPrinter::visit(const ArgumentsList *n) {
    add_node(n->Name());
    add_edge();
    n->var_next->Accept(this);
    add_edge();
    n->var_val->Accept(this);
}
void PrettyPrinter::visit(const MethodDeclaration *n) {
    add_node(n->Name());
    add_edge();
    n->type->Accept(this);
    add_edge();
    n->id->Accept(this);
    add_edge();
    n->exp->Accept(this);
    add_edge();
    n->statements->Accept(this);
    add_edge();
    n->args->Accept(this);
    add_edge();
    n->vars->Accept(this);
    add_edge();
}
void PrettyPrinter::visit(const MethodDeclarationsList *n) {
    add_node(n->Name());
    add_edge();
    n->method_next->Accept(this);
    add_edge();
    n->method_val->Accept(this);
}


// for VarDeclaration.h

void PrettyPrinter::visit(const VarDeclaration *n) {
    add_node(n->Name());
    add_edge();
    n->id->Accept(this);
    add_edge();
    n->type->Accept(this);
}
void PrettyPrinter::visit(const VarDeclarationsList *n) {
    add_node(n->Name());
    add_edge();
    n->var_val->Accept(this);
    add_edge();
    n->var_next->Accept(this);
}


// for ClassDeclaration.h

void PrettyPrinter::visit(const ClassDeclaration *n) {
    add_node(n->Name());
    add_edge();
    n->i1->Accept(this);
    add_edge();
    n->i2->Accept(this);
    add_edge();
    n->methods->Accept(this);
    add_edge();
    n->vars->Accept(this);
}
void PrettyPrinter::visit(const MainClass *n) {
    add_node(n->Name());
    add_edge();
    n->id1->Accept(this);
    add_edge();
    n->id2->Accept(this);
    add_edge();
    n->statement->Accept(this);
}
void PrettyPrinter::visit(const ClassDeclarationsList *n) {
    add_node(n->Name());
    add_edge();
    n->class_val->Accept(this);
    add_edge();
    n->class_next->Accept(this);
}


// for Goal.h

void PrettyPrinter::visit(const Goal *n) {
    add_node(n->Name());
    add_edge();
    n->mainClass->Accept(this);
    add_edge();
    n->classes->Accept(this);
}
