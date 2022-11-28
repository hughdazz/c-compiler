/* simplest version of calculator */

%{
#include <stdio.h>
#include "../../deps/cjson/cJSON.h"
#include "parse_def.h"
#define YYSTYPE cJSON *
#include "lex.yy.h"

int yyerror(yyscan_t scanner,const char *s);
extern int yylex();
extern int yyparse();
extern YYSTYPE yylval;
YYSTYPE parse_ret;
int ret;

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

%token     
    SEMI
    COMMA

    GT
    LT
    NE
    EQ
    GE
    LE
    
    ASSIGNOP
    PLUS
    MINUS
    STAR
    DIV
    AND
    OR
    DOT
    NOT

    LP 
    RP
    LC
    RC
    LB
    RB

    INT
    FLOAT

    IF
    ELSE
    WHILE
    STRUCT
    RETURN

    ID
    NUMBER
    REAL


%left ASSIGNOP
%left OR
%left AND
%left GT LT NE EQ GE LE

%left PLUS MINUS
%left STAR DIV
%right NOT
%left DOT LB LP

%right ELSE

%nonassoc UMINUS


%%
command : 
        | Program {parse_ret = $$;}
        ;
/*High Level Definitions*/
Program : ExtDefList
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Program");
        cJSON_AddItemToObject($$, "ExtDefList", $1);
    }
    ;
ExtDefList : ExtDef ExtDefList
    {
        $$ = cJSON_CreateArray();
        cJSON_AddItemToArray($$, $1);
        for (int i = 0; i < cJSON_GetArraySize($2); i++) {
            cJSON_AddItemToArray($$, cJSON_GetArrayItem($2, i));
        }
    }
    | /* empty */
    {
        $$ = cJSON_CreateArray();
    }
    ;
ExtDef : Specifier ExtDecList SEMI
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "ExtDef");
        cJSON_AddStringToObject($$, "sub_type", "ExtDecList");
        cJSON_AddItemToObject($$, "Specifier", $1);
        cJSON_AddItemToObject($$, "ExtDecList", $2);
    }
    | Specifier SEMI
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "ExtDef");
        cJSON_AddStringToObject($$, "sub_type", "Specifier");
        cJSON_AddItemToObject($$, "Specifier", $1);
    }
    | Specifier FunDec CompSt
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "ExtDef");
        cJSON_AddStringToObject($$, "sub_type", "FunDec");
        cJSON_AddItemToObject($$, "Specifier", $1);
        cJSON_AddItemToObject($$, "FunDec", $2);
        cJSON_AddItemToObject($$, "CompSt", $3);
    }
    ;
ExtDecList : VarDec
    {
        $$ = cJSON_CreateArray();
        cJSON_AddItemToArray($$,$1);
    }
    | VarDec COMMA ExtDecList
    {
        $$ = cJSON_CreateArray();
        cJSON_AddItemToArray($$,$1);
        for (int i = 0; i < cJSON_GetArraySize($3); i++) {
            cJSON_AddItemToArray($$, cJSON_GetArrayItem($3, i));
        }
    }
    ;
/*Specifiers*/
Specifier : INT
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Specifier");
        cJSON_AddStringToObject($$, "sub_type", "int");
    }
    | FLOAT
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Specifier");
        cJSON_AddStringToObject($$, "sub_type", "float");
    }
    | StructSpecifier
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Specifier");
        cJSON_AddStringToObject($$, "sub_type", "struct");
        cJSON_AddItemToObject($$, "StructSpecifier", $1);
    }
    ;
StructSpecifier : STRUCT OptTag LC DefList RC
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "StructSpecifier");
        cJSON_AddItemToObject($$, "OptTag", $2);
        cJSON_AddItemToObject($$, "DefList", $4);
    }
    | STRUCT Tag
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "StructSpecifier");
        cJSON_AddItemToObject($$, "Tag", $2);
    }
    ;
OptTag : ID
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "OptTag");
        cJSON_AddItemToObject($$, "name", $1);
    }
    | /* empty */
    {
        //添加null
        $$ = cJSON_CreateNull();
    }
    ;
