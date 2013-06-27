/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CREATE = 258,
     TABLE = 259,
     INSERT = 260,
     INTO = 261,
     SELECT = 262,
     FROM = 263,
     WHERE = 264,
     PRIMARY = 265,
     FOREIGN = 266,
     KEY = 267,
     DEFAULT = 268,
     CHECK = 269,
     NOT = 270,
     TOKEN_NULL = 271,
     AND = 272,
     OR = 273,
     NEQ = 274,
     GEQ = 275,
     LEQ = 276,
     REFERENCES = 277,
     ORDER = 278,
     BY = 279,
     DELETE = 280,
     AS = 281,
     INT = 282,
     DOUBLE = 283,
     CHAR = 284,
     VARCHAR = 285,
     TEXT = 286,
     USING = 287,
     JOIN = 288,
     INNER = 289,
     OUTER = 290,
     LEFT = 291,
     RIGHT = 292,
     NATURAL = 293,
     UNION = 294,
     VALUES = 295,
     AUTO = 296,
     INCREMENT = 297,
     ASC = 298,
     DESC = 299,
     UNIQUE = 300,
     IN = 301,
     ON = 302,
     COUNT = 303,
     SUM = 304,
     AVG = 305,
     MIN = 306,
     MAX = 307,
     IDENTIFIER = 308,
     STRING_LITERAL = 309,
     DOUBLE_LITERAL = 310,
     INT_LITERAL = 311
   };
#endif
/* Tokens.  */
#define CREATE 258
#define TABLE 259
#define INSERT 260
#define INTO 261
#define SELECT 262
#define FROM 263
#define WHERE 264
#define PRIMARY 265
#define FOREIGN 266
#define KEY 267
#define DEFAULT 268
#define CHECK 269
#define NOT 270
#define TOKEN_NULL 271
#define AND 272
#define OR 273
#define NEQ 274
#define GEQ 275
#define LEQ 276
#define REFERENCES 277
#define ORDER 278
#define BY 279
#define DELETE 280
#define AS 281
#define INT 282
#define DOUBLE 283
#define CHAR 284
#define VARCHAR 285
#define TEXT 286
#define USING 287
#define JOIN 288
#define INNER 289
#define OUTER 290
#define LEFT 291
#define RIGHT 292
#define NATURAL 293
#define UNION 294
#define VALUES 295
#define AUTO 296
#define INCREMENT 297
#define ASC 298
#define DESC 299
#define UNIQUE 300
#define IN 301
#define ON 302
#define COUNT 303
#define SUM 304
#define AVG 305
#define MIN 306
#define MAX 307
#define IDENTIFIER 308
#define STRING_LITERAL 309
#define DOUBLE_LITERAL 310
#define INT_LITERAL 311




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "sql.y"
{
	double dval;
	int ival;
	const char *strval;
}
/* Line 1529 of yacc.c.  */
#line 167 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

