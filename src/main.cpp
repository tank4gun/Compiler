#include <cstdio>
#include <cstdlib>
#include "Goal.h"
#include "PrettyPrinter.h"

extern int yyparse();
extern FILE *yyin;

Goal *maingoal;

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");
    if (input == nullptr) {
        printf("Can not open file!\n");
        exit(1);
    }
    yyin = input;
    yyparse();

    FILE *output = fopen("output.dot", "w");
    PrettyPrinter *printer = new PrettyPrinter(output);
    printer->visit(maingoal);
    delete printer;

    fclose(output);
    fclose(yyin);

    return 0;
}