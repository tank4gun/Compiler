%{
#include <stdio.h>
#include <string>

#include "Expressions.h"
#include "Identifiers.h"
#include "Statements.h"
#include "Types.h"
#include "MethodDeclaration.h"
#include "VarDeclaration.h"
#include "ClassDeclaration.h"
#include "lexer.h"

extern Goal* maingoal;

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
    ExpList* expargs;
    IMethodDeclaration* method;
    MethodDeclarationsList* methods;
    IVarDeclaration* var;
    VarDeclarationsList* vars;
    IArgument* arg;
    ArgumentsList* args;
    Extends* ext;
    ClassDeclaration* classdecl;
    ClassDeclarationsList* classes;
    MainClass* mainclass;
    Goal* goal;
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
%type <expargs> ExpressionArguments
%type <method> MethodDeclaration
%type <methods> Methods
%type <var> VarDeclaration
%type <vars> Variables
%type <arg> Argument
%type <args> Arguments
%type <ext> Extends
%type <classdecl> ClassDeclaration
%type <classes> Classes
%type <mainclass> MainClass
%type <goal> Goal
%%

Goal : MainClass Classes {printf("Goal\n"); maingoal = new Goal($1, $2);}

Classes : %empty {$$ = new ClassDeclarationsList();}
    | ClassDeclaration Classes {printf("ClassDeclaration\n"); $$ = new ClassDeclarationsList($1, $2);}

MainClass : CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPAREN STRING LSQBRACKET RSQBRACKET Identifier RPAREN LBRACE Statement RBRACE RBRACE {
    printf("MainClass\n"); $$ = new MainClass($2, $12, $15);}

ClassDeclaration : CLASS Identifier Extends LBRACE Variables Methods RBRACE {printf("ClassDeclaration\n"); $$ = new ClassDeclaration($2, $3, $5, $6);}

Extends : %empty {$$ = new Extends();}
    | EXTENDS Identifier {printf("Extends\n"); $$ = new Extends($2);}

Variables : %empty {$$ = new VarDeclarationsList();}
    | Variables VarDeclaration {printf("VarDeclaration\n"); $$ = new VarDeclarationsList($2, $1);}

Methods : %empty {$$ = new MethodDeclarationsList();}
    | Methods MethodDeclaration {printf("MethodDeclaration\n"); $$ = new MethodDeclarationsList($2, $1);}

VarDeclaration :
    Type Identifier SEMICOLON {printf("VarDeclaration\n"); $$ = new VarDeclaration($1, $2);}

MethodDeclaration :
    PUBLIC Type Identifier LPAREN Arguments RPAREN LBRACE Variables Statements RETURN Expression SEMICOLON RBRACE {printf("MethodDeclaration\n");
$$ = new MethodDeclaration($2, $3, $5, $8, $9, $11);}

Arguments :
     Argument {printf("Argument\n"); $$ = new ArgumentsList($1);}
     | Arguments COMMA Argument {printf("AdditionalArg\n"); $$ = new ArgumentsList($3, $1);}

Argument :
    Type Identifier {printf("Argument\n"); $$ = new Argument($1, $2);}

Type :
     INT LSQBRACKET RSQBRACKET {printf("Massive of ints\n"); $$ = new IntArrayType();}
    | BOOLEAN   {printf("Bool\n"); $$ = new BooleanType();}
    | INT   {printf("Int\n"); $$ = new IntType();}
    | Identifier {printf("Identifier\n"); $$ = new IdentifierType($1);}

Statement :
     LBRACE Statements RBRACE  {printf("Statements\n"); $$ = new BraceStatement($2);}
    | IF LPAREN Expression RPAREN Statement ELSE Statement  {printf("If-else statement\n"); $$ = new IfStatement($3, $5, $7);}
    | WHILE LPAREN Expression RPAREN Statement  {printf("While statement\n"); $$ = new WhileStatement($3, $5);}
    | OUTPUT LPAREN Expression RPAREN SEMICOLON {printf("Print expression\n"); $$ = new OutputStatement($3);}
    | Identifier ASSIGN Expression SEMICOLON    {printf("Assign identifier\n"); $$ = new AssignStatement($3, $1);}
    | Identifier LSQBRACKET Expression RSQBRACKET ASSIGN Expression SEMICOLON  {printf("Assign massive element\n"); $$ = new ArrayAssignStatement($1, $3, $6);}

Statements:
    %empty {$$ = new StatementsList();}
    | Statement Statements {$$ = new StatementsList($1, $2);}

ExpressionArguments:
     Expression { printf("Expression\n"); $$ = new ExpList($1);}
    | ExpressionArguments COMMA Expression { printf("Expression from list of expressions\n"); $$ = new ExpList($3, $1);}

Expression:
    Expression AND Expression { printf("&&\n"); $$ = new AndExp($1, $3);}
    | Expression LESS Expression { printf("<\n"); $$ = new LessExp($1, $3);}
    | Expression PLUS Expression { printf("+\n"); $$ = new PlusExp($1, $3);}
    | Expression MINUS Expression { printf("-\n"); $$ = new MinusExp($1, $3);}
    | Expression MULTIPLY Expression { printf("*\n"); $$ = new TimesExp($1, $3);}
    | Expression LSQBRACKET Expression RSQBRACKET {$$ = new IndexExp($1, $3);}
    | Expression DOTLENGTH {printf("length\n"); $$ = new LengthExp($1);}
    | Expression DOT Identifier LPAREN ExpressionArguments RPAREN {$$ = new CallMethodExp($1, $3, $5);}
    | NUMBER { printf("number(%d)", $1); $$ = new IntExp($1);}
    | TRUE { printf("true\n"); $$ = new TrueExp();}
    | FALSE { printf("false\n"); $$ = new FalseExp();}
    | Identifier {$$ = new IdExp($1);}
    | THIS { printf("this\n"); $$ = new ThisExp();}
    | NEW INT LSQBRACKET Expression RSQBRACKET {$$ = new NewIntExp($4);}
    | NEW Identifier LPAREN RPAREN {$$ = new IdExp($2);}
    | EXCL_MARK Expression {$$ = new NotExp($2);}
    | LPAREN Expression RPAREN {$$ = new ParenExp($2);}

Identifier : IDENTIFIER {printf("Identifier(%s)\n", $1); char *tmp_id = new char(); strcpy(tmp_id, $1); $$ = new Identifier(tmp_id); }
%%

extern int lineIndex, charIndex;


void yyerror (char *s) {
    printf("%s\n", s);
}
