#include <stdio.h>
#include "parser.h"

void printABSTree(CmdList* cmd,int space);
void printCmdList(CmdList* cmdList,int space);
void printBooleanExpr(BooleanExpr* bexpr,int space);
void printSpace(int space);
void printLine();
void printVariablesList(VariablesList* variables, int space);
void printBexprList(BexprList* bexprList, int space);


int eval(Expr* expr) {
  int result = 0;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    result = expr->attr.value; 
  } 
  else if (expr->kind == E_BOOL) {
    result = expr->attr.value; 
  } 
  else if (expr->kind == E_OPERATION) {
    int vLeft = eval(expr->attr.op.left);
    int vRight = eval(expr->attr.op.right);
    switch (expr->attr.op.operator) {
      case PLUS: 
        result = vLeft + vRight; 
        break;
      // TODO Other cases here ..
      case SUBTRACT: 
        result = vLeft - vRight; 
        break;
      case MULT: 
        result = vLeft * vRight; 
        break;
      case DIVIDE: 
        result = vLeft / vRight; 
        break;
      case MOD: 
        result = vLeft % vRight; 
        break;
      default: yyerror("Unknown operator!");
    }
  }
  return result;
}

void printExpr(Expr* expr, int space){
  printSpace(space);
  if(expr->kind == E_INTEGER){
    printf("%d\n" ,expr->attr.value);
    return;     
  }

  else if(expr->kind == E_VAR){
      printf("%s\n",expr->attr.varname);
      return;
  }

  if(expr->kind == E_OPERATION){
  }
      switch(expr->attr.op.operator){

        case PLUS:
          printf("+:\n");
          space++;
          printExpr(expr->attr.op.left,space);
          printExpr(expr->attr.op.right,space);
          break; 
        
          case SUBTRACT:
          printf("-:\n");
          space++;
          printExpr(expr->attr.op.left,space);
          printExpr(expr->attr.op.right,space);
          break;
        
          case MULT:
          printf("*:\n");
          space++;
          printExpr(expr->attr.op.left,space);
          printExpr(expr->attr.op.right,space);
          break;
        
          case DIVIDE:
          printf("/:\n");
          space++;
          printExpr(expr->attr.op.left,space);
          printExpr(expr->attr.op.right,space);
          break;
        
          case MOD:
          printf("%%:\n");
          space++;
          printExpr(expr->attr.op.left,space);
          printExpr(expr->attr.op.right,space);
          break; 
          
       }   
}

void printBooleanExpr(BooleanExpr* bexpr, int space){

  printSpace(space);

  if (bexpr->kind == E_BOOLEAN) {

      if(bexpr->attr.value == 1)
      {
        printf("true:\n");
        printLine();
      }
      else{
        printf("false:\n");
        printLine();
      }
  }

  else{
    switch(bexpr->attr.op.operator){

      case EQUAL:
        printf("==:\n");
        space++;
        printExpr(bexpr->attr.op.left, space);
        printExpr(bexpr->attr.op.right, space);
        break;
      
      case DIFF:
        printf("!=:\n");
        space++;
        printExpr(bexpr->attr.op.left, space);
        printExpr(bexpr->attr.op.right, space);
        break;
      
      case SMALLER:
        printf("<:\n");
        space++;
        printExpr(bexpr->attr.op.left, space);
        printExpr(bexpr->attr.op.right, space);
        break;
      
      case GREATER:
        printf(">:\n");
        space++;
        printExpr(bexpr->attr.op.left, space);
        printExpr(bexpr->attr.op.right, space);
        break;
      
      case GREATER_OR_EQUAL:
        printf("<=:\n");
        space++;
        printExpr(bexpr->attr.op.left, space);
        printExpr(bexpr->attr.op.right, space);
        break;
      
      case SMALLER_OR_EQUAL:
        printf(">=:\n");
        space++;
        printExpr(bexpr->attr.op.left,space);
        printExpr(bexpr->attr.op.right, space);
       break;
    }
  }
}

