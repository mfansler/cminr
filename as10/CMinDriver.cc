/*
  Filename   : CMinDriver.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 10, 
  Description: Driver for C- parser that accepts a C- source input, builds an AST,
                 builds a symbol table, and performs declaration and type checking.
*/

/******************************************************************************/
// System Includes

#include <iostream>
#include <string>

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
  std::string outFileName;
  
  ++argv, --argc;
  if (argc > 0)
  {
    yyin = fopen (argv[0], "r");
    
    outFileName = std::string(argv[0]);
    outFileName = outFileName.replace(outFileName.end()-2, outFileName.end(), "ast");
  }
  else
  {
    yyin = stdin;
    outFileName = "Default.ast";
  }
  
  // Uncomment to show parser actions (shifts and reductions)
  //extern int yydebug;
  //yydebug = 1;

  ProgramNode* root = nullptr;
  
  int parseResult = yyparse (root);

  if (parseResult == 0)
  {
    std::cout << "Program syntax valid\n"
	      << "Writing tree to: " << outFileName << std::endl;
    
    PrintVisitor* treePrinter = new PrintVisitor (outFileName);
    root->accept (treePrinter);
  }
  else
  {
    std::cout << "Program syntax invalid\n";
  }
  
  delete root;
  
  return EXIT_SUCCESS;
}
