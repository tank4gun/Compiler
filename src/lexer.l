%option noyywrap

%{
#include <cstdio>
#include <string>

int lineIndex = 0;
int charIndex = 0;

void print_coord() {
    printf("(%d.%d-%lu) ", lineIndex, charIndex, charIndex + yyleng - 1);
    charIndex += yyleng;
}

void print_type(std::string str_type) {
    printf("TYPE(%s)", str_type.c_str());
    print_coord();
}

std::string to_upper(std::string str) {
    for(int i = 0; i < str.size(); i++) {
        str[i] += 'A' - 'a';
    }
    return str;
}

void print_upper_token(std::string token_name) {
    printf("%s", to_upper(token_name).c_str());
    print_coord();
}

void print_output(std::string str) {
    printf("%s", str.c_str());
    print_coord();
}
%}

DIGIT           [0-9]
NUMBER          ({DIGIT})+
CHAR            [a-zA-Z_]
CHARSTRING      {CHAR}+
IDENTIFIER      {CHARSTRING}({CHARSTRING}|{NUMBER})*

%%
\n      {print_output("NEW_LINE"); printf("\n"); ++lineIndex; charIndex = 0;}
[ \t]   ++charIndex;
class   print_output("CLASS");
\{      print_output("LPAREN");
\}      print_output("RPAREN");
\(      print_output("LBRACE");
\)      print_output("RBRACE");
\[      print_output("LSQBRACKET");
\]      print_output("RSQBRACKET");
\=      print_output("ASSIGN");
\+      print_output("PLUS");
\-      print_output("MINUS");
\*      print_output("MULTIPLY");
\<      print_output("LESS");
\&&     print_output("AND");
\,      print_output("COMMA");
\;      print_output("SEMICOLON");
\.      print_output("DOT");

public|private|static|void|main|extends|true|false|this|new|if|else|while   print_upper_token(yytext);
System.out.println                                                          print_output("OUTPUT");
int|boolean|String                                                          print_type(yytext);

{IDENTIFIER}    {printf("ID(%s)", yytext); print_coord();}
{NUMBER}        {printf("Number(%s)", yytext); print_coord();}
%%
