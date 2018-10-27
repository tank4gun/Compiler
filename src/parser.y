%{
#include <stdio.h>
#include <string>

#include "Expressions.h"
#include "Identifiers.h"
#include "Statements.h"
#include "Types.h"
#include "lexer.h"


/* #define YYSTYPE string */

void yyerror(char *s);

%}


%union
{
    int int_num;
    char* id_name;
    IIdentifier* identifier;
    IExp* expression;
    IStatement* statement;
    StatementsList* statements;
    IType* type;
}

%start Goal

%token NEW_LINE
%token TAB
%token CLASS
%left LPAREN
%token RPAREN
%left LBRACE
%token RBRACE
%left LSQBRACKET
%token RSQBRACKET
%right ASSIGN
%left PLUS
%left MINUS
%left MULTIPLY
%left LESS
%left AND
%token COMMA
%token SEMICOLON
%left DOT
%token OUTPUT
%token LENGTH
%left EXCL_MARK
%token RETURN
%left DOTLENGTH


%token PUBLIC PRIVATE STATIC VOID MAIN EXTENDS TRUE FALSE THIS NEW IF ELSE WHILE
%token INT BOOLEAN STRING

%token <int_num> NUMBER
%token <id_name> IDENTIFIER

%type <identifier> Identifier
%type <expression> Expression
%type <statement> Statement
%type <statements> Statements
%type <type> Type

%%

Goal : MainClass Classes {printf("Goal\n");}

Classes : %empty
    | ClassDeclaration Classes {printf("ClassDeclaration\n");}

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

Arguments :
     Type Identifier AdditionalArgs {printf("Argument\n");}

AdditionalArgs : %empty
    | COMMA Type Identifier AdditionalArgs {printf("AdditionalArg\n");}

Type :
     INT LSQBRACKET RSQBRACKET {printf("Massive of ints\n");}
    | BOOLEAN   {printf("Bool\n");}
    | INT   {printf("Int\n");}
    | Identifier {printf("Identifier\n"); $$ = new IdentifierType($1);}

Statement :
     LBRACE Statements RBRACE  {printf("Statements\n"); $$ = new BraceStatement($2);}
    | IF LPAREN Expression RPAREN Statement ELSE Statement  {printf("If-else statement\n");}
    | WHILE LPAREN Expression RPAREN Statement  {printf("While statement\n");}
    | OUTPUT LPAREN Expression RPAREN SEMICOLON {printf("Print expression\n");}
    | Identifier ASSIGN Expression SEMICOLON    {printf("Assign identifier\n");}
    | Identifier LSQBRACKET Expression RSQBRACKET ASSIGN Expression SEMICOLON  {printf("Assign massive element\n");}

Statements:
    %empty {$$ = new StatementsList();}
    | Statement Statements {$$ = new StatementsList($1, $2);}

ExpressionArguments:
    %empty {/* TODO */}
    | Expression { printf("Expression\n"); /* TODO */}
    | ExpressionArguments COMMA Expression { printf("Expression from list of expressions\n"); /* TODO */}

Expression:
    Expression AND Expression { printf("&&\n"); $$ = new AndExp($1, $3);}
    | Expression LESS Expression { printf("<\n"); $$ = new LessExp($1, $3);}
    | Expression PLUS Expression { printf("+\n"); $$ = new PlusExp($1, $3);}
    | Expression MINUS Expression { printf("-\n"); $$ = new MinusExp($1, $3);}
    | Expression MULTIPLY Expression { printf("*\n"); $$ = new TimesExp($1, $3);}
    | Expression LSQBRACKET Expression RSQBRACKET {$$ = new IndexExp($1, $3);}
    | Expression DOTLENGTH {printf("length\n"); $$ = new LengthExp($1);}
    | Expression DOT Identifier LPAREN ExpressionArguments RPAREN {/* TODO */}
    | NUMBER { printf("number(%d)", $1); $$ = new IntExp($1);}
    | TRUE { printf("true\n"); $$ = new TrueExp();}
    | FALSE { printf("false\n"); $$ = new FalseExp();}
    | Identifier {$$ = new IdExp($1);}
    | THIS { printf("this\n"); $$ = new ThisExp();}
    | NEW INT LSQBRACKET Expression RSQBRACKET {$$ = new NewIntExp($4);}
    | NEW Identifier LPAREN RPAREN {$$ = new IdExp($2);}
    | EXCL_MARK Expression {$$ = new NotExp($2);}
    | LPAREN Expression RPAREN {$$ = new ParenExp($2);}

Identifier : IDENTIFIER {printf("Identifier(%s)\n", $1); $$ = new Identifier($1); }
%%

extern int lineIndex, charIndex;


void yyerror (char *s) {
    printf("%s\n", s);
}
