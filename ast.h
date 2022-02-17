
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_BOOL,
    E_VAR,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    bool booleanValue;
    char* varname; // for vars
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _BooleanExpr {
  enum { 
    E_BOOLEAN,
    E_BOOLEAN_OPERATION
  } kind;
  union {
    int value; // for integer values
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _Cmd{
  enum{
      CMD_DECLVARIABLE,
      CMD_DECLINT,
      CMD_DECLBOOL,
      CMD_DECLSTRING,
      CMD_IF,
      CMD_ELSE,
      CMD_WHILE,
      CMD_FOR,
      CMD_FORSTATEMENT,
      CMD_EQUALS,
      CMD_PRINT_INT,
      CMD_PRINT_STR,
      CMD_SCAN_INT,
      CMD_RETURN,
      CMD_FUNCTIONS

  }kind;

  union{
      
      struct{
        struct _Expr* expr;
        char* vname;
      }declarationInt;

      struct{
        struct _BooleanExpr* bexpr;
        char* vname;
      }declarationBool;

      struct{
        char* str;
        char* vname;
      }declarationString;
      
      struct{
        struct _CmdList *cmdList;
        struct _BooleanExpr* cond;
        struct _Cmd *cmdElse;
        struct _BexprList *bexprList;
      }if_state;
      
      struct{
        struct _CmdList *cmdList;
      }else_state;
      
      struct{
        struct _CmdList *cmdList;
        struct _BooleanExpr* cond;
      }whiles;
      
      struct{
        struct _Cmd *forStatement;
        struct _CmdList *cmdList;
      }forLoop;

      struct{

        struct _BooleanExpr* cond;
        struct _Expr* expr;
        struct _Expr* expr2;
        char* vname;    
      }for_Statement;

      struct{
        struct _Expr* expr;
      }print_int;

      struct{
        char* str;
      }print_str;

      struct{
        char* vname;
      }scan_int;

      struct{
        char* vname;
        struct VariablesList* next;
      }declarationVariable;

      struct{
        char* vname;
        struct _Expr* expr;
      }equals;

      struct{
        struct _Expr* expr;
      }returnCmd;
      
    }attr;
  };

struct _VariablesList{
  char* vname;
  struct _VariablesList* next;
};

struct _BexprList{
  struct _BooleanExpr* bexpr;
  struct _BexprList* next;
};


struct _CmdList{
  struct _Cmd *cmd;
  struct _CmdList *next;
};


typedef struct _Expr Expr;
typedef struct _BooleanExpr BooleanExpr;
typedef struct _Cmd Cmd;
typedef struct _CmdList CmdList;
typedef struct _VariablesList VariablesList;
typedef struct _BexprList BexprList;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_variable(char* v);
BooleanExpr* ast_boolean(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BooleanExpr* ast_boolOperation(int operator, Expr* left, Expr* right);
Cmd* ast_cmdIf(BooleanExpr* cond, BexprList* bexpList, CmdList* cmdList, Cmd* cmdElse);
Cmd* ast_cmdElse(CmdList* cmdList);
Cmd* ast_cmdWhile(BooleanExpr* cond, CmdList* cmdList);
Cmd* ast_cmdFor(Cmd* forStatement,CmdList* cmdList);
Cmd* ast_cmdForStatement(char* vname, Expr* expr, BooleanExpr* cond, Expr* expr2);
Cmd* ast_cmdPrintInt(Expr* expr);
Cmd* ast_cmdPrintStr(char* str);
Cmd* ast_cmdScanInt(char* vname);
Cmd* ast_cmdDeclarationVariable(char* vname, VariablesList* variables);
Cmd* ast_cmdDeclarationInt(char* vname, Expr* expr);
Cmd* ast_cmdDeclarationBool(char* vname, BooleanExpr* bexpr);
Cmd* ast_cmdDeclarationString(char* vname, char* str);
Cmd* ast_cmdDeclarationEquals(char* vname, Expr* expr);
Cmd* ast_cmdReturn(Expr* expr);
CmdList* ast_cmdList(Cmd* cmd, CmdList* next);
VariablesList* ast_cmdVariablesList(char* vname, VariablesList* next);
BexprList* ast_cmdBexprList(BooleanExpr* bexpr, BexprList* next);

#endif
