/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"

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


#line 87 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMI = 3,                       /* SEMI  */
  YYSYMBOL_COMMA = 4,                      /* COMMA  */
  YYSYMBOL_GT = 5,                         /* GT  */
  YYSYMBOL_LT = 6,                         /* LT  */
  YYSYMBOL_NE = 7,                         /* NE  */
  YYSYMBOL_EQ = 8,                         /* EQ  */
  YYSYMBOL_GE = 9,                         /* GE  */
  YYSYMBOL_LE = 10,                        /* LE  */
  YYSYMBOL_ASSIGNOP = 11,                  /* ASSIGNOP  */
  YYSYMBOL_PLUS = 12,                      /* PLUS  */
  YYSYMBOL_MINUS = 13,                     /* MINUS  */
  YYSYMBOL_STAR = 14,                      /* STAR  */
  YYSYMBOL_DIV = 15,                       /* DIV  */
  YYSYMBOL_AND = 16,                       /* AND  */
  YYSYMBOL_OR = 17,                        /* OR  */
  YYSYMBOL_DOT = 18,                       /* DOT  */
  YYSYMBOL_NOT = 19,                       /* NOT  */
  YYSYMBOL_LP = 20,                        /* LP  */
  YYSYMBOL_RP = 21,                        /* RP  */
  YYSYMBOL_LC = 22,                        /* LC  */
  YYSYMBOL_RC = 23,                        /* RC  */
  YYSYMBOL_LB = 24,                        /* LB  */
  YYSYMBOL_RB = 25,                        /* RB  */
  YYSYMBOL_INT = 26,                       /* INT  */
  YYSYMBOL_FLOAT = 27,                     /* FLOAT  */
  YYSYMBOL_IF = 28,                        /* IF  */
  YYSYMBOL_ELSE = 29,                      /* ELSE  */
  YYSYMBOL_WHILE = 30,                     /* WHILE  */
  YYSYMBOL_STRUCT = 31,                    /* STRUCT  */
  YYSYMBOL_RETURN = 32,                    /* RETURN  */
  YYSYMBOL_ID = 33,                        /* ID  */
  YYSYMBOL_NUMBER = 34,                    /* NUMBER  */
  YYSYMBOL_REAL = 35,                      /* REAL  */
  YYSYMBOL_UMINUS = 36,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_command = 38,                   /* command  */
  YYSYMBOL_Program = 39,                   /* Program  */
  YYSYMBOL_ExtDefList = 40,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 41,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 42,                /* ExtDecList  */
  YYSYMBOL_Specifier = 43,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 44,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 45,                    /* OptTag  */
  YYSYMBOL_Tag = 46,                       /* Tag  */
  YYSYMBOL_VarDec = 47,                    /* VarDec  */
  YYSYMBOL_FunDec = 48,                    /* FunDec  */
  YYSYMBOL_VarList = 49,                   /* VarList  */
  YYSYMBOL_ParamDec = 50,                  /* ParamDec  */
  YYSYMBOL_CompSt = 51,                    /* CompSt  */
  YYSYMBOL_StmtList = 52,                  /* StmtList  */
  YYSYMBOL_Stmt = 53,                      /* Stmt  */
  YYSYMBOL_DefList = 54,                   /* DefList  */
  YYSYMBOL_Def = 55,                       /* Def  */
  YYSYMBOL_DecList = 56,                   /* DecList  */
  YYSYMBOL_Dec = 57,                       /* Dec  */
  YYSYMBOL_Exp = 58,                       /* Exp  */
  YYSYMBOL_Args = 59                       /* Args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   312

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  123

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    81,    81,    82,    85,    92,   101,   105,   113,   120,
     130,   135,   145,   151,   157,   165,   172,   179,   186,   191,
     199,   207,   217,   224,   232,   240,   246,   255,   264,   273,
     278,   285,   290,   297,   305,   314,   324,   333,   337,   345,
     350,   359,   365,   375,   384,   393,   402,   411,   420,   429,
     438,   447,   456,   465,   474,   483,   492,   496,   504,   512,
     520,   528,   536,   544,   548,   552,   557,   566
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMI", "COMMA", "GT",
  "LT", "NE", "EQ", "GE", "LE", "ASSIGNOP", "PLUS", "MINUS", "STAR", "DIV",
  "AND", "OR", "DOT", "NOT", "LP", "RP", "LC", "RC", "LB", "RB", "INT",
  "FLOAT", "IF", "ELSE", "WHILE", "STRUCT", "RETURN", "ID", "NUMBER",
  "REAL", "UMINUS", "$accept", "command", "Program", "ExtDefList",
  "ExtDef", "ExtDecList", "Specifier", "StructSpecifier", "OptTag", "Tag",
  "VarDec", "FunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt",
  "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291
};
#endif

#define YYPACT_NINF (-48)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-18)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     281,   -48,   -48,    -8,    43,   -48,   -48,   281,    11,   -48,
      28,    34,   -48,   -48,   -48,   -48,    38,    51,     2,    42,
     281,   275,   -48,    40,    46,   281,   -48,    40,    59,   281,
     -48,    40,    53,    98,   -48,   -48,    78,    27,    -7,   101,
     118,   -48,   -48,    81,   -48,   281,   -48,    50,    50,    50,
     104,   105,    50,   106,   -48,   -48,   -48,   100,    27,    83,
      50,   -48,    40,   -48,   -48,    -2,   165,    50,    50,   103,
      32,   -48,   -48,   -48,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,   110,    50,   225,
     -48,   -48,   185,   205,   -48,   -48,   124,   123,    63,    63,
      63,    63,    63,    63,   245,    -6,    -6,    -2,    -2,   285,
     265,   -48,   144,    27,    27,    50,   -48,   -48,   116,   -48,
     -48,    27,   -48
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,    12,    13,    18,     0,     3,     4,     6,     0,    14,
      19,     0,    16,     1,     5,     8,    20,     0,    10,     0,
      37,     0,     7,     0,     0,    37,     9,     0,     0,    37,
      23,     0,     0,    25,    20,    11,     0,    29,    41,     0,
      39,    15,    36,    26,    22,     0,    21,     0,     0,     0,
       0,     0,     0,    63,    64,    65,    31,     0,    29,     0,
       0,    38,     0,    24,    57,    58,     0,     0,     0,     0,
       0,    27,    28,    30,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
      40,    56,     0,     0,    32,    60,    67,     0,    46,    47,
      48,    49,    50,    51,    43,    52,    53,    54,    55,    44,
      45,    62,     0,     0,     0,     0,    59,    61,    33,    35,
      66,     0,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -48,   -48,   -48,   139,   -48,   140,     3,   -48,   -48,   -48,
     -20,   -48,   102,   -48,   145,   107,   -42,   -10,   -48,   122,
     -48,   -47,    52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,    17,    27,     9,    11,    12,
      18,    19,    32,    33,    56,    57,    58,    28,    29,    39,
      40,    59,    97
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      64,    65,    66,     8,    60,    69,    23,    38,    83,    84,
       8,    43,    87,    89,    15,    37,    87,    24,    88,    42,
      92,    93,    88,    96,    31,    10,    24,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
      47,   112,    38,    13,    16,    47,    48,    49,    31,    25,
     -17,    48,    49,    95,    22,    50,    20,    51,    21,    52,
      53,    54,    55,    47,    25,    53,    54,    55,    96,    48,
      49,   118,   119,    34,    44,    81,    82,    83,    84,   122,
      36,    87,    41,    53,    54,    55,    73,    88,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    45,    46,    61,    24,    94,    88,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    62,    71,    67,    68,    70,    88,   115,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,   111,   116,   121,    14,    63,    88,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    35,    26,    72,     0,   120,    88,   117,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    90,     0,    91,     0,     0,    88,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,     0,     0,   113,     0,     0,    88,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,     0,     0,   114,     0,     0,    88,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,     0,     0,     0,     0,     0,    88,
      74,    75,    76,    77,    78,    79,     0,    81,    82,    83,
      84,    85,    86,    87,     0,     0,     0,     0,     0,    88,
      74,    75,    76,    77,    78,    79,     0,    81,    82,    83,
      84,    85,     0,    87,     0,     0,     0,     0,     0,    88,
      74,    75,    76,    77,    78,    79,    30,    81,    82,    83,
      84,     1,     2,    87,     0,     0,     3,     1,     2,    88,
       0,     0,     3
};

static const yytype_int8 yycheck[] =
{
      47,    48,    49,     0,    11,    52,     4,    27,    14,    15,
       7,    31,    18,    60,     3,    25,    18,    24,    24,    29,
      67,    68,    24,    70,    21,    33,    24,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      13,    88,    62,     0,    33,    13,    19,    20,    45,    22,
      22,    19,    20,    21,     3,    28,    22,    30,    20,    32,
      33,    34,    35,    13,    22,    33,    34,    35,   115,    19,
      20,   113,   114,    33,    21,    12,    13,    14,    15,   121,
      34,    18,    23,    33,    34,    35,     3,    24,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     4,    25,     3,    24,     3,    24,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     4,    23,    20,    20,    20,    24,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    33,    21,    29,     7,    45,    24,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    23,    19,    58,    -1,   115,    24,    25,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    62,    -1,    21,    -1,    -1,    24,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,    24,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,    24,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,    24,
       5,     6,     7,     8,     9,    10,    -1,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,    24,
       5,     6,     7,     8,     9,    10,    -1,    12,    13,    14,
      15,    16,    -1,    18,    -1,    -1,    -1,    -1,    -1,    24,
       5,     6,     7,     8,     9,    10,    21,    12,    13,    14,
      15,    26,    27,    18,    -1,    -1,    31,    26,    27,    24,
      -1,    -1,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,    27,    31,    38,    39,    40,    41,    43,    44,
      33,    45,    46,     0,    40,     3,    33,    42,    47,    48,
      22,    20,     3,     4,    24,    22,    51,    43,    54,    55,
      21,    43,    49,    50,    33,    42,    34,    54,    47,    56,
      57,    23,    54,    47,    21,     4,    25,    13,    19,    20,
      28,    30,    32,    33,    34,    35,    51,    52,    53,    58,
      11,     3,     4,    49,    58,    58,    58,    20,    20,    58,
      20,    23,    52,     3,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    24,    58,
      56,    21,    58,    58,     3,    21,    58,    59,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    33,    58,    21,    21,     4,    21,    25,    53,    53,
      59,    29,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    39,    40,    40,    41,    41,    41,
      42,    42,    43,    43,    43,    44,    44,    45,    45,    46,
      47,    47,    48,    48,    49,    49,    50,    51,    52,    52,
      53,    53,    53,    53,    53,    53,    54,    54,    55,    56,
      56,    57,    57,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    59,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     0,     3,     2,     3,
       1,     3,     1,     1,     1,     5,     2,     1,     0,     1,
       1,     4,     4,     3,     3,     1,     2,     4,     2,     0,
       2,     1,     3,     5,     7,     5,     2,     0,     3,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     4,
       3,     4,     3,     1,     1,     1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* command: Program  */
