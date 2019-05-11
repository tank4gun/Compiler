#include <iostream>
#include "IRTreePrinter.h"

IRTreePrinter::IRTreePrinter(const std::string &path) : nodeNumber(0) {
    f = fopen(path.c_str(), "w+");
    fprintf(f, "%s", "strict graph G{\n");
}

IRTreePrinter::~IRTreePrinter() {
    fprintf(f, "%s", "}");
    fclose(f);
}

void IRTreePrinter::visit(const ConstExp *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"CONST\\n%d\"];\n", cur, n->value);
}

void IRTreePrinter::visit(const NameExp *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"NAME\\n%s\"];\n", cur, n->label.label.c_str());
}

void IRTreePrinter::visit(const TempExp *n) {
    int cur = nodeNumber;
    std::string tmpLabel = n->value.label;
    fprintf(f, "%d [label=\"TEMP\\n%s\"];\n", cur, tmpLabel.c_str());
}

void IRTreePrinter::visit(const BinaryExp *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"%s\"];\n", cur, n->getType().c_str());
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->leftExp->Accept(this);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->rightExp->Accept(this);
}

void IRTreePrinter::visit(const MemoryExp *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"MEM\"];\n", cur);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->exp->Accept(this);
}

void IRTreePrinter::visit(const CallExp *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"CALL\"];\n", cur);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->funcExp->Accept(this);
    const auto &arguments = n->args->expressions;
    for (const auto &arg : arguments) {
        nodeNumber++;
        fprintf(f, "%d -- %d;\n", cur, nodeNumber);
        arg->Accept(this);
    }
}

void IRTreePrinter::visit(const ESeqExp *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"ESEQ\"];\n", cur);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->exp->Accept(this);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->stm->Accept(this);
}

void IRTreePrinter::visit(const MoveStm *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"MOVE\"];\n", cur);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->from->Accept(this);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->to->Accept(this);
}

void IRTreePrinter::visit(const ExpStm *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"EXP\"];\n", cur);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->exp->Accept(this);
}

void IRTreePrinter::visit(const JumpStm *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"JUMP\\n%s\"];\n", cur, n->target.label.c_str());
}

void IRTreePrinter::visit(const CJumpStm *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"CJUMP\\n%s\"];\n", cur, n->getType().c_str());
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->exp1->Accept(this);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->exp2->Accept(this);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    fprintf(f, "%d [label=\"iftrue\\n%s\"];\n", nodeNumber, n->labelTrue.label.c_str());
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    fprintf(f, "%d [label=\"iffalse\\n%s\"];\n", nodeNumber, n->labelFalse.label.c_str());
}

void IRTreePrinter::visit(const SeqStm *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"SEQ\"];\n", cur);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->leftStm->Accept(this);
    nodeNumber++;
    fprintf(f, "%d -- %d;\n", cur, nodeNumber);
    n->rightStm->Accept(this);
}

void IRTreePrinter::visit(const LabelStm *n) {
    int cur = nodeNumber;
    fprintf(f, "%d [label=\"LABEL\\n%s\"];\n", cur, n->label.label.c_str());
}
void IRTreePrinter::visit(const IRStmList *n) {
    int cur = nodeNumber;
    fprintf( f, "%d [label=\"StmList\"];\n", cur );
    std::unique_ptr<IRStmList> newStmList( new IRStmList );
    for( auto& expression : n->statements ) {
        nodeNumber++;
        fprintf( f, "%d -- %d;\n", cur, nodeNumber );
        expression->Accept( this );
    }

}
