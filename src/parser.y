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

%token OUTPUT
%token PUBLIC PRIVATE STATIC VOID MAIN EXTENDS TRUE FALSE THIS NEW IF ELSE WHILE
%token INT BOOLEAN STRING

%token <int_num> NUMBER
%token <id_name> IDENTIFIER

%%

program_start :
    | OUTPUT {}
    | public {}
    | private {}
    | static {}
    | void {}
    | main {}
    | extends {}
    | true {}
    | false {}
    | this {}
    | new {}
    | if {}
    | else {}
    | while {}
    | int {}
    | boolean {}
    | String {}
    | NUMBER {}
    | IDENTIFIER {}
;
%%



int main() {
    yyparse();
}

void yyerror (char *s) {
    printf (”%s\n”, s);
}