#line 82 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
                  {parse_ret = yyval;}
#line 1267 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 4: /* Program: ExtDefList  */
#line 86 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Program");
        cJSON_AddItemToObject(yyval, "ExtDefList", yyvsp[0]);
    }
#line 1277 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 5: /* ExtDefList: ExtDef ExtDefList  */
#line 93 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
        cJSON_AddItemToArray(yyval, yyvsp[-1]);
        for (int i = 0; i < cJSON_GetArraySize(yyvsp[0]); i++) {
            cJSON_AddItemToArray(yyval, cJSON_GetArrayItem(yyvsp[0], i));
        }
    }
#line 1289 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 6: /* ExtDefList: %empty  */
#line 101 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
    }
#line 1297 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 7: /* ExtDef: Specifier ExtDecList SEMI  */
#line 106 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "ExtDef");
        cJSON_AddStringToObject(yyval, "sub_type", "ExtDecList");
        cJSON_AddItemToObject(yyval, "Specifier", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "ExtDecList", yyvsp[-1]);
    }
#line 1309 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 8: /* ExtDef: Specifier SEMI  */
#line 114 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "ExtDef");
        cJSON_AddStringToObject(yyval, "sub_type", "Specifier");
        cJSON_AddItemToObject(yyval, "Specifier", yyvsp[-1]);
    }
