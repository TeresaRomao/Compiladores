// Tokens
%token 
  INT  
  PLUS
  MINUS
  DIV
  MUL
  PER

// Operator associativity & precedence
%left PLUS
%left MINUS
%left DIV
%left MUL
%left PER


// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue; 
}

%type <intValue> INT
%type <exprValue> expr

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Expr* root;
}

%%
program: expr { root = $1; }

expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  | 
  expr PLUS expr { 
    $$ = ast_operation(PLUS, $1, $3); 
  }
  |
  expr MINUS expr {
    $$ = ast_operation(MINUS, $1, $3);
  }
  |
  expr DIV expr {
    $$ = ast_operation(DIV, $1, $3);
  }
  |
  expr MUL expr {
    $$ = ast_operation(MUL, $1, $3);
  }
  |
  expr PER expr {
    $$ = ast_operation(PER, $1, $3);
  }
  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
