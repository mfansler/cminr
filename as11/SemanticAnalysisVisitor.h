/*
  Filename   : SemanticAnalysisVisitor.h
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 11, Semantic Analysis
  Description: Structure used to traverse C- AST's via Visitor Pattern,
                 annotating the tree with type information and carrying
		 out basic semantic analysis.
*/

#ifndef __C_MINUS_SEMANTIC_ANALYSIS_VISITOR_H__
#define __C_MINUS_SEMANTIC_ANALYSIS_VISITOR_H__

/********************************************************************/
// Local Includes

#include "CMinusAst.h"

/********************************************************************/
// Class Definition

class SemanticAnalysisVisitor : public IVisitor
{
  bool errorEmitted = false;
  ValueType returnType;

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