#line 1320 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 9: /* ExtDef: Specifier FunDec CompSt  */
#line 121 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "ExtDef");
        cJSON_AddStringToObject(yyval, "sub_type", "FunDec");
        cJSON_AddItemToObject(yyval, "Specifier", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "FunDec", yyvsp[-1]);
        cJSON_AddItemToObject(yyval, "CompSt", yyvsp[0]);
    }
#line 1333 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 10: /* ExtDecList: VarDec  */
#line 131 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
        cJSON_AddItemToArray(yyval,yyvsp[0]);
    }
#line 1342 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 11: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 136 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
        cJSON_AddItemToArray(yyval,yyvsp[-2]);
        for (int i = 0; i < cJSON_GetArraySize(yyvsp[0]); i++) {
            cJSON_AddItemToArray(yyval, cJSON_GetArrayItem(yyvsp[0], i));
        }
    }
#line 1354 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 12: /* Specifier: INT  */
#line 146 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Specifier");
        cJSON_AddStringToObject(yyval, "sub_type", "int");
    }
#line 1364 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 13: /* Specifier: FLOAT  */
#line 152 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Specifier");
        cJSON_AddStringToObject(yyval, "sub_type", "float");
    }
#line 1374 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 14: /* Specifier: StructSpecifier  */
#line 158 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Specifier");
        cJSON_AddStringToObject(yyval, "sub_type", "struct");
        cJSON_AddItemToObject(yyval, "StructSpecifier", yyvsp[0]);
    }
