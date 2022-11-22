%{

%}
%option noyywrap
/* recognize tokens for the calculator and print them out */
%%

[0-9]+                  { printf("INTEGER %s\n", yytext); }
[0-9]+[.][0-9]+         { printf("REAL %s\n", yytext); }
";"                     { printf("SEMI\n"); }
","                     { printf("COMMA\n"); }

">"                     { printf("GT\n"); }
"<"                     { printf("LT\n"); }
"!="                    { printf("NE\n"); }
"=="                    { printf("EQ\n"); }
">="                    { printf("GE\n"); }
"<="                    { printf("LE\n"); }

"="                     { printf("ASSIGNOP\n"); }
"+"                     { printf("PLUS\n"); }
"-"                     { printf("MINUS\n"); }          
"*"                     { printf("STAR\n"); } 
"/"                     { printf("DIV\n"); }
"&&"                    { printf("AND\n"); }
"||"                    { printf("OR\n"); }
"."                     { printf("DOT\n"); }
"!"                     { printf("NOT\n"); }
"int"|"float"           { printf("TYPE %s\n",yytext); }

"("                     { printf("LP\n"); }
")"                     { printf("RP\n"); }
"{"                     { printf("LC\n"); }
"}"                     { printf("RC\n"); }
"["                     { printf("LB\n"); }
"]"                     { printf("RB\n"); }

"if"                    { printf("IF\n"); }
"else"                  { printf("ELSE\n"); }
"while"                 { printf("WHILE\n"); }
"struct"                { printf("STRUCT\n"); }
"return"                { printf("RETURN\n"); }

[a-zA-Z]+[a-zA-Z_]      { printf("IDENTIFIER %s\n", yytext); }
[\t" "\n]               { }

.                       { printf("Mystery character %s\n", yytext); }
%%
int main(int argc, char **argv)
{
    yylex();
}