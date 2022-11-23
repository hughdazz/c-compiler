/* simplest version of calculator */

%{
#include <stdio.h>
int yyerror(const char *);
extern int yylex();
extern int yyparse();
extern int int_val;
extern float float_val;
extern char sstr[100];
int ret;
%}

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

    NUMBER
    REAL
    ID

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
command : Program
        ;
/*High Level Definitions*/
Program : ExtDefList
    {
        printf("Program\n");
    }
    ;
ExtDefList : ExtDef ExtDefList
    {
        printf("ExtDefList\n");
    }
    | /* empty */
    {
        printf("ExtDefList\n");
    }
    ;
ExtDef : Specifier ExtDecList SEMI
    {
        printf("ExtDef\n");
    }
    | Specifier SEMI
    {
        printf("ExtDef\n");
    }
    | Specifier FunDec CompSt
    {
        printf("ExtDef\n");
    }
    ;
ExtDecList : VarDec
    {
        printf("ExtDecList\n");
    }
    | VarDec COMMA ExtDecList
    {
        printf("ExtDecList\n");
    }
    ;
/*Specifiers*/
Specifier : INT
    {
        printf("Specifier\n");
    }
    | FLOAT
    {
        printf("Specifier\n");
    }
    | StructSpecifier
    {
        printf("Specifier\n");
    }
    ;
StructSpecifier : STRUCT OptTag LC DefList RC
    {
        printf("StructSpecifier\n");
    }
    | STRUCT Tag
    {
        printf("StructSpecifier\n");
    }
    ;
OptTag : ID
    {
        printf("OptTag\n");
    }
    | /* empty */
    {
        printf("OptTag\n");
    }
    ;
Tag : ID
    {
        printf("Tag\n");
    }
    ;
/*Declarators*/
VarDec : ID
    {
        printf("VarDec\n");
    }
    | VarDec LB INT RB
    {
        printf("VarDec\n");
    }
    ;
FunDec : ID LP VarList RP
    {
        printf("FunDec\n");
    }
    | ID LP RP
    {
        printf("FunDec\n");
    }
    ;
VarList : ParamDec COMMA VarList
    {
        printf("VarList\n");
    }
    | ParamDec
    {
        printf("VarList\n");
    }
    ;
ParamDec : Specifier VarDec
    {
        printf("ParamDec\n");
    }
    ;
/*Statements*/
CompSt : LC DefList StmtList RC
    {
        printf("CompSt\n");
    }
    ;
StmtList : Stmt StmtList
    {
        printf("StmtList\n");
    }
    | /* empty */
    {
        printf("StmtList\n");
    }
    ;
    
Stmt : Exp SEMI
    {
        printf("Stmt\n");
    }
    | CompSt
    {
        printf("Stmt\n");
    }
    | RETURN Exp SEMI
    {
        printf("Stmt\n");
    }
    | IF LP Exp RP Stmt
    {
        printf("Stmt\n");
    }
    | IF LP Exp RP Stmt ELSE Stmt
    {
        printf("Stmt\n");
    }
    | WHILE LP Exp RP Stmt
    {
        printf("Stmt\n");
    }
    ;
/*Local Definitions*/
DefList : Def DefList
    {
        printf("DefList\n");
    }
    | /* empty */
    {
        printf("DefList\n");
    }
    ;
Def : Specifier DecList SEMI
    {
        printf("Def\n");
    }
    ;
DecList : Dec
    {
        printf("DecList\n");
    }
    | Dec COMMA DecList
    {
        printf("DecList\n");
    }
    ;
Dec : VarDec
    {
        printf("Dec\n");
    }
    | VarDec ASSIGNOP Exp
    {
        printf("Dec\n");
    }
    ;
/*Expressions*/
/////////////////////////////////////////////////////////////////////////////////////////
//VIRTUAL NODES START////////////////////////////////////////////////////////////////////

//VIRTUAL NODES END//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

Exp : Exp ASSIGNOP Exp
    {
        printf("Exp\n");
    }
    | Exp AND Exp
    {
        printf("Exp\n");
    }
    | Exp OR Exp
    {
        printf("Exp\n");
    }
    | Exp GT Exp
    {
        printf("Exp\n");
    }
    | Exp LT Exp
    {
        printf("Exp\n");
    }
    | Exp NE Exp
    {
        printf("Exp\n");
    }
    | Exp EQ Exp
    {
        printf("Exp\n");
    }
    | Exp GE Exp
    {
        printf("Exp\n");
    }
    | Exp LE Exp
    {
        printf("Exp\n");
    }
    | Exp PLUS Exp
    {
        printf("Exp\n");
    }
    | Exp MINUS Exp
    {
        printf("Exp\n");
    }
    | Exp STAR Exp
    {
        printf("Exp\n");
    }
    | Exp DIV Exp
    {
        printf("Exp\n");
    }
    | LP Exp RP
    {
        printf("Exp\n");
    }
    | MINUS Exp %prec UMINUS
    {
        printf("Exp\n");
    }
    | NOT Exp
    {
        printf("Exp\n");
    }
    | ID LP Args RP
    {
        printf("Exp\n");
    }
    | ID LP RP
    {
        printf("Exp\n");
    }
    | Exp LB Exp RB
    {
        printf("Exp\n");
    }
    | Exp DOT ID
    {
        printf("Exp\n");
    }
    | ID
    {
        printf("Exp\n");
    }
    | NUMBER
    {
        printf("Exp\n");
    }
    | REAL
    {
        printf("Exp\n");
    }
    ;
Args : Exp COMMA Args
    {
        printf("Args\n");
    }
    | Exp
    {
        printf("Args\n");
    } 
    ;

%%
int main()
{
    yyparse();
    return 0;
}
int yyerror(const char *s)
{
    printf("error: %s\n", s);
    return ret;
}