/*
  Filename   : CMinDriver.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 8, C- Parser_2
  Description: Driver for C- parser that accepts a C- source input and outputs
                 confirmation of syntactic validity or location or syntax error
*/

/******************************************************************************/
// System Includes

#include <iostream>

/******************************************************************************/
// External references

extern
int
yyparse ();

extern FILE* yyin;

/******************************************************************************/

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
  
  // Uncomment to show parser actions (shifts and reductions)
  //extern int yydebug;
  //yydebug = 1;

  int parseResult = yyparse ();

  if (parseResult == 0)
    std::cout << "program syntax valid\n";

  return EXIT_SUCCESS;
}
