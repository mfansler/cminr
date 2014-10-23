/*
  Filename   : CMinLexerDriver.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 4, Lex Luthor vs C-
  Description: Driver for C- lexer that accepts a C- source input and outputs
                 a list of the resulting tokens
*/

/******************************************************************************/
// System Includes

#include <iostream>
#include <iomanip>
#include <map>
#include <string>

/******************************************************************************/
// Local Includes

/******************************************************************************/
// Namespace declarations

/******************************************************************************/
// External references

extern
int
yyparse ();

/******************************************************************************/

int
main ()
{
  // Uncomment to show parser actions (shifts and reductions)
  //extern int yydebug;
  //yydebug = 1;

  int parseResult = yyparse ();

  if (parseResult == 0)
    std::cout << "program syntax valid";

  return EXIT_SUCCESS;
}
