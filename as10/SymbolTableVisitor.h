/*
  Filename   : SymbolTableVisitor.h
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 10, 
  Description: Structure used to traverse C- AST's via Visitor Pattern,
                 building a symbol table and annotating usages
		 (expressions) with corresponding declarations, or
		 returning error information.
*/

#ifndef __C_MINUS_SYMBOL_TABLE_VISITOR_H__
#define __C_MINUS_SYMBOL_TABLE_VISITOR_H__

/********************************************************************/
// System Includes

/********************************************************************/
// Local Includes

#include "CMinusAst.h"
#include "SymbolTable.h"

/********************************************************************/
// Using delcarations


/********************************************************************/
// Class Definition

class SymbolTableVisitor : public IVisitor
{
  int level;
  SymbolTable symbolTable;

public:
  SymbolTableVisitor ();
  ~SymbolTableVisitor ();
  
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
  void visit (AdditiveExpressionNode* node);
  void visit (MultiplicativeExpressionNode* node);
  void visit (RelationalExpressionNode* node);
  void visit (UnaryExpressionNode* node);
  void visit (IntegerLiteralExpressionNode* node);

  void visit (ReferenceNode* node);
  void visit (VariableExpressionNode* node);
  void visit (SubscriptExpressionNode* node);
  void visit (CallExpressionNode* node);
};

#endif
