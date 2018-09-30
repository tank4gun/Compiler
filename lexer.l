%option noyywrap
%{
#include <stdio.h>
int lineIndex = 0;
int charIndex = 0;
void print_coord() {
    printf("(%d.%d-%d) ", lineIndex, charIndex, charIndex + yyleng - 1);
    charIndex += yyleng;
}
#include <cstdio>
#include <string>

DIGIT           [0-9]
NUMBER          (DIGIT)+
CHAR            [a-zA-Z]
CHARSTRING      (CHAR)+
IDENTIFIER      (CHARSTRING)(CHARSTRING|NUMBER)*
void print_type(std::string str_type) {
    printf("TYPE(%s)", str_type.c_str());
}

std::string to_upper(std::string str) {
    for(int i = 0; i < str.size(); i++) {
        str[i] += 'A' - 'a';
    }
    return str;
}

void print_visible(std::string vis) {
    printf(" %s ", to_upper(vis).c_str());
}
%}

%%
stop    {printf("STOP"); print_coord();}
start   {printf("START"); print_coord();}
\n      {printf("NEW_LINE"); print_coord(); printf("\n"); ++lineIndex; charIndex = 0;}
[ \t]     {++charIndex;}
class   printf("CLASS ");
\{      printf("LPAREN ");
\}      printf("RPAREN ");
\(      printf("LBRACE ");
\)      printf("RBRACE ");
\[      printf("LSQBRACKET ");
\]      printf("RSQBRACKET ");
=       printf("ASSIGN ");
+       printf("PLUS ");
-       printf("MINUS ");
*       printf("MULTIPLY ");
<       printf("LESS ");
&&      printf("AND ");
,       printf("COMMA ");
;       printf("SEMICOLON ");
\.      printf("DOT ");
public|private|static|void|main|extends|true|false|this|new|if|else|while  print_visible(yytext);
System.out.println printf("OUTPUT ")
int|boolean     print_type(yytext);

\n      printf("NEWLINE\n");

stop    printf("Получена команда stop");
start   printf("Получена команда start");
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