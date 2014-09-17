/*
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

#include <CMinTokens.hpp>

//**

extern FILE* yyin;

extern "C"
int
yylex ();

//**


int
main (int argc, char* argv[])
{
  ++argv, argc;
  if (argc > 0)
  {
    yyin = fopen (argv[0], "r");
  }
  else
  {
    yyin = stdin;
  }

  TokenType result;  // <- this is totally wrong; probably should be an object
  do
  {
    result = yylex ();
    // TODO: recognize and printout
  } while (result != 0);

  return EXIT_SUCCESS;
}
