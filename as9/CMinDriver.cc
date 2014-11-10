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
// Local Includes

#include "CMinusAst.h"
#include "PrintVisitor.h"

/******************************************************************************/
// External references

extern
int
yyparse (ProgramNode* &root);

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

  ProgramNode* root;
  
  int parseResult = yyparse (root);

  if (parseResult == 0)
  {
    PrintVisitor* treePrinter = new PrintVisitor ();
    
    root->accept (treePrinter);
  }
  else
  {
    std::cout << "Program syntax invalid\n";
  }
  
  delete root;
  
  return EXIT_SUCCESS;
}