#line 1385 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 15: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 166 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "StructSpecifier");
        cJSON_AddItemToObject(yyval, "OptTag", yyvsp[-3]);
        cJSON_AddItemToObject(yyval, "DefList", yyvsp[-1]);
    }
#line 1396 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 16: /* StructSpecifier: STRUCT Tag  */
#line 173 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "StructSpecifier");
        cJSON_AddItemToObject(yyval, "Tag", yyvsp[0]);
    }
#line 1406 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 17: /* OptTag: ID  */
#line 180 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "OptTag");
        cJSON_AddItemToObject(yyval, "name", yyvsp[0]);
    }
#line 1416 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 18: /* OptTag: %empty  */
#line 186 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        //添加null
        yyval = cJSON_CreateNull();
    }
#line 1425 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 19: /* Tag: ID  */
#line 192 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Tag");
        cJSON_AddItemToObject(yyval, "name", yyvsp[0]);
    }
#line 1435 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 20: /* VarDec: ID  */
#line 200 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "VarDec");
        cJSON_AddStringToObject(yyval, "sub_type", "elem");
        cJSON_AddItemToObject(yyval, "name", yyvsp[0]);

    }
#line 1447 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 21: /* VarDec: VarDec LB NUMBER RB  */
#line 208 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "VarDec");
        cJSON_AddStringToObject(yyval, "sub_type", "array");
        //父类型
        cJSON_AddItemToObject(yyval, "VarDec", yyvsp[-3]);
        cJSON_AddItemToObject(yyval, "size", yyvsp[-1]);
    }
#line 1460 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 22: /* FunDec: ID LP VarList RP  */
#line 218 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "FunDec");
        cJSON_AddItemToObject(yyval, "name", yyvsp[-3]);
        cJSON_AddItemToObject(yyval, "VarList", yyvsp[-1]);
    }
#line 1471 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 23: /* FunDec: ID LP RP  */
#line 225 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "FunDec");
        cJSON_AddItemToObject(yyval, "name", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "VarList", cJSON_CreateArray());
    }
#line 1482 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 24: /* VarList: ParamDec COMMA VarList  */
#line 233 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
        cJSON_AddItemToArray(yyval, yyvsp[-2]);
        for (int i = 0; i < cJSON_GetArraySize(yyvsp[0]); i++) {
            cJSON_AddItemToArray(yyval, cJSON_GetArrayItem(yyvsp[0], i));
        }
    }
#line 1494 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 25: /* VarList: ParamDec  */
#line 241 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
        cJSON_AddItemToArray(yyval,yyvsp[0]);
    }