void printABSTree(CmdList* cmdList, int space){

  Cmd* cmd = cmdList->cmd;

  while(cmdList != NULL){

    printSpace(space);
    switch(cmd->kind){

      case CMD_DECLINT:
        printf("int:\n");
        printSpace(space+1);
        printf("%s =:\n", cmd->attr.declarationInt.vname);
        printExpr(cmd->attr.declarationInt.expr, space+2);
        printLine();
        break;

      case CMD_DECLBOOL:
        printf("bool:\n");
        printSpace(space+1);
        printf("%s =:\n", cmd->attr.declarationBool.vname);
        printBooleanExpr(cmd->attr.declarationBool.bexpr, space + 2);
        printLine();
        break;

      case CMD_DECLSTRING:
        printf("string:\n");
        printSpace(space+1);
        printf("%s =:\n", cmd->attr.declarationString.vname);
        printSpace(space+2);
        printf("%s\n", cmd->attr.declarationString.str);
        printLine();
        break;

      case CMD_IF:
        printf("if:\n");
        printBooleanExpr(cmd->attr.if_state.cond, space + 1);
        if(cmd->attr.if_state.bexprList != NULL){
          printBexprList(cmd->attr.if_state.bexprList, space + 1);
        }

        printLine();
        printCmdList(cmd->attr.if_state.cmdList, space+1); 
        space++;       
        if(cmd->attr.if_state.cmdElse != NULL){
          printSpace(space);
          printf("else:\n");
          printABSTree(cmd->attr.if_state.cmdElse->attr.else_state.cmdList, space + 1);
        }
        break;

      case CMD_WHILE:
        printf("while:\n");
        printBooleanExpr(cmd->attr.whiles.cond, space + 1);
        printLine();
        printABSTree(cmd->attr.whiles.cmdList, space + 1);
        break;      

      case CMD_FOR:
        printf("for:\n");
        printSpace(space+1);
        printf("int:\n");
        printSpace(space+2);
        printf("%s =:\n", cmd->attr.forLoop.forStatement->attr.for_Statement.vname);
        printExpr(cmd->attr.forLoop.forStatement->attr.for_Statement.expr, space + 3);
        printBooleanExpr(cmd->attr.forLoop.forStatement->attr.for_Statement.cond, space + 1);
        printExpr(cmd->attr.forLoop.forStatement->attr.for_Statement.expr2, space + 1);
        printCmdList(cmd->attr.forLoop.cmdList, space+1);
        break;  

      case CMD_PRINT_INT:
        printf("print_int:\n");
        printExpr(cmd->attr.print_int.expr, space+1);
        break;


      case CMD_PRINT_STR:
        printf("print_str:\n");
        printSpace(space+1);
        printf("%s\n", cmd->attr.print_str.str);
        break;


      case CMD_SCAN_INT:
        printf("%s =:\n", cmd->attr.scan_int.vname);
        printSpace(space+1);
        printf("scan_int:\n");
        break;


      case CMD_RETURN: 
        printf("return:\n");
        printExpr(cmd->attr.returnCmd.expr, space+2);
        break;


      case CMD_DECLVARIABLE:
        printf("int:\n");        
        printSpace(space+1);
        printf("%s\n", cmd->attr.declarationVariable.vname);
        if(cmd->attr.declarationVariable.next != NULL){
          printVariablesList(cmd->attr.declarationVariable.next, space+1);
        }
        break;

      case CMD_EQUALS:
        printf("%s =:\n", cmd->attr.equals.vname);
        printExpr(cmd->attr.equals.expr, space+2);
        break;
    }

    if(cmdList->next != NULL){
      cmdList = cmdList->next;
      cmd = cmdList->cmd;
    }
    else{
      break;
    }
  }

  return;
}


void printVariablesList(VariablesList* variables, int space){

  if(variables->next != NULL){
    printSpace(space);
    printf("%s\n", variables->vname);
    printVariablesList(variables->next, space);
  }
  else{
    printSpace(space);
    printf("%s\n", variables->vname);
    printLine();
  }
}

void printBexprList(BexprList* bexprList, int space){


  BexprList* node = bexprList;

  printBooleanExpr(node -> bexpr, space);
  if(node -> next != NULL){

    printBexprList(node -> next, space);
  }

}

void printSpace(int space){

    for(int i = 0;i < space;i++){
      printf("  ");
    }
  return;
}

void printLine(){

    printf("\n");
return;
}


void printCmdList(CmdList* cmdList, int space) {

  CmdList* node = cmdList;

  while(node != NULL) {

    printABSTree(node, space);
    node = node->next;
  }
}


int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
      printf("int main():\n\n");
      printABSTree(root, 2);
      printf("\n");
  }
  return 0;


}
