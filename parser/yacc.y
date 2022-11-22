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


%%
command :
        | Program
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
RELOP: GT
    {
        printf("RELOP\n");
    }
    | LT
    {
        printf("RELOP\n");
    }
    | NE
    {
        printf("RELOP\n");
    }
    | EQ
    {
        printf("RELOP\n");
    }
    | GE
    {
        printf("RELOP\n");
    }
    | LE
    {
        printf("RELOP\n");
    }
    ;
sub_term : ID
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
term : sub_term
    {
        printf("Exp\n");
    }
    | LP Exp RP
    {
        printf("Exp\n");
    }
    | MINUS Exp
    {
        printf("Exp\n");
    }
    | NOT Exp
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

    ;
factor : term
    {
        printf("Exp\n");
    }
    | term STAR factor
    {
        printf("Exp\n");
    }
    | term DIV factor
    {
        printf("Exp\n");
    }
    ;
LogicExp : RelExp
    {
        printf("Exp\n");
    }
    | RelExp AND LogicExp
    {
        printf("Exp\n");
    }
    | RelExp OR LogicExp
    {
        printf("Exp\n");
    }
    ;
RelExp : ArithExp
    {
        printf("Exp\n");
    }
    | ArithExp RELOP RelExp
    {
        printf("Exp\n");
    }
    ;
ArithExp : factor
    {
        printf("Exp\n");
    }
    | factor PLUS ArithExp
    {
        printf("Exp\n");
    }
    | factor MINUS ArithExp
    {
        printf("Exp\n");
    }
    ;
//VIRTUAL NODES END//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

Exp : ID ASSIGNOP LogicExp
    {
        printf("Exp\n");
    }
    | LogicExp
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