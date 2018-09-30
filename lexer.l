%option noyywrap
%{
#include <stdio.h>
%}

%%
stop    printf("Получена команда stop\n");
start   printf("Получена команда start\n");
%%

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