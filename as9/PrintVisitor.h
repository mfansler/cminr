/*
  Filename   : PrintVisitor.h
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 9, A Happy Little AST
  Description: Implements the IVisitor interface, printing Node information
                 as it traverse the AST's built by the Bison parser.
*/

/********************************************************************/
// System Includes

#include <string>

/********************************************************************/
// Local Includes

#include "CMinusAst.h"

/********************************************************************/
// Class Definition

class PrintVisitor : public IVisitor
{
  int depth;
  
  std::string indent ();

public:
  PrintVisitor ();
  ~PrintVisitor ();
  
  void visit (ProgramNode* node);
  void visit (DeclarationNode* node);
  void visit (StatementNode* node);
  void visit (ExpressionNode* node);
  void visit (ParameterNode* node);

  void visit (FunctionDeclarationNode* node);
  void visit (VariableDeclarationNode* node);
  void visit (ArrayDeclarationNode* node);
};
