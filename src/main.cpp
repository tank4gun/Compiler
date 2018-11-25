#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "ST-AST/Goal.h"
#include "ST-AST/PrettyPrinter.h"
#include "ST-AST/ASTBuilder.h"
#include "StringConverter.h"
#include "SymbolTable/STableBuilder.h"
#include "SymbolTable/TypeChecker.h"

extern int yyparse();
extern FILE *yyin;

std::unique_ptr<Goal> maingoal;
std::vector<std::string> errors;

StringConverter stringConverter;
int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");
    if (input == nullptr) {
        printf("Can not open file!\n");
        exit(1);
    }
    yyin = input;
    yyparse();

    // Syntax errors checking:
    std::cout << "\n";
    if (errors.empty()) {
        std::cout << "No syntax errors" << std::endl;
        std::cout << "\n";
    } else {
        std::cout << "Syntax errors:" << std::endl;
        for (const auto &error : errors) {
            std::cout << error << std::endl;
        }
        exit(-1);
    }


    ASTBuilder *builder = new ASTBuilder();
    builder->visit(maingoal);
    std::unique_ptr<ASTGoal> tree_head = std::move(builder->astgoal_pointer);
    delete builder;

    STableBuilder *sTableBuilder = new STableBuilder();
    sTableBuilder->visit(tree_head);
    std::cout << "\n\n";
    sTableBuilder->printErrors();

    TypeChecker typeChecker(sTableBuilder->getTable());
    typeChecker.visit(tree_head);
    std::cout << "\n\n";
    typeChecker.printErrors();

    FILE *output1 = fopen("ast.dot", "w");
    PrettyPrinter *printer1 = new PrettyPrinter(output1);
    printer1->visit(tree_head);
    delete printer1;
    fclose(yyin);

    return 0;
}