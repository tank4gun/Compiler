#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "ST-AST/Goal.h"
#include "ST-AST/PrettyPrinter.h"
#include "ST-AST/ASTBuilder.h"
#include "StringConverter.h"
#include "SymbolTable/STableBuilder.h"
#include "IRTree/Translator.h"
#include "IRTree/IRTreePrinter.h"
#include "SymbolTable/TypeChecker.h"
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <CanonicalTree/CallCanonizer.h>
#include <CanonicalTree/ESEQCanonizer.h>
#include <CanonicalTree/SEQCanonizer.h>

void read_directory(const std::string& name, std::vector<std::string>& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    if (dirp == NULL) {
        exit(100);
    }
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}


extern int yyparse();
extern void yylex_destroy();
extern FILE *yyin;
extern bool hasLexErrors;

std::unique_ptr<Goal> maingoal;
std::vector<std::string> errors;

StringConverter stringConverter;



int main(int argc, char *argv[]) {


    FILE *input = fopen("src/data/Samples/Factorial.java", "r");
//        FILE *input = fopen(argv[1], "r");
        if (input == nullptr) {
            printf("Can not open file!\n");
            exit(1);
        }
        yyin = input;
        yyparse();

        if (hasLexErrors) {
            hasLexErrors = false;
            fclose(yyin);
            yylex_destroy();
        }
        // Syntax errors checking:
        if (errors.empty()) {
            std::cout << "No syntax errors" << std::endl;
        } else {
            std::cout << "Syntax errors:" << std::endl;
            for (const auto &error : errors) {
                std::cout << error << std::endl;
            }
            errors.clear();
            fclose(yyin);
            yylex_destroy();
        }

        ASTBuilder *builder = new ASTBuilder();
        builder->visit(maingoal);
        std::unique_ptr<ASTGoal> tree_head = std::move(builder->astgoal_pointer);
        delete builder;

        STableBuilder *sTableBuilder = new STableBuilder();
        sTableBuilder->visit(tree_head);
        sTableBuilder->printErrors();

        if (!sTableBuilder->hasErrors()) {
            TypeChecker typeChecker(sTableBuilder->getTable());
            typeChecker.visit(tree_head);
            typeChecker.printErrors();
        }

        Translator *translator = new Translator(sTableBuilder->getTable());
        translator->visit(tree_head);

        for (auto &codeFragment : translator->codeFragments) {
            std::string name = codeFragment.second.frame->Name() + ".txt";
            IRTreePrinter builder(name.c_str());
            codeFragment.second.body->Accept(&builder);

            CallCanonizer* cc = new CallCanonizer();
            codeFragment.second.body->Accept(cc);
            IIRStm* root_canon = cc->getRoot();

            ESEQCanonizer* eseqc = new ESEQCanonizer();
            codeFragment.second.body->Accept(eseqc);
            IIRStm* root_eseq = eseqc->CanonicalTree();

            SEQCanonizer* seqc = new SEQCanonizer();
            codeFragment.second.body->Accept(seqc);
            IIRStm* root_seq = seqc->CanonicalTree();

            break;
        }


    delete translator;
        fclose(yyin);
        yylex_destroy();
        delete (sTableBuilder);






//    std::vector<std::string> files;
//    read_directory("./src/data/Samples/", files);
//    for (auto & file : files) {
//        if (file[0] == '.') {
//            continue;
//        }
//        std::cout << std::endl << std::endl << file << std::endl << std::endl;
//
//        std::string path = "src/data/Samples/" + file;
//        FILE *input = fopen(path.c_str(), "r");
////        FILE *input = fopen(argv[1], "r");
//        if (input == nullptr) {
//            printf("Can not open file!\n");
//            exit(1);
//        }
//        yyin = input;
//        yyparse();
//
//        if (hasLexErrors) {
//            hasLexErrors = false;
//            fclose(yyin);
//            yylex_destroy();
//            continue;
//        }
//        // Syntax errors checking:
//        if (errors.empty()) {
//            std::cout << "No syntax errors" << std::endl;
//        } else {
//            std::cout << "Syntax errors:" << std::endl;
//            for (const auto &error : errors) {
//                std::cout << error << std::endl;
//            }
//            errors.clear();
//            fclose(yyin);
//            yylex_destroy();
//            continue;
//        }
//
//        ASTBuilder *builder = new ASTBuilder();
//        builder->visit(maingoal);
//        std::unique_ptr<ASTGoal> tree_head = std::move(builder->astgoal_pointer);
//        delete builder;
//
//        STableBuilder *sTableBuilder = new STableBuilder();
//        sTableBuilder->visit(tree_head);
//        sTableBuilder->printErrors();
//
//        if (!sTableBuilder->hasErrors()) {
//            TypeChecker typeChecker(sTableBuilder->getTable());
//            typeChecker.visit(tree_head);
//            typeChecker.printErrors();
//        }
//
//        FILE *output1 = fopen("ast.dot", "w");
//        PrettyPrinter *printer1 = new PrettyPrinter(output1);
//        printer1->visit(tree_head);
//        delete printer1;
//        fclose(yyin);
//        yylex_destroy();
//        delete (sTableBuilder);
//    }
//    return 0;
}