#line 1503 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 26: /* ParamDec: Specifier VarDec  */
#line 247 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "ParamDec");
        cJSON_AddItemToObject(yyval, "Specifier", yyvsp[-1]);
        cJSON_AddItemToObject(yyval, "VarDec", yyvsp[0]);
    }
#line 1514 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 27: /* CompSt: LC DefList StmtList RC  */
#line 256 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Stmt");
        cJSON_AddStringToObject(yyval, "sub_type", "CompSt");
        cJSON_AddItemToObject(yyval, "DefList", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "StmtList", yyvsp[-1]);
    }
#line 1526 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 28: /* StmtList: Stmt StmtList  */
#line 265 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
        cJSON_AddItemToArray(yyval, yyvsp[-1]);
        for (int i = 0; i < cJSON_GetArraySize(yyvsp[0]); i++) {
            cJSON_AddItemToArray(yyval, cJSON_GetArrayItem(yyvsp[0], i));
        }
    }
#line 1538 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 29: /* StmtList: %empty  */
#line 273 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
    }
#line 1546 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 30: /* Stmt: Exp SEMI  */
#line 279 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Stmt");
        cJSON_AddItemToObject(yyval, "Exp", yyvsp[-1]);
        cJSON_AddStringToObject(yyval, "sub_type", "ExpStmt");
    }
#line 1557 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 31: /* Stmt: CompSt  */
#line 286 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = yyvsp[0];

    }
#line 1566 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 32: /* Stmt: RETURN Exp SEMI  */
#line 291 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Stmt");
        cJSON_AddItemToObject(yyval, "Exp", yyvsp[-1]);
        cJSON_AddStringToObject(yyval, "sub_type", "ReturnStmt");
    }
#line 1577 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 33: /* Stmt: IF LP Exp RP Stmt  */
#line 298 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Stmt");
        cJSON_AddItemToObject(yyval, "Exp", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Stmt", yyvsp[0]);
        cJSON_AddStringToObject(yyval, "sub_type", "IfStmt");
    }
#line 1589 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 34: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 306 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Stmt");
        cJSON_AddItemToObject(yyval, "Exp", yyvsp[-4]);
        cJSON_AddItemToObject(yyval, "Stmt", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "ElseStmt", yyvsp[0]);
        cJSON_AddStringToObject(yyval, "sub_type", "IfElseStmt");
    }
#line 1602 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 35: /* Stmt: WHILE LP Exp RP Stmt  */
#line 315 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Stmt");
        cJSON_AddItemToObject(yyval, "Exp", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Stmt", yyvsp[0]);
        cJSON_AddStringToObject(yyval, "sub_type", "WhileStmt");
    }
#line 1614 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 36: /* DefList: Def DefList  */
#line 325 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
        cJSON_AddItemToArray(yyval, yyvsp[-1]);
        for (int i = 0; i < cJSON_GetArraySize(yyvsp[0]); i++) {
            cJSON_AddItemToArray(yyval, cJSON_GetArrayItem(yyvsp[0], i));
        }
    }
#line 1626 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 37: /* DefList: %empty  */
#line 333 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
    }
#line 1634 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 38: /* Def: Specifier DecList SEMI  */
#line 338 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Def");
        cJSON_AddItemToObject(yyval, "Specifier", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "DecList", yyvsp[-1]);
    }
#line 1645 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 39: /* DecList: Dec  */
#line 346 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {   
        yyval = cJSON_CreateArray();
        cJSON_AddItemToArray(yyval, yyvsp[0]);
    }
#line 1654 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 40: /* DecList: Dec COMMA DecList  */
#line 351 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
        cJSON_AddItemToArray(yyval, yyvsp[-2]);
        for (int i = 0; i < cJSON_GetArraySize(yyvsp[0]); i++) {
            cJSON_AddItemToArray(yyval, cJSON_GetArrayItem(yyvsp[0], i));
        }
    }
#line 1666 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 41: /* Dec: VarDec  */
#line 360 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Dec");
        cJSON_AddItemToObject(yyval, "VarDec", yyvsp[0]);
    }
#line 1676 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 42: /* Dec: VarDec ASSIGNOP Exp  */
#line 366 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Dec");
        cJSON_AddItemToObject(yyval, "VarDec", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp", yyvsp[0]);
    }
