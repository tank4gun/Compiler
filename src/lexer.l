%option noyywrap
%option header-file="src/lexer.h"

%{
#include <stdio.h>
#include <string>

#include "ST-AST/Expressions.h"
#include "ST-AST/Identifiers.h"
#include "parser.hpp"


void yyerror(char *s);
void yyerror(char *s, int lineIndex, int charIndex);
// example: yyerror("error_message_here", lineIndex, charIndex + 1);

int lineIndex = 1;
int charIndex = 0;

void update_crd() {
    charIndex += yyleng;
}

%}

DIGIT           [0-9]
NUM             ({DIGIT})+
CHAR            [a-zA-Z_]
CHARSTRING      {CHAR}+
ID              {CHARSTRING}({CHARSTRING}|{NUM})*



%%
\n      {++lineIndex; charIndex = 0;}
[ \t]   {++charIndex;}  // Token TAB
class   {update_crd(); return CLASS;}
\{      {update_crd(); return LBRACE;}
\}      {update_crd(); return RBRACE;}
\(      {update_crd(); return LPAREN;}
\)      {update_crd(); return RPAREN;}
\[      {update_crd(); return LSQBRACKET;}
\]      {update_crd(); return RSQBRACKET;}
\=      {update_crd(); return ASSIGN;}
\+      {update_crd(); return PLUS;}
\-      {update_crd(); return MINUS;}
\*      {update_crd(); return MULTIPLY;}
\<      {update_crd(); return LESS;}
\&&     {update_crd(); return AND;}
\,      {update_crd(); return COMMA;}
\;      {update_crd(); return SEMICOLON;}
\.      {update_crd(); return DOT;}
\!      {update_crd(); return EXCL_MARK;}

\.length  {update_crd(); return DOTLENGTH;}

public  {update_crd(); return PUBLIC;}
static  {update_crd(); return STATIC;}
void    {update_crd(); return VOID;}
main    {update_crd(); return MAIN;}
extends {update_crd(); return EXTENDS;}
true    {update_crd(); return TRUE;}
false   {update_crd(); return FALSE;}
this    {update_crd(); return THIS;}
new     {update_crd(); return NEW;}
if      {update_crd(); return IF;}
else    {update_crd(); return ELSE;}
while   {update_crd(); return WHILE;}
return  {update_crd(); return RETURN;}

System.out.println  {update_crd(); return OUTPUT;}
int                 {update_crd(); return INT;}
boolean             {update_crd(); return BOOLEAN;}
String              {update_crd(); return STRING;}

"//".*"\n" {}

{ID}    {yylval.id_name = yytext; update_crd(); return IDENTIFIER;}
{NUM}   {yylval.int_num = atoi(yytext); update_crd(); return NUMBER;}

<<EOF>> { yyterminate(); }

. { yyerror("Unknown symbol\n"); }
%%
