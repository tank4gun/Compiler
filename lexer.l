%option noyywrap

%{
#include <stdio.h>
%}

%%
stop    printf("Получена команда stop\n");
start   printf("Получена команда start\n");
%%

main(int argc, char **argv)
{
    yylex();
}