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
     INCLUDE_MAIN = 258,
     RETURN = 259,
     FLOAT = 260,
     INT = 261,
     STR = 262,
     IF = 263,
     ELSE = 264,
     WHILE = 265,
     CIN = 266,
     COUT = 267,
     ENDL = 268,
     SEMICOLON = 269,
     OPEN_PAREN = 270,
     CLOSE_PAREN = 271,
     OPEN_SQ = 272,
     CLOSE_SQ = 273,
     OPEN_BRACE = 274,
     CLOSE_BRACE = 275,
     SHIFT_LEFT = 276,
     SHIFT_RIGHT = 277,
     PLUS = 278,
     MINUS = 279,
     MULTIPLY = 280,
     DIVIDE = 281,
     MODULO = 282,
     ASSIGN = 283,
     GREATER_EQUAL = 284,
     EQUAL = 285,
     NOT_EQUAL = 286,
     LESS_EQUAL = 287,
     GREATER = 288,
     LESS = 289,
     ID = 290,
     CONST = 291,
     DIGIT_0 = 292,
     DIGIT = 293,
     BINARY_DIGIT = 294,
     OCTAL_DIGIT = 295,
     HEX_DIGIT = 296
   };
#endif
/* Tokens.  */
#define INCLUDE_MAIN 258
#define RETURN 259
#define FLOAT 260
#define INT 261
#define STR 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define CIN 266
#define COUT 267
#define ENDL 268
#define SEMICOLON 269
#define OPEN_PAREN 270
#define CLOSE_PAREN 271
#define OPEN_SQ 272
#define CLOSE_SQ 273
#define OPEN_BRACE 274
#define CLOSE_BRACE 275
#define SHIFT_LEFT 276
#define SHIFT_RIGHT 277
#define PLUS 278
#define MINUS 279
#define MULTIPLY 280
#define DIVIDE 281
#define MODULO 282
#define ASSIGN 283
#define GREATER_EQUAL 284
#define EQUAL 285
#define NOT_EQUAL 286
#define LESS_EQUAL 287
#define GREATER 288
#define LESS 289
#define ID 290
#define CONST 291
#define DIGIT_0 292
#define DIGIT 293
#define BINARY_DIGIT 294
#define OCTAL_DIGIT 295
#define HEX_DIGIT 296




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

