/*
  Filename   : CMinDriver.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 11, Semantic Analysis 
  Description: Driver for C- parser that accepts a C- source input, builds an AST,
                 builds a symbol table, and performs declaration and type checking.
		 If all is valid, ASTs are printed to file "*.ast".
*/

/******************************************************************************/
// System Includes

#include <iostream>
#include <string>

/******************************************************************************/
// Local Includes

#include "CMinusAst.h"
#include "SymbolTableVisitor.h"
#include "SemanticAnalysisVisitor.h"
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

    outFileName = std::string (argv[0]);
    outFileName = outFileName.replace (outFileName.end () - 2, outFileName.end (), "ast");
  }
  else
  {
    yyin = stdin;

    outFileName = "Default.ast";
  }
  
  ProgramNode* root = nullptr;
  int parseResult = yyparse (root);

  if (parseResult == 0)
  {
    std::cout << "Program syntax valid\n";

    SymbolTableVisitor stv;
    root->accept (&stv);

    if (root->isValid)
    {
      SemanticAnalysisVisitor sAnalyzer;
      root->accept (&sAnalyzer);

      if (root->isValid)
      {
	std::cout << "Program semantics valid\n";

	std::ofstream outFile;
	outFile.open (outFileName);

	std::cout << "Writing tree to: " << outFileName << std::endl;

	PrintVisitor treePrinter (outFile);
	root->accept (&treePrinter);

	outFile.close ();
      }
      else
      {
	std::cout << "Program semantics invalid\n";
      }
    }
  }
  else
  {
    std::cout << "Program syntax invalid\n";
  }
  
  delete root;
  
  return EXIT_SUCCESS;
}
