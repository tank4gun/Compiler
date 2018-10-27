%option noyywrap
%option header-file="src/lexer.h"

%{
#include <stdio.h>
#include <string>

#include "Expressions.h"
#include "Identifiers.h"
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
//    printf("%s", str.c_str());
//    print_coord();
}

%}

DIGIT           [0-9]
NUM         ({DIGIT})+
CHAR            [a-zA-Z_]
CHARSTRING      {CHAR}+
ID      {CHARSTRING}({CHARSTRING}|{NUM})*

%%
\n      {print_output("NEW_LINE"); printf("\n"); ++lineIndex; charIndex = 0;}
[ \t]   {++charIndex;}//  Token TAB
class   {print_output("CLASS"); return CLASS;}
\{      {print_output("LBRACE"); return LBRACE;}
\}      {print_output("RBRACE"); return RBRACE;}
\(      {print_output("LPAREN"); return LPAREN;}
\)      {print_output("RPAREN"); return RPAREN;}
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
\!      {print_output("EXCL_MARK"); return EXCL_MARK;}

\.length  {print_output("DOTLENGTH"); return DOTLENGTH;}

public  {print_output("PUBLIC"); return PUBLIC;}
static  {print_output("STATIC"); return STATIC;}
void    {print_output("VOID"); return VOID;}
main    {print_output("MAIN"); return MAIN;}
extends {print_output("EXTENDS"); return EXTENDS;}
true    {print_output("TRUE"); return TRUE;}
false   {print_output("FALSE"); return FALSE;}
this    {print_output("THIS"); return THIS;}
new     {print_output("NEW"); return NEW;}
if      {print_output("IF"); return IF;}
else    {print_output("ELSE"); return ELSE;}
while   {print_output("WHILE"); return WHILE;}
return  {print_output("RETURN"); return RETURN;}

System.out.println {print_output("OUTPUT"); return OUTPUT;}
int {print_output("TYPE(INT)"); return INT;}
boolean {print_output("TYPE(BOOLEAN"); return BOOLEAN;}
String {print_output("TYPE(STRING)"); return STRING;}

{ID}    {/*printf("ID(%s)", yytext); print_coord();*/ yylval.id_name = yytext; return IDENTIFIER;}
{NUM}   {/*printf("Number(%s)", yytext); print_coord();*/yylval.int_num = atoi(yytext); return NUMBER;}

<<EOF>> { /*printf("END_OF_FILE");*/ yyterminate(); }

. {yyterminate();}
%%