Tag : ID
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Tag");
        cJSON_AddItemToObject($$, "name", $1);
    }
    ;
/*Declarators*/
VarDec : ID
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "VarDec");
        cJSON_AddStringToObject($$, "sub_type", "elem");
        cJSON_AddItemToObject($$, "name", $1);

    }
    | VarDec LB NUMBER RB
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "VarDec");
        cJSON_AddStringToObject($$, "sub_type", "array");
        //父类型
        cJSON_AddItemToObject($$, "VarDec", $1);
        cJSON_AddItemToObject($$, "size", $3);
    }
    ;
FunDec : ID LP VarList RP
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "FunDec");
        cJSON_AddItemToObject($$, "name", $1);
        cJSON_AddItemToObject($$, "VarList", $3);
    }
    | ID LP RP
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "FunDec");
        cJSON_AddItemToObject($$, "name", $1);
        cJSON_AddItemToObject($$, "VarList", cJSON_CreateArray());
    }
    ;
VarList : ParamDec COMMA VarList
    {
        $$ = cJSON_CreateArray();
        cJSON_AddItemToArray($$, $1);
        for (int i = 0; i < cJSON_GetArraySize($3); i++) {
            cJSON_AddItemToArray($$, cJSON_GetArrayItem($3, i));
        }
    }
    | ParamDec
    {
        $$ = cJSON_CreateArray();
        cJSON_AddItemToArray($$,$1);
    }
    ;
ParamDec : Specifier VarDec
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "ParamDec");
        cJSON_AddItemToObject($$, "Specifier", $1);
        cJSON_AddItemToObject($$, "VarDec", $2);
    }
    ;
/*Statements*/
CompSt : LC DefList StmtList RC
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Stmt");
        cJSON_AddStringToObject($$, "sub_type", "CompSt");
        cJSON_AddItemToObject($$, "DefList", $2);
        cJSON_AddItemToObject($$, "StmtList", $3);
    }
    ;
StmtList : Stmt StmtList
    {
        $$ = cJSON_CreateArray();
        cJSON_AddItemToArray($$, $1);
        for (int i = 0; i < cJSON_GetArraySize($2); i++) {
            cJSON_AddItemToArray($$, cJSON_GetArrayItem($2, i));
        }
    }
    | /* empty */
    {
        $$ = cJSON_CreateArray();
    }
    ;
    
Stmt : Exp SEMI
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Stmt");
        cJSON_AddItemToObject($$, "Exp", $1);
        cJSON_AddStringToObject($$, "sub_type", "ExpStmt");
    }
    | CompSt
    {
        $$ = $1;

    }
    | RETURN Exp SEMI
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Stmt");
        cJSON_AddItemToObject($$, "Exp", $2);
        cJSON_AddStringToObject($$, "sub_type", "ReturnStmt");
    }
    | IF LP Exp RP Stmt
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Stmt");
        cJSON_AddItemToObject($$, "Exp", $3);
        cJSON_AddItemToObject($$, "Stmt", $5);
        cJSON_AddStringToObject($$, "sub_type", "IfStmt");
    }
    | IF LP Exp RP Stmt ELSE Stmt
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Stmt");
        cJSON_AddItemToObject($$, "Exp", $3);
        cJSON_AddItemToObject($$, "Stmt", $5);
        cJSON_AddItemToObject($$, "ElseStmt", $7);
        cJSON_AddStringToObject($$, "sub_type", "IfElseStmt");
    }
    | WHILE LP Exp RP Stmt
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Stmt");
        cJSON_AddItemToObject($$, "Exp", $3);
        cJSON_AddItemToObject($$, "Stmt", $5);
        cJSON_AddStringToObject($$, "sub_type", "WhileStmt");
    }
    ;
/*Local Definitions*/
DefList : Def DefList
    {
        $$ = cJSON_CreateArray();
        cJSON_AddItemToArray($$, $1);
        for (int i = 0; i < cJSON_GetArraySize($2); i++) {
            cJSON_AddItemToArray($$, cJSON_GetArrayItem($2, i));
        }
    }
    | /* empty */
    {
        $$ = cJSON_CreateArray();
    }
    ;
