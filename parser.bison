// Tokens
%token 
  INT
  BOOL
  WHILE
  FOR
  IF
  ELSE
  PRINT_INT
  SCAN_INT
  PRINT_STR
  VNAME
  STRING
  SEMI_COLON
  COMMA
  OPEN_BRACKETS
  CLOSE_BRACKETS
  OPEN_PARENTESIS
  CLOSE_PARENTESIS
  DECLARATION
  EQUAL
  DIFF
  GREATER
  SMALLER
  GREATER_OR_EQUAL
  SMALLER_OR_EQUAL
  TRUE
  FALSE
  RETURN
  VOID
  NOT
  AND
  OR

// Operator associativity & precedence
%left PLUS SUBTRACT
%left MULT DIVIDE MOD
%left EQUAL DIFF SMALLER GREATER GREATER_OR_EQUAL SMALLER_OR_EQUAL


// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  bool boolVal;
  Expr* exprValue; 
  char* strValue;
  char* varName;
  BooleanExpr* exprBoolean;
  Cmd* cmds; 
  CmdList* cmdList; 
  VariablesList* vars;
  BexprList* blist;
}

%type <intValue> INT
%type <boolVal> BOOL
%type <strValue> STRING
%type <exprValue> expr
%type <exprBoolean> bexpr
%type <boolValue> TRUE
%type <boolValue> FALSE
%type <cmdList> cmdList
%type <varName> VNAME
%type <cmds> cmds
%type <cmds> else
%type <cmds> forStatement
%type <vars> variables
%type <blist> bexprList

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
CmdList* root;
}

%%
program: 
  INT VNAME OPEN_PARENTESIS CLOSE_PARENTESIS OPEN_BRACKETS cmdList CLOSE_BRACKETS{ root = $6; }


cmdList:
 { $$ = NULL; }
 |
 cmds cmdList { $$ = ast_cmdList($1, $2); }
 ;

cmds: 

  IF OPEN_PARENTESIS bexpr bexprList CLOSE_PARENTESIS OPEN_BRACKETS cmdList CLOSE_BRACKETS {
     $$ = ast_cmdIf($3, $4, $7, NULL);
  }
  |
  IF OPEN_PARENTESIS bexpr bexprList CLOSE_PARENTESIS OPEN_BRACKETS cmdList CLOSE_BRACKETS else {
     $$ = ast_cmdIf($3 ,$4,  $7, $9);
  }
  |
  WHILE OPEN_PARENTESIS bexpr CLOSE_PARENTESIS OPEN_BRACKETS cmdList CLOSE_BRACKETS {
     $$ = ast_cmdWhile($3, $6);
  }
  |
  FOR OPEN_PARENTESIS forStatement CLOSE_PARENTESIS OPEN_BRACKETS cmdList CLOSE_BRACKETS {
     $$ = ast_cmdFor($3, $6);
  }
  |
  PRINT_INT OPEN_PARENTESIS expr CLOSE_PARENTESIS SEMI_COLON {
    $$ = ast_cmdPrintInt($3);
  }  
  |
  PRINT_STR OPEN_PARENTESIS STRING CLOSE_PARENTESIS SEMI_COLON {
    $$ = ast_cmdPrintStr($3);
  }
  |
  VNAME DECLARATION SCAN_INT OPEN_PARENTESIS CLOSE_PARENTESIS SEMI_COLON {
    $$ = ast_cmdScanInt($1);
  }
  |
  INT VNAME DECLARATION SCAN_INT OPEN_PARENTESIS CLOSE_PARENTESIS SEMI_COLON {
    $$ = ast_cmdScanInt($2);
  }
  |
  INT VNAME DECLARATION expr SEMI_COLON{
    $$ = ast_cmdDeclarationInt($2, $4);
  } 
  |
  BOOL VNAME DECLARATION bexpr SEMI_COLON{
    $$ = ast_cmdDeclarationBool($2, $4);
  }  
  |
  STRING VNAME DECLARATION STRING SEMI_COLON{
    $$ = ast_cmdDeclarationString($2, $4);
  } 
  |
  INT VNAME variables SEMI_COLON {
    $$ = ast_cmdDeclarationVariable($2, $3);
  }
  |
  VNAME DECLARATION expr SEMI_COLON {
    $$ = ast_cmdDeclarationEquals($1, $3);
  }
  |
  RETURN expr SEMI_COLON {
    $$ = ast_cmdReturn($2);
  }
  ;

variables:
  { $$ = NULL;}
  |
  COMMA VNAME variables { $$ = ast_cmdVariablesList($2,$3);}
  ;

bexprList: 
  { $$ = NULL; } 
  |
  OR bexpr bexprList { $$ = ast_cmdBexprList($2, $3); }
  |
  AND bexpr bexprList { $$ = ast_cmdBexprList($2, $3); }

else:

  ELSE OPEN_BRACKETS cmdList CLOSE_BRACKETS {
    $$ = ast_cmdElse($3);
  }
  ;

forStatement: 

  INT VNAME DECLARATION expr SEMI_COLON bexpr SEMI_COLON expr{
    $$ = ast_cmdForStatement($2, $4, $6, $8);
  }

expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  |   
  VNAME { 
    $$ = ast_variable($1); ; 
  }
  |
  expr PLUS expr { 
    $$ = ast_operation(PLUS, $1, $3); 
  } 
  | 
  expr SUBTRACT expr { 
    $$ = ast_operation(SUBTRACT, $1, $3); 
  } 
  | 
  expr MULT expr { 
    $$ = ast_operation(MULT, $1, $3); 
  } 
  | 
  expr DIVIDE expr { 
    $$ = ast_operation(DIVIDE, $1, $3); 
  } 
  | 
  expr MOD expr { 
    $$ = ast_operation(MOD, $1, $3); 
  } 
  ;

bexpr:
  TRUE {
    $$ = ast_boolean(1); 
  }
  |
  FALSE {
    $$ = ast_boolean(0); 
  }
  |
  expr EQUAL expr { 
    $$ = ast_boolOperation(EQUAL, $1, $3); 
  } 
  |
  expr DIFF expr { 
    $$ = ast_boolOperation(DIFF, $1, $3); 
  } 
  |
  expr GREATER expr { 
    $$ = ast_boolOperation(GREATER, $1, $3); 
  }
  | 
  expr GREATER_OR_EQUAL expr { 
    $$ = ast_boolOperation(GREATER_OR_EQUAL, $1, $3); 
  }
  | 
  expr SMALLER expr { 
    $$ = ast_boolOperation(SMALLER, $1, $3); 
  }
  | 
  expr SMALLER_OR_EQUAL expr { 
    $$ = ast_boolOperation(SMALLER_OR_EQUAL, $1, $3); 
  } 
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}


