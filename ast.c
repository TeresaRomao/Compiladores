// AST constructor functions

#include <stdlib.h> // for malloc
#include <stdbool.h> // for boolean
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}
Expr* ast_boolValue(bool v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_BOOL;
  node->attr.value = v;
  return node;
}
Expr* ast_variable(char* v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VAR;
  //node->attr.value = 0;
  node->attr.varname = v;
  return node;
}

BooleanExpr* ast_boolean(int v) {
  BooleanExpr* node = (BooleanExpr*) malloc(sizeof(BooleanExpr));
  node->kind = E_BOOLEAN;
  node->attr.value = v;
  return node;
}

Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

BooleanExpr* ast_boolOperation(int operator, Expr* left, Expr* right) {
  BooleanExpr* node = (BooleanExpr*) malloc(sizeof(BooleanExpr));
  node->kind = E_BOOLEAN_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Cmd* ast_cmdIf(BooleanExpr* cond, BexprList* bexprList, CmdList* cmdList, Cmd* cmdElse){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_IF;
  node->attr.if_state.cond = cond;  
  node->attr.if_state.cmdElse = cmdElse;
  node->attr.if_state.cmdList = cmdList;
  node->attr.if_state.bexprList = bexprList;
  return node;

}

Cmd* ast_cmdElse(CmdList* cmdList){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_ELSE;
  node->attr.else_state.cmdList = cmdList;
  return node;
}


Cmd* ast_cmdWhile(BooleanExpr* cond, CmdList* cmdList){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_WHILE;
  node->attr.whiles.cond = cond;
  node->attr.whiles.cmdList = cmdList;
  return node;
}


Cmd* ast_cmdFor( Cmd* forStatement, CmdList* cmdList){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_FOR;
  node->attr.forLoop.forStatement = forStatement;
  node->attr.forLoop.cmdList = cmdList;
  return node;
}

Cmd* ast_cmdForStatement(char* vname, Expr* expr, BooleanExpr* cond, Expr* expr2 ){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_FORSTATEMENT;
  node->attr.for_Statement.cond = cond;
  node->attr.for_Statement.expr = expr;
  node->attr.for_Statement.expr2 = expr2;
  node->attr.for_Statement.vname = vname;
  return node;
}

Cmd* ast_cmdPrintInt(Expr* expr){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_PRINT_INT;
  node->attr.print_int.expr = expr;
  return node;
}


Cmd* ast_cmdPrintStr(char* str){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_PRINT_STR;
  node->attr.print_str.str = str;
  return node;
}

Cmd* ast_cmdScanInt(char* vname){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_SCAN_INT;
  node->attr.scan_int.vname = vname;
  return node;
}

Cmd* ast_cmdDeclarationInt(char* vname, Expr* expr){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_DECLINT;
  node->attr.declarationInt.vname = vname;
  node->attr.declarationInt.expr = expr;
  return node;
}


Cmd* ast_cmdDeclarationBool(char* vname, BooleanExpr* bexpr){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_DECLBOOL;
  node->attr.declarationBool.vname = vname;
  node->attr.declarationBool.bexpr = bexpr;
  return node;
}

Cmd* ast_cmdDeclarationString(char* vname, char* str){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_DECLSTRING;
  node->attr.declarationString.vname = vname;
  node->attr.declarationString.str = str;
  return node;
}



Cmd* ast_cmdDeclarationVariable(char* vname, VariablesList* variables){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_DECLVARIABLE;
  node->attr.declarationVariable.vname = vname;
  node->attr.declarationVariable.next = variables;
  return node;
}


Cmd* ast_cmdDeclarationEquals(char* vname, Expr* expr) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_EQUALS;
  node->attr.equals.vname = vname;
  node->attr.equals.expr = expr;
  return node;
}


Cmd* ast_cmdReturn(Expr* expr){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = CMD_RETURN;
  node->attr.returnCmd.expr = expr;
  return node;
}

VariablesList* ast_cmdVariablesList(char* vname, VariablesList* next){
  VariablesList* node = (VariablesList*) malloc(sizeof(VariablesList));
  node->vname = vname;
  node->next = next;
  return node;

}


BexprList* ast_cmdBexprList(BooleanExpr* bexpr, BexprList* next){
  BexprList* node = (BexprList*) malloc(sizeof(BexprList));
  node->bexpr = bexpr;
  node->next = next;
  return node;

}

CmdList* ast_cmdList(Cmd* cmd, CmdList* next){
  CmdList* node = (CmdList*) malloc(sizeof(CmdList));
  node->cmd = cmd;
  node->next = next;
  return node;

}