Def : Specifier DecList SEMI
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Def");
        cJSON_AddItemToObject($$, "Specifier", $1);
        cJSON_AddItemToObject($$, "DecList", $2);
    }
    ;
DecList : Dec
    {   
        $$ = cJSON_CreateArray();
        cJSON_AddItemToArray($$, $1);
    }
    | Dec COMMA DecList
    {
        $$ = cJSON_CreateArray();
        cJSON_AddItemToArray($$, $1);
        for (int i = 0; i < cJSON_GetArraySize($3); i++) {
            cJSON_AddItemToArray($$, cJSON_GetArrayItem($3, i));
        }
    }
    ;
Dec : VarDec
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Dec");
        cJSON_AddItemToObject($$, "VarDec", $1);
    }
    | VarDec ASSIGNOP Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Dec");
        cJSON_AddItemToObject($$, "VarDec", $1);
        cJSON_AddItemToObject($$, "Exp", $3);
    }
    ;
/*Expressions*/

Exp : Exp ASSIGNOP Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", "=");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp AND Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", "&&");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp OR Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", "||");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp GT Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", ">");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp LT Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", "<");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp NE Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", "!=");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp EQ Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", "==");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp GE Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", ">=");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp LE Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", "<=");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp PLUS Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", "+");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp MINUS Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", "-");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp STAR Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", "*");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp DIV Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "BinaryExp");
        cJSON_AddStringToObject($$, "op", "/");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | LP Exp RP
    {
        $$ = $2;
    }
    | MINUS Exp %prec UMINUS
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "UnaryExp");
        cJSON_AddStringToObject($$, "op", "-");
        cJSON_AddItemToObject($$, "Exp", $2);
    }
    | NOT Exp
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "UnaryExp");
        cJSON_AddStringToObject($$, "op", "!");
        cJSON_AddItemToObject($$, "Exp", $2);
    }
    | ID LP Args RP
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "FuncCall");
        cJSON_AddItemToObject($$, "name", $1);
        cJSON_AddItemToObject($$, "Args", $3);  
    }
    | ID LP RP
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "FuncCall");
        cJSON_AddItemToObject($$, "name", $1);
        cJSON_AddItemToObject($$, "Args", cJSON_CreateArray());
    }
    | Exp LB Exp RB
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "ArrayExp");
        cJSON_AddItemToObject($$, "Exp1", $1);
        cJSON_AddItemToObject($$, "Exp2", $3);
    }
    | Exp DOT ID
    {
        $$ = cJSON_CreateObject();
        cJSON_AddStringToObject($$, "type", "Exp");
        cJSON_AddStringToObject($$, "sub_type", "StructExp");
        cJSON_AddItemToObject($$, "Exp", $1);
        cJSON_AddItemToObject($$, "name", $3);
    }
    | ID
    {
        $$ = $1;
    }
    | NUMBER
    {
        $$ = $1;
    }
    | REAL
    {
        $$ = $1;
    }
    ;
Args : Exp COMMA Args
    {
        $$ = cJSON_CreateArray();
        cJSON_AddItemToArray($$, $1);
        for(int i = 0; i < cJSON_GetArraySize($3); i++)
        {
            cJSON_AddItemToArray($$, cJSON_GetArrayItem($3, i));
        }
    }
    | Exp
    {
        $$ = cJSON_CreateArray();
        cJSON_AddItemToArray($$, $1);
    } 
    ;

%%


extern void scan_string(const char *str, yyscan_t scanner);

int c_parse(const char *s, cJSON** syntax_tree)
{
    yyscan_t scanner;
    yylex_init(&scanner);
    scan_string(s, scanner);
    int ret = yyparse(scanner);
    yylex_destroy(scanner);
    *syntax_tree = parse_ret;
    return ret;
}
int yyerror(yyscan_t scanner,const char *s)
{
    printf("error: %s\n\n", s);
    return ret;
}