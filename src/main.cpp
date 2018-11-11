#include <cstdio>
#include <cstdlib>
#include "Goal.h"
#include "PrettyPrinter.h"
#include "ASTBuilder.h"

extern int yyparse();
extern FILE *yyin;

std::unique_ptr<Goal> maingoal;

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
//    maingoal = builder->goal_pointer;
    std::unique_ptr<Goal> tree_head = std::move(builder->goal_pointer);
    delete builder;
    FILE *output1 = fopen("ast.dot", "w");
    PrettyPrinter *printer1 = new PrettyPrinter(output1);
    printer1->visit(maingoal);
    delete printer1;
    fclose(yyin);

    return 0;
}