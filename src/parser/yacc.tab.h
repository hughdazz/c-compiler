/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_COM_DOCKER_DEVENVIRONMENTS_CODE_C_COMPILER_SRC_PARSER_YACC_TAB_H_INCLUDED
# define YY_YY_COM_DOCKER_DEVENVIRONMENTS_CODE_C_COMPILER_SRC_PARSER_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMI = 258,                    /* SEMI  */
    COMMA = 259,                   /* COMMA  */
    GT = 260,                      /* GT  */
    LT = 261,                      /* LT  */
    NE = 262,                      /* NE  */
    EQ = 263,                      /* EQ  */
    GE = 264,                      /* GE  */
    LE = 265,                      /* LE  */
    ASSIGNOP = 266,                /* ASSIGNOP  */
    PLUS = 267,                    /* PLUS  */
    MINUS = 268,                   /* MINUS  */
    STAR = 269,                    /* STAR  */
    DIV = 270,                     /* DIV  */
    AND = 271,                     /* AND  */
    OR = 272,                      /* OR  */
    DOT = 273,                     /* DOT  */
    NOT = 274,                     /* NOT  */
    LP = 275,                      /* LP  */
    RP = 276,                      /* RP  */
    LC = 277,                      /* LC  */
    RC = 278,                      /* RC  */
    LB = 279,                      /* LB  */
    RB = 280,                      /* RB  */
    INT = 281,                     /* INT  */
    FLOAT = 282,                   /* FLOAT  */
    IF = 283,                      /* IF  */
    ELSE = 284,                    /* ELSE  */
    WHILE = 285,                   /* WHILE  */
    FOR = 286,                     /* FOR  */
    STRUCT = 287,                  /* STRUCT  */
    RETURN = 288,                  /* RETURN  */
    ID = 289,                      /* ID  */
    NUMBER = 290,                  /* NUMBER  */
    REAL = 291,                    /* REAL  */
    UMINUS = 292                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_COM_DOCKER_DEVENVIRONMENTS_CODE_C_COMPILER_SRC_PARSER_YACC_TAB_H_INCLUDED  */