#line 1687 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 43: /* Exp: Exp ASSIGNOP Exp  */
#line 376 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", "=");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1700 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 44: /* Exp: Exp AND Exp  */
#line 385 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", "&&");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1713 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 45: /* Exp: Exp OR Exp  */
#line 394 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", "||");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1726 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 46: /* Exp: Exp GT Exp  */
#line 403 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", ">");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1739 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 47: /* Exp: Exp LT Exp  */
#line 412 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", "<");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1752 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 48: /* Exp: Exp NE Exp  */
#line 421 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", "!=");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1765 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 49: /* Exp: Exp EQ Exp  */
#line 430 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", "==");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1778 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 50: /* Exp: Exp GE Exp  */
#line 439 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", ">=");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1791 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 51: /* Exp: Exp LE Exp  */
#line 448 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", "<=");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1804 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 52: /* Exp: Exp PLUS Exp  */
#line 457 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", "+");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1817 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 53: /* Exp: Exp MINUS Exp  */
#line 466 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", "-");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1830 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 54: /* Exp: Exp STAR Exp  */
#line 475 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", "*");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1843 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 55: /* Exp: Exp DIV Exp  */
#line 484 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "BinaryExp");
        cJSON_AddStringToObject(yyval, "op", "/");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[0]);
    }
#line 1856 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 56: /* Exp: LP Exp RP  */
#line 493 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = yyvsp[-1];
    }
#line 1864 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 57: /* Exp: MINUS Exp  */
#line 497 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "UnaryExp");
        cJSON_AddStringToObject(yyval, "op", "-");
        cJSON_AddItemToObject(yyval, "Exp", yyvsp[0]);
    }
#line 1876 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 58: /* Exp: NOT Exp  */
#line 505 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "UnaryExp");
        cJSON_AddStringToObject(yyval, "op", "!");
        cJSON_AddItemToObject(yyval, "Exp", yyvsp[0]);
    }
#line 1888 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 59: /* Exp: ID LP Args RP  */
#line 513 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "FuncCall");
        cJSON_AddItemToObject(yyval, "name", yyvsp[-3]);
        cJSON_AddItemToObject(yyval, "Args", yyvsp[-1]);  
    }
#line 1900 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 60: /* Exp: ID LP RP  */
#line 521 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "FuncCall");
        cJSON_AddItemToObject(yyval, "name", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "Args", cJSON_CreateArray());
    }
#line 1912 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 61: /* Exp: Exp LB Exp RB  */
#line 529 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "ArrayExp");
        cJSON_AddItemToObject(yyval, "Exp1", yyvsp[-3]);
        cJSON_AddItemToObject(yyval, "Exp2", yyvsp[-1]);
    }
#line 1924 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 62: /* Exp: Exp DOT ID  */
#line 537 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateObject();
        cJSON_AddStringToObject(yyval, "type", "Exp");
        cJSON_AddStringToObject(yyval, "sub_type", "StructExp");
        cJSON_AddItemToObject(yyval, "Exp", yyvsp[-2]);
        cJSON_AddItemToObject(yyval, "name", yyvsp[0]);
    }
#line 1936 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 63: /* Exp: ID  */
#line 545 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = yyvsp[0];
    }
#line 1944 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 64: /* Exp: NUMBER  */
#line 549 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = yyvsp[0];
    }
#line 1952 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 65: /* Exp: REAL  */
#line 553 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = yyvsp[0];
    }
#line 1960 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 66: /* Args: Exp COMMA Args  */
#line 558 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
        cJSON_AddItemToArray(yyval, yyvsp[-2]);
        for(int i = 0; i < cJSON_GetArraySize(yyvsp[0]); i++)
        {
            cJSON_AddItemToArray(yyval, cJSON_GetArrayItem(yyvsp[0], i));
        }
    }
#line 1973 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;

  case 67: /* Args: Exp  */
#line 567 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"
    {
        yyval = cJSON_CreateArray();
        cJSON_AddItemToArray(yyval, yyvsp[0]);
    }
#line 1982 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"
    break;


#line 1986 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 573 "/com.docker.devenvironments.code/c-compiler/src/parser/yacc.y"



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
