%{
#include <ctype.h>
#include <stdio.h>
#include "fp.h"

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

%start root

%%

root :
     | root expr '\n' { show($2); }
     ;

expr : term
     | term OP_ADD term { $$ = fp_add($1, $3); }
     | term OP_SUB term { $$ = fp_sub($1, $3); }
     ;

term : NUMBER
     | NUMBER OP_MUL NUMBER { $$ = fp_mul($1, $3); }
     | NUMBER OP_DIV NUMBER { $$ = fp_div($1, $3); }
     ;

%%

void show(fp_t f) {
  char buf[20];

  fp_tostr(f, buf);
  printf("=> %s\n> ", buf);
}

int yylex() {
  int c;

  do {
    c = getchar();
  } while(c == ' ');
  
  switch(c) {
    case '+': return OP_ADD;
    case '-': return OP_SUB;
    case '*': return OP_MUL;
    case '/': return OP_DIV;

    default:
      if(isdigit(c)) {
        float f;
        char  buf[20];

        ungetc(c, stdin);
        (void)scanf("%f", &f);
        snprintf(buf, sizeof buf - 1, "%f", f);
        yylval = fp_fromstr(buf);

        return NUMBER;
      }
  }

  return c == EOF ? 0 : c;
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
