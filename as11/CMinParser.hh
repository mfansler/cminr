/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_CMINPARSER_HH_INCLUDED
# define YY_YY_CMINPARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 33 "CMinParser.yy" /* yacc.c:1909  */

  #include "CMinusAst.h"

#line 48 "CMinParser.hh" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ERROR = 258,
    IF = 259,
    ELSE = 260,
    INT = 261,
    VOID = 262,
    RETURN = 263,
    WHILE = 264,
    FOR = 265,
    PLUS = 266,
    MINUS = 267,
    TIMES = 268,
    DIVIDE = 269,
    LT = 270,
    LTE = 271,
    GT = 272,
    GTE = 273,
    EQ = 274,
    NEQ = 275,
    INCREMENT = 276,
    DECREMENT = 277,
    ASSIGN = 278,
    SEMI = 279,
    COMMA = 280,
    LPAREN = 281,
    RPAREN = 282,
    LBRACK = 283,
    RBRACK = 284,
    LBRACE = 285,
    RBRACE = 286,
    ID = 287,
    NUM = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 44 "CMinParser.yy" /* yacc.c:1909  */

  // literals
  char* name;
  int	intValue;

  // symbols
  ValueType		     valType;
  AdditiveOperatorType       addType;
  RelationalOperatorType     relType;
  MultiplicativeOperatorType mulType;

  // node pointers
  Node*			   nodePtr;
  DeclarationNode* 	   declPtr;
  StatementNode*   	   stmtPtr;
  ExpressionNode*	   exprPtr;
  ParameterNode*	   paramPtr;
  VariableDeclarationNode* vardPtr;
  VariableExpressionNode*  varePtr;
  ExpressionStatementNode* exprStmtPtr;
  CompoundStatementNode*   cmpdStmtPtr;
  
  // vector pointers
  vector<DeclarationNode*>*	    declVect;
  vector<VariableDeclarationNode*>* vardVect;
  vector<ExpressionNode*>* 	    exprVect;
  vector<ParameterNode*>* 	    paramVect;
  vector<StatementNode*>* 	    stmtVect;
  

#line 125 "CMinParser.hh" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (ProgramNode* &root);

#endif /* !YY_YY_CMINPARSER_HH_INCLUDED  */
