%option noyywrap
%option outfile="lexer.cpp" header-file="lexer.h"

%{
#include <cstdio>
#include <string>
#include "parser.hpp"


int lineIndex = 0;
int charIndex = 0;

void print_coord() {
    printf("(%d.%d-%lu) ", lineIndex, charIndex, charIndex + yyleng - 1);
    charIndex += yyleng;
}

void print_type(std::string str_type) {
    printf("TYPE(%s)", str_type.c_str());
    print_coord();
}

std::string to_upper(std::string str) {
    for(int i = 0; i < str.size(); i++) {
        str[i] += 'A' - 'a';
    }
    return str;
}

void print_upper_token(std::string token_name) {
    printf("%s", to_upper(token_name).c_str());
    print_coord();
}

void print_output(std::string str) {
    printf("%s", str.c_str());
    print_coord();
}

%}

DIGIT           [0-9]
NUMBER          ({DIGIT})+
CHAR            [a-zA-Z_]
CHARSTRING      {CHAR}+
IDENTIFIER      {CHARSTRING}({CHARSTRING}|{NUMBER})*

%%
\n      {print_output("NEW_LINE"); printf("\n"); ++lineIndex; charIndex = 0; return NEW_LINE;}
[ \t]   {++charIndex; return TAB;}//  Token TAB
class   {print_output("CLASS"); return CLASS;}
\{      {print_output("LPAREN"); return LPAREN;} //print_output("LPAREN");
\}      {print_output("RPAREN"); return RPAREN;}
\(      {print_output("LBRACE"); return LBRACE;}
\)      {print_output("RBRACE"); return RBRACE;}
\[      {print_output("LSQBRACKET"); return LSQBRACKET;}
\]      {print_output("RSQBRACKET"); return RSQBRACKET;}
\=      {print_output("ASSIGN"); return ASSIGN;}
\+      {print_output("PLUS"); return PLUS;}
\-      {print_output("MINUS"); return MINUS;}
\*      {print_output("MULTIPLY"); return MULTIPLY;}
\<      {print_output("LESS"); return LESS;}
\&&     {print_output("AND"); return AND;}
\,      {print_output("COMMA"); return COMMA;}
\;      {print_output("SEMICOLON"); return SEMICOLON;}
\.      {print_output("DOT"); return DOT;}

public|private|static|void|main|extends|true|false|this|new|if|else|while   print_upper_token(yytext);
System.out.println                                                          print_output("OUTPUT");
int|boolean|String                                                          print_type(yytext);

{IDENTIFIER}    {printf("ID(%s)", yytext); print_coord();}
{NUMBER}        {printf("Number(%s)", yytext); print_coord();}
%%
