/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_ZOMPILER_PARSER_HPP_INCLUDED
# define YY_ZOMPILER_PARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int zompilerdebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TINTEGER = 258,
     TLBRACE = 259,
     TRBRACE = 260,
     TSEMI = 261,
     TLPAREN = 262,
     TRPAREN = 263,
     TLBRACKET = 264,
     TRBRACKET = 265,
     TINCREMENT = 266,
     TDECREMENT = 267,
     TIF = 268,
     TELSE = 269,
     TEQUAL = 270,
     TMAIN = 271,
     TROTATE = 272,
     TFORWARD = 273,
     TATTACK = 274,
     TRANGED_ATTACK = 275,
     TSAVE_LOC = 276,
     TMEMORY = 277,
     TIS_HUMAN = 278,
     TIS_PASSABLE = 279,
     TIS_RANDOM = 280,
     TIS_ZOMBIE = 281
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 16 "zompiler.y"

    Node* node;
	NBlock* block;
	NStatement* statement;
	NNumeric* numeric;
	NBoolean* boolean;
	std::string* string;
	int token;


/* Line 2058 of yacc.c  */
#line 94 "parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE zompilerlval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int zompilerparse (void *YYPARSE_PARAM);
#else
int zompilerparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int zompilerparse (void);
#else
int zompilerparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_ZOMPILER_PARSER_HPP_INCLUDED  */
