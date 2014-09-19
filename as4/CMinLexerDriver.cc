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

extern FILE* yyin;

extern "C"
int
yylex ();

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

  std::cout << IF;

  int result;  // CHECK: Make sure this is correct; maybe retun a
               // freakn' token straight away
  do
  {
    result = yylex ();
    switch (result)
    { // TODO: fill out cases
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
      default:
        printf("Token number %i",result);
    }
    // TODO: figure out how to print the lexeme string and value
  } while (result != 0);

  return EXIT_SUCCESS;
}
