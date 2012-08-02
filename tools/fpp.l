%{
#include "fp/fp.h"
#include <stdio.h>

void print_fp(char *s);

%}

%option noyywrap
NUMBER "-"?[0-9]+("."[0-9]+)?

%%

"%FP("{NUMBER}")" { print_fp(yytext); }

%%

void print_fp(char *s) {
  fp_t     f;
  uint32_t hi, lo;

  /* Ignore "%FP(" and ")" and convert. */
  s[strlen(s) - 1] = 0;
  f = fp_fromstr(&s[4]);

  hi = f.data >> 32;
  lo = f.data;

  fprintf(yyout, "(fp_t){%u, 0x%02x, 0x%08x%08xULL}", f.sgn, f.expt, hi, lo);
}

int main(int argc, char *argv[]) {
  if(argc == 2)
    yyin = fopen(argv[1], "r");
  else
    yyin = stdin;

  yylex();
  return 0;
}

