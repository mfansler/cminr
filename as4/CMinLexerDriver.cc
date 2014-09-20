/*A
  Filename   : CMinLexerDriver.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 4, Lex Luthor vs C-
  Description: Driver for C- lexer that accepts an C- source input and outputs
                 a list of the resulting tokens
*/

// System Includes

#include <iostream>

#include <cstdio>
#include <cstdlib>

// Local Includes

#include "CMinTokens.hpp"

//**

extern "C"
int
yylex ();

extern FILE* yyin;

extern char* yytext;

extern int lineCount;
extern int colCount;

//**

int
main (int argc, char* argv[])
{
  ++argv, --argc;
  if (argc > 0)
  {
    yyin = fopen (argv[0], "r");
  }
  else
  {
    yyin = stdin;
  }

  int result;

  do
  {
    result = yylex ();
    switch (result)
    { // TODO: DISPLAY LEXEMES AND VALUES; FORMAT
      case ERROR:
        printf("TokenError: Unrecognized character sequence");
        break;
      case IF:
        printf("IF\n");
        break;
      case ELSE:
        printf("ELSE\n");
        break;
      case INT:
        printf("INT\n");
        break;
      case VOID:
        printf("VOID\n");
        break;
      case RETURN:
        printf("RETURN\n");
        break;
      case WHILE:
        printf("WHILE\n");
        break;
      case FOR:
        printf("FOR\n");
        break;
      case PLUS:
        printf("PLUS\n");
        break;
      case MINUS:
        printf("MINUS\n");
        break;
      case TIMES:
        printf("TIMES\n");
        break;
      case DIVIDE:
        printf("DIVIDE\n");
        break;
      case LT:
        printf("LT\n");
        break;
      case LTE:
        printf("LTE\n");
        break;
      case GT:
        printf("GT\n");
        break;
      case GTE:
        printf("GTE\n");
        break;
      case EQ:
        printf("EQ\n");
        break;
      case NEQ:
        printf("NEQ\n");
        break;
      case INCREMENT:
        printf("INCREMENT\n");
        break;
      case DECREMENT:
        printf("DECREMENT\n");
        break;
      case ASSIGN:
        printf("ASSIGN\n");
        break;
      case SEMI:
        printf("SEMI\n");
        break;
      case COMMA:
        printf("COMMA\n");
        break;
      case LPAREN:
        printf("LPAREN\n");
        break;
      case RPAREN:
        printf("RPAREN\n");
        break;
      case LBRACK:
        printf("LBRACK\n");
        break;
      case RBRACK:
        printf("RBRACK\n");
        break;
      case LBRACE:
        printf("LBRACE\n");
        break;
      case RBRACE:
        printf("RBRACE\n");
        break;
      case ID:
        printf("ID\n");
        break;
      case NUM:
        printf("NUM\n");
        break;
      default:
        printf("Token number %i",result);
    }
    // TODO: figure out how to print the lexeme string and value
  } while (result != 0);

  return EXIT_SUCCESS;
}
