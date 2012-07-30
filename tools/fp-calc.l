%{
#include "fp/fp.h"
#define YYSTYPE fp_t

#include "fp-calc.h"
#include <stdlib.h>
#include <stdio.h>

%}

%option noyywrap

%%

[0-9]+("."[0-9]+)? { yylval = fp_fromstr(yytext); return NUMBER;             }
"+"                { return OP_ADD;                                          }
"-"                { return OP_SUB;                                          }
"*"                { return OP_MUL;                                          }
"/"                { return OP_DIV;                                          }
"("                { return OP_LPAREN;                                       }
")"                { return OP_RPAREN;                                       }
\n                 { return '\n';                                            }
" "+
.                  { fprintf(stderr, "unknown input\n"); exit(EXIT_FAILURE); }

%%

