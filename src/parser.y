%{
#include <stdio.h>
#include <string>
#include "lexer.h"

/* #define YYSTYPE string */

void yyerror(char *s);

%}


%union
{
    int int_num;
    char* id_name;
}

%start Goal

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
%token LENGTH
%token EXCL_MARK
%token RETURN

%token PUBLIC PRIVATE STATIC VOID MAIN EXTENDS TRUE FALSE THIS NEW IF ELSE WHILE
%token INT BOOLEAN STRING

%token <int_num> NUMBER
%token <id_name> IDENTIFIER

%%

Goal : MainClass Classes {printf("Goal\n");}

Classes : %empty
    | Classes ClassDeclaration {printf("ClassDeclaration\n");}

MainClass : CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPAREN STRING LSQBRACKET RSQBRACKET Identifier RPAREN LBRACE Statement RBRACE RBRACE {printf("MainClass\n");}

ClassDeclaration : CLASS Identifier Extends LBRACE Variables Methods RBRACE {printf("ClassDeclaration\n");}

Extends : %empty
    | EXTENDS Identifier {printf("Extends\n");}

Variables : %empty
    | Variables VarDeclaration {printf("VarDeclaration\n");}

Methods : %empty
    | Methods MethodDeclaration {printf("MethodDeclaration\n");}

VarDeclaration :
    Type Identifier SEMICOLON {printf("VarDeclaration\n");}

MethodDeclaration :
    PUBLIC Type Identifier LPAREN Arguments RPAREN LBRACE Variables Statements RETURN Expression SEMICOLON RBRACE {printf("MethodDeclaration\n");}

Arguments : %empty
    | Type Identifier AdditionalArgs {printf("Argument\n");}

AdditionalArgs : %empty
    | AdditionalArgs COMMA Type Identifier {printf("AdditionalArg\n");}

Type :
     INT LSQBRACKET RSQBRACKET {printf("Massive of ints\n");}
    | BOOLEAN   {printf("Bool\n");}
    | INT   {printf("Int\n");}
    | Identifier    {printf("Identifier\n");}

Statement :
     LBRACE Statements RBRACE  {printf("Statements\n");}
    | IF LPAREN Expression RPAREN Statement ELSE Statement  {printf("If-else statement\n");}
    | WHILE LPAREN Expression RPAREN Statement  {printf("While statement\n");}
    | OUTPUT LPAREN Expression RPAREN SEMICOLON {printf("Print expression\n");}
    | Identifier ASSIGN Expression SEMICOLON    {printf("Assign identifier\n");}
    | Identifier LSQBRACKET Expression RSQBRACKET ASSIGN Expression SEMICOLON   {printf("Assign massive element\n");}

Statements:
    %empty
    | Statements Statement

ExpressionArguments:
    %empty
    | Expression { printf("Expression\n"); }
    | ExpressionArguments COMMA Expression { printf("Expression from list of expressions\n"); }

Expression:
    Expression AND Expression { printf("&&\n"); }
    | Expression LESS Expression { printf("<\n"); }
    | Expression PLUS Expression { printf("+\n"); }
    | Expression MINUS Expression { printf("-\n"); }
    | Expression MULTIPLY Expression { printf("*\n"); }
    | Expression LSQBRACKET Expression RSQBRACKET {}
    | Expression DOT LENGTH {}
    | Expression DOT IDENTIFIER LPAREN ExpressionArguments RPAREN {}
    | NUMBER { printf("number(%d)", $1); }
    | TRUE { printf("true\n"); }
    | FALSE { printf("false\n"); }
    | IDENTIFIER { printf("Identifier(%s)\n", $1); }
    | THIS { printf("this\n"); }
    | NEW INT LSQBRACKET Expression RSQBRACKET {}
    | NEW IDENTIFIER LPAREN RPAREN {}
    | EXCL_MARK Expression {}
    | LPAREN Expression RPAREN {}

Identifier : IDENTIFIER {printf("Identifier\n");}
%%

extern int lineIndex, charIndex;


void yyerror (char *s) {
    printf("%s\n", s);
}