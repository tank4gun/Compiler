%{
#include <stdio.h>
#include <string>
#include "lexer.h"

void yyerror(char *s);

%}



%union
{
    int int_num;
    char* id_name;
}

%start program_start

%token NEW_LINE
%token TAB
%token CLASS
%token LPAREN
%token RPAREN
%token LBRACE
%token RBRACE
%token LSQBRACKET
%token RSQBRACKET
%token ASSIGN
%token PLUS
%token MINUS
%token MULTIPLY
%token LESS
%token AND
%token COMMA
%token SEMICOLON
%token DOT
%token OUTPUT

%token PUBLIC PRIVATE STATIC VOID MAIN EXTENDS TRUE FALSE THIS NEW IF ELSE WHILE
%token INT BOOLEAN STRING

%token <int_num> NUMBER
%token <id_name> IDENTIFIER

%%

program_start :
    | OUTPUT program_start {}
    | PUBLIC program_start {}
    | PRIVATE program_start {}
    | STATIC program_start {}
    | VOID program_start {}
    | MAIN program_start {}
    | EXTENDS program_start {}
    | TRUE program_start {}
    | FALSE program_start {}
    | THIS program_start {}
    | NEW program_start {}
    | IF program_start {}
    | ELSE program_start {}
    | WHILE program_start {}
    | INT program_start {}
    | BOOLEAN program_start {}
    | STRING program_start {}
    | NUMBER program_start {}
    | IDENTIFIER program_start {}
    | NEW_LINE program_start {}
    | TAB program_start {}
    | CLASS program_start {}
    | LPAREN program_start {}
    | RPAREN program_start {}
    | LBRACE program_start {}
    | RBRACE program_start {}
    | LSQBRACKET program_start {}
    | RSQBRACKET program_start {}
    | ASSIGN program_start {}
    | PLUS program_start {}
    | MINUS program_start {}
    | MULTIPLY program_start {}
    | LESS program_start {}
    | AND program_start {}
    | COMMA program_start {}
    | SEMICOLON program_start {}
    | DOT program_start {}
    | OUTPUT program_start {}
%%

extern int lineIndex, charIndex;


void yyerror (char *s) {
    printf("%s\n", s);
}