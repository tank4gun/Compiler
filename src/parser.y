%locations


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
extern std::vector<std::string> errors;
extern LocStruct location;
/* #define YYSTYPE string */
extern StringConverter stringConverter;

void yyerror(const char *msg);

%}


%union
{
    int int_num;
    char* id_name;
    Identifier* identifier;
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
%token LPAREN
%token RPAREN
%token LBRACE
%token RBRACE
%token LSQBRACKET
%token RSQBRACKET
%right ASSIGN
%token PLUS MINUS MULTIPLY LESS AND
%token COMMA
%token SEMICOLON
%token DOT
%token OUTPUT
%token LENGTH
%token EXCL_MARK
%token RETURN
%token DOTLENGTH


%token PUBLIC PRIVATE STATIC VOID MAIN EXTENDS TRUE FALSE THIS NEW IF ELSE WHILE
%token INT BOOLEAN STRING

%token <int_num> NUMBER
%token <id_name> IDENTIFIER

%left PLUS MINUS MULTIPLY LESS AND
%right EXCL_MARK
%precedence DOT
%precedence DOTLENGTH
%precedence LSQBRACKET


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



%%

Goal : MainClass Classes {/*printf("Goal\n");*/ maingoal = std::make_unique<Goal>($1, $2, location);}
  	| error MainClass Classes { yyerrok; }
  	| MainClass Classes error { yyerrok; }

Classes : %empty {$$ = new ClassDeclarationsList(location);}
    | ClassDeclaration Classes {/*printf("ClassDeclarationsList\n");*/ $$ = new ClassDeclarationsList($1, $2, location);}

MainClass : CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPAREN STRING LSQBRACKET RSQBRACKET Identifier RPAREN LBRACE Statement RBRACE RBRACE {
    /*printf("MainClass\n");*/ $$ = new MainClass($2, $12, $15, location);}

ClassDeclaration : CLASS Identifier Extends LBRACE Variables Methods RBRACE {/*printf("ClassDeclaration\n");*/ $$ = new ClassDeclaration($2, $3, $5, $6, location);}
    | CLASS error Identifier Extends LBRACE Variables Methods RBRACE {  yyerrok; }

Extends : %empty {/*printf("NotInherited\n");*/ $$ = new Extends(location);}
    | EXTENDS Identifier {/*printf("Extends\n");*/ $$ = new Extends($2, location);}
    | EXTENDS Identifier error { yyerrok; }


Variables : %empty {$$ = new VarDeclarationsList(location);}
    | Variables VarDeclaration {/*printf("VarDeclarationsList\n");*/ $$ = new VarDeclarationsList($2, $1, location);}

Methods : %empty {$$ = new MethodDeclarationsList(location);}
    | Methods MethodDeclaration {/*printf("MethodDeclarationsList\n");*/ $$ = new MethodDeclarationsList($2, $1, location);}

VarDeclaration :
    Type Identifier SEMICOLON {/*printf("VarDeclaration\n");*/ $$ = new VarDeclaration($1, $2, location);}
  	| Type error SEMICOLON { yyerrok; }

MethodDeclaration :
    PUBLIC Type Identifier LPAREN Arguments RPAREN LBRACE Variables Statements ReturnStatement SEMICOLON RBRACE {/*printf("MethodDeclaration\n");*/
$$ = new MethodDeclaration($2, $3, $5, $8, $9, $10, location);}
    | PUBLIC Type Identifier LPAREN error RPAREN LBRACE Variables Statements ReturnStatement SEMICOLON RBRACE { yyerrok; }

ReturnStatement:
    RETURN Expression {$$ = new ReturnStatement($2, location);}

Arguments : %empty {$$ = new ArgumentsList(location); }
     | Argument {/*printf("Argument\n");*/ $$ = new ArgumentsList($1, location);}
     | Arguments COMMA Argument {/*printf("AdditionalArg\n"); */$$ = new ArgumentsList($3, $1, location);}

Argument :
    Type Identifier {/*printf("Argument\n"); */$$ = new Argument($1, $2, location);}

Type :
     INT LSQBRACKET RSQBRACKET {/*printf("Massive of ints\n");*/ $$ = new IntArrayType(location);}
    | BOOLEAN   {/*printf("Bool\n");*/ $$ = new BooleanType(location);}
    | INT   {/*printf("Int\n");*/ $$ = new IntType(location);}
    | Identifier {/*printf("IdentifierType\n");*/ $$ = new IdentifierType($1, location);}

Statement :
     LBRACE Statements RBRACE  {/*printf("Statements\n"); */$$ = new BraceStatement($2, location);}
    | IF LPAREN Expression RPAREN Statement ELSE Statement {/*printf("If-elseStatement\n");*/ $$ = new IfStatement($3, $5, $7, location);}
    | WHILE LPAREN Expression RPAREN Statement  {/*printf("WhileStatement\n");*/ $$ = new WhileStatement($3, $5, location);}
    | OUTPUT LPAREN Expression RPAREN SEMICOLON {/*printf("PrintStatement\n"); */$$ = new OutputStatement($3, location);}
    | Identifier ASSIGN Expression SEMICOLON    {/*printf("AssignStatement\n");*/ $$ = new AssignStatement($3, $1, location);}
    | Identifier LSQBRACKET Expression RSQBRACKET ASSIGN Expression SEMICOLON  {/*printf("AssignArrayStatement\n");*/ $$ = new ArrayAssignStatement($1, $3, $6, location);}
    | LBRACE error RBRACE { yyerrok; }
    | IF LPAREN error RPAREN Statement ELSE Statement { yyerrok; }
    | WHILE LPAREN error RPAREN Statement { yyerrok; }
    | error SEMICOLON { yyerrok; }

Statements:
    %empty {$$ = new StatementsList(location);}
    | Statement Statements {$$ = new StatementsList($1, $2, location);}

ExpressionArguments: %empty {$$ = new ExpList(location);}
    | Expression { /*printf("Expression\n");*/ $$ = new ExpList($1, location);}
    | ExpressionArguments COMMA Expression { /*printf("Expression from list of expressions\n");*/ $$ = new ExpList($3, $1, location);}

Expression:
    Expression AND Expression { /*printf("&&\n");*/ $$ = new BinOp(BinaryOps::ANDOP, $1, $3, location);}
    | Expression LESS Expression { /*printf("<\n");*/ $$ = new BinOp(BinaryOps::LESSOP, $1, $3, location);}
    | Expression PLUS Expression { /*printf("+\n"); */$$ = new BinOp(BinaryOps::PLUSOP, $1, $3, location);}
    | Expression MINUS Expression {/* printf("-\n");*/ $$ = new BinOp(BinaryOps::MINUSOP, $1, $3, location);}
    | Expression MULTIPLY Expression { /*printf("*\n"); */$$ = new BinOp(BinaryOps::MULTOP, $1, $3, location);}
    | Expression LSQBRACKET Expression RSQBRACKET {$$ = new IndexExp($1, $3, location);}
    | Expression DOTLENGTH {/*printf("length\n");*/ $$ = new LengthExp($1, location);}
    | Expression DOT Identifier LPAREN ExpressionArguments RPAREN {$$ = new CallMethodExp($1, $3, $5, location);}
    | NUMBER { /*printf("number(%d)\n", $1);*/ $$ = new IntExp($1, location);}
    | TRUE { /*printf("true\n"); */$$ = new BooleanExp(true, location);}
    | FALSE { /*printf("false\n");*/ $$ = new BooleanExp(false, location);}
    | Identifier {$$ = new IdExp($1, location);}
    | THIS { /*printf("this\n"); */$$ = new ThisExp(location);}
    | NEW INT LSQBRACKET Expression RSQBRACKET {$$ = new NewIntExp($4, location);}
    | NEW Identifier LPAREN RPAREN {$$ = new NewExp($2, location);}
    | EXCL_MARK Expression {$$ = new NotExp($2, location);}
    | LPAREN Expression RPAREN { $$ = $2; }
    | Expression LSQBRACKET error RSQBRACKET { yyerrok; }
    | NEW INT LSQBRACKET error RSQBRACKET { yyerrok; }
    | LPAREN error RPAREN { yyerrok; }


Identifier : IDENTIFIER {/*printf("Identifier(%s)\n", $1);*/ $$ = new Identifier(stringConverter.getIntern($1), location); }
%%

extern int lineIndex, charIndex;


void yyerror(const char *msg) {
    std::string error_msg = std::string(std::to_string(location.first_line) + ":" + std::to_string(location.first_column) + " " + msg);
    errors.push_back(error_msg);
}
