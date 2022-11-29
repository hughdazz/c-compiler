%{// c定义
#include "../../deps/cjson/cJSON.h"
#define YYSTYPE cJSON*
#include"yacc.tab.h"
// #include"parse_def.h"
// printf\(([\S\s]+)\);
// /*printf($1)*/
%}
/* Prevent the need for linking with -lfl */
%option noyywrap
%option bison-bridge
%option reentrant


%%

[0-9]+                  { 
                            cJSON* item = cJSON_CreateObject();
                            cJSON_AddStringToObject(item,"value",strdup(yytext));
                            cJSON_AddStringToObject(item,"type","number");
                            *yylval = item;
                            return NUMBER;
                        }
[0-9]+[.][0-9]+         { 
                            cJSON* item = cJSON_CreateObject();
                            cJSON_AddStringToObject(item,"value",strdup(yytext));
                            cJSON_AddStringToObject(item,"type","real");
                            *yylval = item;
                            return REAL;
                        }
";"                     {   /*printf("SEMI\n")*/ return SEMI;}
","                     {   /*printf("COMMA\n")*/ return COMMA;}

">"                     {   /*printf("GT\n")*/  return GT;}
"<"                     {   /*printf("LT\n")*/ return LT;}
"!="                    {   /*printf("NE\n")*/ return NE;}
"=="                    {   /*printf("EQ\n")*/ return EQ;}
">="                    {   /*printf("GE\n")*/ return GE;}
"<="                    {   /*printf("LE\n")*/ return LE;}

"="                     {   /*printf("ASSIGNOP\n")*/ return ASSIGNOP;}
"+"                     {   /*printf("PLUS\n")*/ return PLUS;}
"-"                     {   /*printf("MINUS\n")*/ return MINUS;}          
"*"                     {   /*printf("STAR\n")*/ return STAR;} 
"/"                     {   /*printf("DIV\n")*/ return DIV;}
"&&"                    {   /*printf("AND\n")*/ return AND;}
"||"                    {   /*printf("OR\n")*/ return OR;}
"."                     {   /*printf("DOT\n")*/ return DOT;}
"!"                     {   /*printf("NOT\n")*/ return NOT;}

"("                     {   /*printf("LP\n")*/ return LP;}
")"                     {   /*printf("RP\n")*/ return RP;}
"{"                     {   /*printf("LC\n")*/ return LC;}
"}"                     {   /*printf("RC\n")*/ return RC;}
"["                     {   /*printf("LB\n")*/ return LB;}
"]"                     {   /*printf("RB\n")*/ return RB;}

"int"                   {   /*printf("INT\n")*/ return INT;}
"float"                 {   /*printf("FLOAT\n")*/ return FLOAT;}

"if"                    {   /*printf("IF\n")*/ return IF;}
"else"                  {   /*printf("ELSE\n")*/ return ELSE;}
"while"                 {   /*printf("WHILE\n")*/ return WHILE;}
"struct"                {   /*printf("STRUCT\n")*/ return STRUCT;}
"return"                {   /*printf("RETURN\n")*/ return RETURN;}
"for"                   {   /*printf("FOR\n")*/ return FOR;}

[//][^\r]*[\r]            {   /*printf("COMMENT\n")*/}
[/*][\S\s]*[*/]         {   /*printf("COMMENT\n")*/}

[a-zA-Z_]+[a-zA-Z0-9_]*                 {   
                            cJSON* item = cJSON_CreateObject();
                            cJSON_AddStringToObject(item,"value",strdup(yytext));
                            cJSON_AddStringToObject(item,"type","id");
                            *yylval = item;
                            return ID;
                        }
[\t" "\n]               { }

.                       { /*printf("Mystery character %s\n", yytext)*/ }
%%


void scan_string(const char *str, yyscan_t scanner) {
  yy_switch_to_buffer(yy_scan_string(str, scanner), scanner);
}