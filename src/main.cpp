//
// Created by elena on 01.10.18.
//

#include <stdio.h>
#include <stdlib.h>
#include "Goal.h"

extern int yyparse();
extern FILE *yyin;

Goal* maingoal;

int main(int argc, char *argv[]) {
  FILE *input = fopen(argv[1], "r");
  if (input == nullptr) {
    printf("Can not open file!\n");
    exit(1);
  }
  yyin = input;
  yyparse();
  fclose(yyin);

  return 0;
}