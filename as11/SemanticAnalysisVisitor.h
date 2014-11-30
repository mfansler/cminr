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
// System Includes

#include <string>
#include <map>

/********************************************************************/
// Local Includes

#include "CMinusAst.h"

/********************************************************************/
// Class Definition

class SemanticAnalysisVisitor : public IVisitor
{
  // state variables
  bool errorEmitted = false;
  ValueType expectedReturnType;
  bool returnCalled = false;
  
  std::map<ValueType, std::string> vtString =
    {
      {	ValueType::INT  , "INT"   },
      { ValueType::VOID , "VOID"  },
      { ValueType::ARRAY, "ARRAY" }
    };

  std::map<UnaryOperatorType, std::string> uOpString =
    {
      { UnaryOperatorType::INCREMENT, "++" },
      { UnaryOperatorType::DECREMENT, "--" }
    };

  std::map<AdditiveOperatorType, std::string> aOpString =
    {
      { AdditiveOperatorType::PLUS , "+" },
      { AdditiveOperatorType::MINUS, "-" }
    };

  std::map<MultiplicativeOperatorType, std::string> mOpString =
    {
      { MultiplicativeOperatorType::TIMES , "*" },
      { MultiplicativeOperatorType::DIVIDE, "/" }
    };

  std::map<RelationalOperatorType, std::string> rOpString =
    {
      { RelationalOperatorType::LT , "<"  },
      { RelationalOperatorType::LTE, "<=" },
      { RelationalOperatorType::GT , ">"  },
      { RelationalOperatorType::GTE, ">=" },
      { RelationalOperatorType::EQ , "==" },
      { RelationalOperatorType::NEQ, "!=" }
    };

  bool
  isArray (DeclarationNode* node);
  
  bool
  isFunction (DeclarationNode* node);
  
  // Error emitting methods
  void
  emitUnaryOperationError (UnaryExpressionNode* node);

  void
  emitAssignmentError (AssignmentExpressionNode* node);

  void
  emitAdditiveOperationError (AdditiveExpressionNode* node);

  void
  emitMultiplicativeOperationError (MultiplicativeExpressionNode* node);

  void
  emitRelationalOperationError (RelationalExpressionNode* node);

  void
  emitSubscriptTypeError (SubscriptExpressionNode* node);

  void
  emitSubscriptOperationError (SubscriptExpressionNode* node);

  void
  emitNotAFunctionError (CallExpressionNode* node);

  void
  emitArgumentCountError (CallExpressionNode* node,
			       FunctionDeclarationNode* decl);

  void
  emitArgumentTypeError (CallExpressionNode* node,
			      FunctionDeclarationNode* decl,
			      int index);

  void
  emitVoidError (DeclarationNode* node);

  void
  emitFunctionAsVariableError (VariableExpressionNode* node);

  void
  emitReturnTypeError (Node* node, ValueType foundReturnType);

  void
  emitMainError (DeclarationNode* node);
  
public:
  SemanticAnalysisVisitor ();
  ~SemanticAnalysisVisitor ();
  
  // Visit methods
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
