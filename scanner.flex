%{
// HEADERS
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);
   return INT; 
}

"int" 	{ return INT; }
"bool" 	{ return BOOL; }
"string" 	{ return STRING; }
"void" 	{ return VOID; }
"if" 	{ return IF; }
"else" 	{ return ELSE; }
"while" 	{ return WHILE; }
"for" 	{ return FOR; }
"true"  { return TRUE;}
"false" { return FALSE;}
"print_int" 	{ return PRINT_INT; }
"print_str" 	{ return PRINT_STR; }
"scan_int" 	{ return SCAN_INT; }
"return" 	{ return RETURN; }
";" 	{ return SEMI_COLON; }
"," 	{ return COMMA; }
"+" { return PLUS; }
"-" { return SUBTRACT; }
"*" { return MULT; }
"/" { return DIVIDE; }
"%" { return MOD; }
"=" { return DECLARATION;}
"==" { return EQUAL;}
"!=" { return DIFF;}
"<"  { return SMALLER;}
">"  { return GREATER;}
"<=" { return SMALLER_OR_EQUAL;}
">=" { return GREATER_OR_EQUAL;}
"(" 	{ return OPEN_PARENTESIS; }
")" 	{ return CLOSE_PARENTESIS; }
"{" 	{ return OPEN_BRACKETS; }
"}" 	{ return CLOSE_BRACKETS; }
"!" 	{ return NOT; }
"||" 	{ return OR; }
"&&" 	{ return AND; }


[a-zA-Z_]?\"(\\.|[^\\"])*\" { yylval.strValue = strdup(yytext);
	return STRING; 
}

[a-zA-Z][a-zA-Z0-9_]* {  
	yylval.varName = strdup(yytext);
	return VNAME;
}

.  { yyerror("unexpected character"); }


%%

