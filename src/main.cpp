#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "ST-AST/Goal.h"
#include "ST-AST/PrettyPrinter.h"
#include "ST-AST/ASTBuilder.h"
#include "StringConverter.h"
#include "SymbolTable/STableBuilder.h"

extern int yyparse();
extern FILE *yyin;

std::unique_ptr<Goal> maingoal;

StringConverter stringConverter;
int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");
    if (input == nullptr) {
        printf("Can not open file!\n");
        exit(1);
    }
    yyin = input;
    yyparse();
    ASTBuilder *builder = new ASTBuilder();
    builder->visit(maingoal);
    std::unique_ptr<Goal> tree_head = std::move(builder->goal_pointer);
    delete builder;

    STableBuilder *sTableBuilder = new STableBuilder();
    sTableBuilder->visit(tree_head);
    std::cout << "\n\n\n";
    sTableBuilder->printErrors();


//    FILE *output1 = fopen("ast.dot", "w");
//    PrettyPrinter *printer1 = new PrettyPrinter(output1);
//    printer1->visit(tree_head);
//    delete printer1;
//    fclose(yyin);

    return 0;
}