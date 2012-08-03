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
#include <ctype.h>
#include <stdio.h>
#include "fp/fp.h"

#undef  YYSTYPE
#define YYSTYPE fp_t

void show   (fp_t f);
int  yylex  (void);
int  yyerror(const char *s);

%}

%token NUMBER

%token OP_ADD
%token OP_SUB
%token OP_MUL
%token OP_DIV
%token OP_LPAREN
%token OP_RPAREN

%left OP_ADD OP_SUB
%left OP_MUL OP_DIV

%start root

%%

root :
     | root expr '\n' { show($2); }
     ;

expr : factor
     | expr OP_ADD factor { $$ = fp_add($1, $3); }
     | expr OP_SUB factor { $$ = fp_sub($1, $3); }
     ;

factor : term
       | factor OP_MUL term { $$ = fp_mul($1, $3); }
       | factor OP_DIV term { $$ = fp_div($1, $3); }
       ;

term : NUMBER
     | OP_LPAREN expr OP_RPAREN { $$ = $2; }
     ;

%%

void show(fp_t f) {
  char buf[20];

  fp_tostr(f, buf);
  printf("=> %s\n> ", buf);
}

int yyerror(const char *s) {
  printf("%s\n", s);
  return 0;
}

int main() {
  printf("fp-calc\n> ");
  yyparse();
  return 0;
}
