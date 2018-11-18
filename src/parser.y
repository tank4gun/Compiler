%{
#include <stdio.h>
#include <string>

#include "ST-AST/Expressions.h"
#include "ST-AST/Identifiers.h"
#include "ST-AST/Statements.h"
#include "ST-AST/Types.h"
#include "ST-AST/MethodDeclaration.h"
#include "ST-AST/VarDeclaration.h"
#include "ST-AST/ClassDeclaration.h"
#include "StringConverter.h"
#include "lexer.h"

extern std::unique_ptr<Goal> maingoal;
/* #define YYSTYPE string */
extern StringConverter stringConverter;

void yyerror(char *s);
void yyerror(char *s, int lineIndex, int charIndex);

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
    ReturnStatement* retstat;
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
%type <retstat> ReturnStatement

%locations

%%

Goal : MainClass Classes {printf("Goal\n"); maingoal = std::make_unique<Goal>($1, $2);}

Classes : %empty {$$ = new ClassDeclarationsList(yylloc);}
    | ClassDeclaration Classes {printf("ClassDeclarationsList\n"); $$ = new ClassDeclarationsList($1, $2, yylloc);}

MainClass : CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPAREN STRING LSQBRACKET RSQBRACKET Identifier RPAREN LBRACE Statement RBRACE RBRACE {
    printf("MainClass\n"); $$ = new MainClass($2, $12, $15, yylloc);}

ClassDeclaration : CLASS Identifier Extends LBRACE Variables Methods RBRACE {printf("ClassDeclaration\n"); $$ = new ClassDeclaration($2, $3, $5, $6, yylloc);}

Extends : %empty {printf("NotInherited\n"); $$ = new Extends(yylloc);}
    | EXTENDS Identifier {printf("Extends\n"); $$ = new Extends($2, yylloc);}

Variables : %empty {$$ = new VarDeclarationsList(yylloc);}
    | Variables VarDeclaration {printf("VarDeclarationsList\n"); $$ = new VarDeclarationsList($2, $1, yylloc);}

Methods : %empty {$$ = new MethodDeclarationsList(yylloc);}
    | Methods MethodDeclaration {printf("MethodDeclarationsList\n"); $$ = new MethodDeclarationsList($2, $1, yylloc);}

VarDeclaration :
    Type Identifier SEMICOLON {printf("VarDeclaration\n"); $$ = new VarDeclaration($1, $2, yylloc);}

MethodDeclaration :
    PUBLIC Type Identifier LPAREN Arguments RPAREN LBRACE Variables Statements ReturnStatement SEMICOLON RBRACE {printf("MethodDeclaration\n");
$$ = new MethodDeclaration($2, $3, $5, $8, $9, $10, yylloc);}

ReturnStatement:
    RETURN Expression {$$ = new ReturnStatement($2, yylloc);}

Arguments : %empty {$$ = new ArgumentsList(yylloc); }
     | Argument {printf("Argument\n"); $$ = new ArgumentsList($1, yylloc);}
     | Arguments COMMA Argument {printf("AdditionalArg\n"); $$ = new ArgumentsList($3, $1, yylloc);}

Argument :
    Type Identifier {printf("Argument\n"); $$ = new Argument($1, $2, yylloc);}

Type :
     INT LSQBRACKET RSQBRACKET {printf("Massive of ints\n"); $$ = new IntArrayType(yylloc);}
    | BOOLEAN   {printf("Bool\n"); $$ = new BooleanType(yylloc);}
    | INT   {printf("Int\n"); $$ = new IntType(yylloc);}
    | Identifier {printf("IdentifierType\n"); $$ = new IdentifierType($1, yylloc);}

Statement :
     LBRACE Statements RBRACE  {printf("Statements\n"); $$ = new BraceStatement($2, yylloc);}
    | IF LPAREN Expression RPAREN Statement ELSE Statement  {printf("If-elseStatement\n"); $$ = new IfStatement($3, $5, $7, yylloc);}
    | WHILE LPAREN Expression RPAREN Statement  {printf("WhileStatement\n"); $$ = new WhileStatement($3, $5, yylloc);}
    | OUTPUT LPAREN Expression RPAREN SEMICOLON {printf("PrintStatement\n"); $$ = new OutputStatement($3, yylloc);}
    | Identifier ASSIGN Expression SEMICOLON    {printf("AssignStatement\n"); $$ = new AssignStatement($3, $1, yylloc);}
    | Identifier LSQBRACKET Expression RSQBRACKET ASSIGN Expression SEMICOLON  {printf("AssignArrayStatement\n"); $$ = new ArrayAssignStatement($1, $3, $6, yylloc);}

Statements:
    %empty {$$ = new StatementsList(yylloc);}
    | Statement Statements {$$ = new StatementsList($1, $2, yylloc);}

ExpressionArguments: %empty {$$ = new ExpList(yylloc);}
    | Expression { printf("Expression\n"); $$ = new ExpList($1, yylloc);}
    | ExpressionArguments COMMA Expression { printf("Expression from list of expressions\n"); $$ = new ExpList($3, $1, yylloc);}

Expression:
    Expression AND Expression { printf("&&\n"); $$ = new BinOp(BinaryOps::ANDOP, $1, $3, yylloc);}
    | Expression LESS Expression { printf("<\n"); $$ = new BinOp(BinaryOps::LESSOP, $1, $3, yylloc);}
    | Expression PLUS Expression { printf("+\n"); $$ = new BinOp(BinaryOps::PLUSOP, $1, $3, yylloc);}
    | Expression MINUS Expression { printf("-\n"); $$ = new BinOp(BinaryOps::MINUSOP, $1, $3, yylloc);}
    | Expression MULTIPLY Expression { printf("*\n"); $$ = new BinOp(BinaryOps::MULTOP, $1, $3, yylloc);}
    | Expression LSQBRACKET Expression RSQBRACKET {$$ = new IndexExp($1, $3, yylloc);}
    | Expression DOTLENGTH {printf("length\n"); $$ = new LengthExp($1, yylloc);}
    | Expression DOT Identifier LPAREN ExpressionArguments RPAREN {$$ = new CallMethodExp($1, $3, $5, yylloc);}
    | NUMBER { printf("number(%d)\n", $1); $$ = new IntExp($1, yylloc);}
    | TRUE { printf("true\n"); $$ = new BooleanExp(true, yylloc);}
    | FALSE { printf("false\n"); $$ = new BooleanExp(false, yylloc);}
    | Identifier {$$ = new IdExp($1, yylloc);}
    | THIS { printf("this\n"); $$ = new ThisExp(yylloc);}
    | NEW INT LSQBRACKET Expression RSQBRACKET {$$ = new NewIntExp($4, yylloc);}
    | NEW Identifier LPAREN RPAREN {$$ = new NewExp($2, yylloc);}
    | EXCL_MARK Expression {$$ = new NotExp($2, yylloc);}
    | LPAREN Expression RPAREN { $$ = $2; }

Identifier : IDENTIFIER {printf("Identifier(%s)\n", $1); $$ = new Identifier(stringConverter.getIntern(std::string($1))); }
%%

extern int lineIndex, charIndex;


void yyerror(char *s) {
    printf("%s\n", s);
}

void yyerror(char *s, int lineIndex, int charIndex) {
    printf("%d:%d %s\n", lineIndex, charIndex, s);
}
