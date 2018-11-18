//
// Created by elena on 18.11.18.
//

#include "STableBuilder.h"

STableBuilder::STableBuilder(): table(new Table()), classInfo(nullptr), variableInfo(nullptr), methodInfo(nullptr) {
}

void STableBuilder::visit(std::unique_ptr<Goal> &n) {
    n->mainClass->Accept(this);
    n->classes->Accept(this);
}
void STableBuilder::visit(const ASTClassDeclarations *n) {
    for (auto & classe : *(n->classes)) {
        classe->Accept(this);
    }
}

