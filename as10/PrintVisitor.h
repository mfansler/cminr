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
#include <fstream>

/********************************************************************/
// Local Includes

#include "CMinusAst.h"

/********************************************************************/
// Class Definition

class PrintVisitor : public IVisitor
{
  int depth;
  std::ofstream outFile;
  
  std::string indent ();

public:
  PrintVisitor (std::string ofname);
  ~PrintVisitor ();
  
  void visit (ProgramNode* node);

  void visit (DeclarationNode* node);
  void visit (FunctionDeclarationNode* node);
  void visit (VariableDeclarationNode* node);
  void visit (ArrayDeclarationNode* node);
  void visit (ParameterNode* node);

  void visit (StatementNode* node);
  void visit (CompoundStatementNode* node);
  void visit (IfStatementNode* node);
  void visit (WhileStatementNode* node);
  void visit (ForStatementNode* node);
  void visit (ReturnStatementNode* node);
  void visit (ExpressionStatementNode* node);

  void visit (ExpressionNode* node);
  void visit (AssignmentExpressionNode* node);
  void visit (VariableExpressionNode* node);
  void visit (SubscriptExpressionNode* node);
  void visit (CallExpressionNode* node);
  void visit (AdditiveExpressionNode* node);
  void visit (MultiplicativeExpressionNode* node);
  void visit (RelationalExpressionNode* node);
  void visit (UnaryExpressionNode* node);
  void visit (IntegerLiteralExpressionNode* node);  
};
