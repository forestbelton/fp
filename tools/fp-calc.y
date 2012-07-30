%{
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

/*int yylex() {
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
} */

int yyerror(const char *s) {
  printf("%s\n", s);
  return 0;
}

int main() {
  printf("fp-calc\n> ");
  yyparse();
  return 0;
}
