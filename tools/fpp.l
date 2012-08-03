%{
/* Copyright (c) 2012 Forest Belton (apples)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
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

