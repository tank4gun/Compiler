%option noyywrap

%{
#include <stdio.h>
int lineIndex = 0;
int charIndex = 0;
void print_coord() {
    printf("(%d.%d-%d) ", lineIndex, charIndex, charIndex + yyleng - 1);
    charIndex += yyleng;
}
%}

%%
stop    {printf("STOP"); print_coord();}
start   {printf("START"); print_coord();}
\n      {printf("NEW_LINE"); print_coord(); printf("\n"); ++lineIndex; charIndex = 0;}
[ \t]     {++charIndex;}
%%

int main(int argc, char **argv)
{
    yylex();
}