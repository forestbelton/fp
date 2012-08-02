%{
#include "fp/fp.h"
#include <stdio.h>

/* Displays the internal representation of the floating-point value represented
 * by the given string. If is_constant is 0, it will drop the (fp_t) "cast"
 * which causes it to be allocated as an object with static/automatic storage
 * duration. This is useful when you're initializing static variables. */
void print_fp(int is_constant, char *s);

%}

%option noyywrap
NUMBER "-"?[0-9]+("."[0-9]+)?

%%

"%FP("{NUMBER}")"       { print_fp(0, yytext); }
"%FP_CONST("{NUMBER}")" { print_fp(1, yytext); }

%%

void print_fp(int is_constant, char *s) {
  fp_t     f;
  uint32_t hi, lo;

  /* Ignore "%FP(" and ")" and convert. */
  s[strlen(s) - 1] = 0;
  f = fp_fromstr(&s[4]);

  hi = f.data >> 32;
  lo = f.data;

  if(!is_constant)
    fprintf(yyout, "(fp_t)");
  fprintf(yyout, "{%u, 0x%02x, 0x%08x%08xULL}", f.sgn, f.expt, hi, lo);
}

int main(int argc, char *argv[]) {
  if(argc == 2)
    yyin = fopen(argv[1], "r");
  else
    yyin = stdin;

  yylex();
  return 0;
}

