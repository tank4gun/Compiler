%{
#include <stdio.h>
#include <string>
%}

%union
{
    int int_num;
    std::string id_name;
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
    | OUTPUT {}
    | PUBLIC {}
    | PRIVATE {}
    | STATIC {}
    | VOID {}
    | MAIN {}
    | EXTENDS {}
    | TRUE {}
    | FALSE {}
    | THIS {}
    | NEW {}
    | IF {}
    | ELSE {}
    | WHILE {}
    | INT {}
    | BOOLEAN {}
    | STRING {}
    | NUMBER {}
    | IDENTIFIER {}
;
%%



int main() {
    yyparse();
}
/*
void yyerror (char *s) {
    printf (”%s\n”, s);
}
*/