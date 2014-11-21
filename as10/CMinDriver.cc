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
#include "SymbolTableVisitor.h"

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
    yyin = fopen (argv[0], "r");
  else
    yyin = stdin;
  
  ProgramNode* root = nullptr;
  
  int parseResult = yyparse (root);

  if (parseResult == 0)
  {
    std::cout << "Program syntax valid\n";

    SymbolTableVisitor stv;
    root->accept (&stv);
  }
  else
  {
    std::cout << "Program syntax invalid\n";
  }
  
  delete root;
  
  return EXIT_SUCCESS;
}
