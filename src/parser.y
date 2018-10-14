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


Goal :
    | MainClass Classes {printf("Goal\n");}

Classes : %empty
    | Classes ClassDeclaration {printf("ClassDeclaration\n");}

MainClass :
    | CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPAREN STRING LSQBRACKET RSQBRACKET Identifier RPAREN LBRACE Statement RBRACE RBRACE {printf("MainClass\n");}

ClassDeclaration :
    | CLASS Identifier Extends LBRACE Variables Methods RBRACE {printf("ClassDeclaration\n");}

Extends : %empty
    | EXTENDS Identifier {printf("Extends\n");}

Variables : %empty
    | Variables VarDeclaration {printf("VarDeclaration\n");}

Methods : %empty
    | Methods MethodDeclaration {printf("MethodDeclaration\n");}

VarDeclaration :
    | Type Identifier SEMICOLON {printf("VarDeclaration\n");}

MethodDeclaration :
    | PUBLIC Type Identifier LPAREN Arguments RPAREN LBRACE Variables Statements RETURN Expression SEMICOLON RBRACE {printf("MethodDeclaration\n");}

Arguments : %empty
    | Type Identifier AdditionalArgs {printf("Argument\n");}

AdditionalArgs : %empty
    | AdditionalArgs COMMA Type Identifier {printf("AdditionalArg\n");}

Type :
    | INT LSQBRACKET RSQBRACKET {printf("Massive of ints\n");}
    | BOOLEAN   {printf("Bool\n");}
    | INT   {printf("Int\n");}
    | Identifier    {printf("Identifier\n");}

Statement :
    | LBRACE Statements RBRACE  {printf("Statements\n");}
    | IF LPAREN Expression RPAREN Statement ELSE Statement  {printf("If-else statement\n");}
    | WHILE LPAREN Expression RPAREN Statement  {printf("While statement\n");}
    | OUTPUT LPAREN Expression RPAREN SEMICOLON {printf("Print expression\n");}
    | Identifier ASSIGN Expression SEMICOLON    {printf("Assign identifier\n");}
    | Identifier LSQBRACKET Expression RSQBRACKET ASSIGN Expression SEMICOLON   {printf("Assign massive element\n");}

Statements:
    %empty
    | Statements Statement
%%

extern int lineIndex, charIndex;


void yyerror (char *s) {
    printf("%s\n", s);
}