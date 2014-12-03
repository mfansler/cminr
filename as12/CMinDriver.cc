/*
  Filename   : CMinDriver.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 12, Code Generation 
  Description: Compiles C- source (.cm) to an executable format.
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
#include "CodeGeneratorVisitor.h"

/******************************************************************************/
// Using Declarations

using std::cout;
using std::endl;
using std::string;

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
  string fileNameBase;
  
  ++argv, --argc;
  if (argc > 0)
  {
    yyin = fopen (argv[0], "r");

    fileNameBase = string (argv[0]);
    fileNameBase.erase (fileNameBase.end () - 3, fileNameBase.end ());
  }
  else
  {
    yyin = stdin;

    fileNameBase = "Default";
  }
  
  ProgramNode* root = nullptr;
  int parseResult = yyparse (root);

  if (parseResult == 0)
  {
    cout << "Program syntax valid\n";

    SymbolTableVisitor stv;
    root->accept (&stv);

    if (root->isValid)
    {
      SemanticAnalysisVisitor sAnalyzer;
      root->accept (&sAnalyzer);

      if (root->isValid)
      {
	cout << "Program semantics valid\n";

	std::ofstream outFile;

	// Printing Tree
	outFile.open (fileNameBase + ".ast");

	cout << "Writing tree to: " << fileNameBase << ".ast\n";

	PrintVisitor treePrinter (outFile);
	root->accept (&treePrinter);

	outFile.close ();

	// Writing Assembly
	outFile.open (fileNameBase + ".s");

	cout << "Writing assembly to: " << fileNameBase << ".s\n";

	CodeGeneratorVisitor cgv (outFile);
	root->accept (&cgv);
	
	outFile.close ();

	// Linking Assembly
	cout << "Writing executable to: " << fileNameBase << endl;

	string gccCall = "gcc -m32 " + fileNameBase + ".s " + "-o " + fileNameBase;
	int result = system (gccCall.data ());

	if (result == -1)
	  cout << "Error occurred while attempting to build executable!\n";
	else
	  cout << "Success (perhaps)!\n";
      }
      else
      {
	cout << "Program semantics invalid\n";
      }
    }
  }
  else
  {
    cout << "Program syntax invalid\n";
  }
  
  delete root;
  
  return EXIT_SUCCESS;
}
