//
// Created by elena on 01.10.18.
//

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern FILE* yyin;


int main(int argc, char *argv[])
{
    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Can not open file!\n");
        exit(1);
    }
    yyin = input;
    yylex();
    fclose(yyin);

    return 0;
}