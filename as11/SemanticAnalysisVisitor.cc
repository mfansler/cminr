/*
  Filename   : SemanticAnalysisVisitor.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 11, Semantic Analysis  
  Description: Structure used to traverse C- AST's via Visitor Pattern,
                 building a symbol table and annotating usages
		 (expressions) with corresponding declarations, or
		 returning error information.
*/

/********************************************************************/
// System Includes

#include <string>
#include <iostream>
 
/********************************************************************/
// Local Includes

#include "SemanticAnalysisVisitor.h"

/********************************************************************/
// Using declarations

using std::cout;

/********************************************************************/
// Class Methods

SemanticAnalysisVisitor::SemanticAnalysisVisitor () {}

SemanticAnalysisVisitor::~SemanticAnalysisVisitor () {}

/********************************************************************/
// Error printing methods

void
SemanticAnalysisVisitor::emitUnaryOperationError (UnaryExpressionNode* node)
{
  cout << "Error: unary operator "
       << uOpString[node->unaryOperator] << " requires INT variable; found "
       << node->variable->identifier << " of type "
       << vtString[node->variable->evalType] << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitAssignmentError (AssignmentExpressionNode* node)
{
  cout << "Error: invalid assignment of expression of type "
       << vtString[node->expression->evalType] << " to variable of type "
       << vtString[node->variable->evalType] << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitAdditiveOperationError (AdditiveExpressionNode* node)
{
  cout << "Error: invalid additive operation; found "
       << vtString[node->left->evalType] << " "
       << aOpString[node->addOperator] << " "
       << vtString[node->right->evalType] << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitMultiplicativeOperationError (MultiplicativeExpressionNode* node)
{
  cout << "Error: invalid multiplicative operation; found "
       << vtString[node->left->evalType] << " "
       << mOpString[node->multOperator] << " "
       << vtString[node->right->evalType] << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitRelationalOperationError (RelationalExpressionNode* node)
{
  cout << "Error: invalid relational operation; found "
       << vtString[node->left->evalType] << " "
       << rOpString[node->relationalOperator] << " "
       << vtString[node->right->evalType] << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitSubscriptTypeError (SubscriptExpressionNode* node)
{
  cout << "Error: invalid index type: found index type "
       << vtString[node->index->evalType] << " expected type INT at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitSubscriptOperationError (SubscriptExpressionNode* node)
{
  cout << "Error: invalid subscript operation: "
       << node->identifier << " not an array at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitNotAFunctionError (CallExpressionNode* node)
{
  cout << "Error: invalid call operation: "
       << node->identifier << " not a function at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitArgumentCountError (CallExpressionNode* node,
						 FunctionDeclarationNode* decl)
{
  cout << "Error: invalid number of arguments: expected "
       << decl->parameters.size () << " arguments, found "
       << node->arguments.size () << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitArgumentTypeError (CallExpressionNode* node,
						FunctionDeclarationNode* decl,
						int index)
{
  cout << "Error: invalid argument type: expected "
       << vtString[decl->parameters[index]->evalType] << ", found "
       << vtString[node->arguments[index]->evalType] << " at ("
       << node->arguments[index]->rowNumber << ","
       << node->arguments[index]->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitVoidError (DeclarationNode* node)
{
  cout << "Error: variable declared with VOID type at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";
  
  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitFunctionAsVariableError (VariableExpressionNode* node)
{
  cout << "Error: function being used as a variable at ("
       << node->declaration->rowNumber << ","
       << node->declaration->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitReturnTypeError (Node* node,
					      ValueType foundReturnType)
{
  cout << "Error: unexpected return type: expected "
       << vtString[expectedReturnType] << ", but found "
       << vtString[foundReturnType] << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitMainError (DeclarationNode* node)
{
  cout << "Error: main() function not declared as final function ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

/********************************************************************/
// Utilities

// Tests whether a declared variable is an array
bool
SemanticAnalysisVisitor::isArray (ValueType t)
{
  return (t == ValueType::INT_ARRAY ||
	  t == ValueType::VOID_ARRAY);
}

// Tests whether a declaration is a function
bool
SemanticAnalysisVisitor::isFunction (ValueType t)
{
  return (t == ValueType::INT_FUNCTION ||
	  t == ValueType::VOID_FUNCTION);
}

/********************************************************************/
// Visit methods

void
SemanticAnalysisVisitor::visit (ProgramNode* node)
{
  bool foundMain = false;
  bool isLast = true;
  
  for (DeclarationNode* d : node->children)
  {
    d->accept (this);

    if (foundMain && isLast)
    {
      isLast = false;
      emitMainError (d);
    }
    
    if (d->identifier == "main")
      foundMain = true;
  }

  if (!foundMain)
    cout << "Warning: No main() method declared\n";
  
  node->isValid = !errorEmitted;
}
  
void
SemanticAnalysisVisitor::visit (DeclarationNode* node) {}

void
SemanticAnalysisVisitor::visit (FunctionDeclarationNode* node)
{
  switch (node->valueType)
  {
  case ValueType::VOID:
    node->evalType = ValueType::VOID_FUNCTION;
    break;
  case ValueType::INT:
    node->evalType = ValueType::INT_FUNCTION;
    break;
  default:
    node->evalType = node->valueType;
  }
  
  for (ParameterNode* p : node->parameters)
    p->accept (this);
  
  // set state variables
  expectedReturnType = node->valueType;
  returnCalled = false;
  
  node->functionBody->accept (this);
  
  if (!returnCalled && expectedReturnType != ValueType::VOID)
    emitReturnTypeError (node, ValueType::VOID);
}

void
SemanticAnalysisVisitor::visit (VariableDeclarationNode* node)
{
  if (node->valueType == ValueType::VOID)
    emitVoidError (node);
  
  node->evalType = node->valueType;
}

void
SemanticAnalysisVisitor::visit (ArrayDeclarationNode* node)
{
  switch (node->valueType)
  {
  case ValueType::VOID:
    emitVoidError (node);
    node->evalType = ValueType::VOID_ARRAY;
    break;
  case ValueType::INT:
    node->evalType = ValueType::INT_ARRAY;
    break;
  default:
    node->evalType = node->valueType;
  }
}

void
SemanticAnalysisVisitor::visit (ParameterNode* node)
{
  switch (node->valueType)
  {
  case ValueType::VOID:
    emitVoidError (node);
    if (node->isArray)
      node->evalType = ValueType::VOID_ARRAY;
    else
      node->evalType = ValueType::VOID;
    break;
  case ValueType::INT:
    if (node->isArray)
      node->evalType = ValueType::INT_ARRAY;
    else
      node->evalType = ValueType::INT;
    break;
  default:
    node->evalType = node->valueType;
  }
}

void
SemanticAnalysisVisitor::visit (StatementNode* node) {}

void
SemanticAnalysisVisitor::visit (CompoundStatementNode* node)
{ 
  for (auto l : node->localDeclarations)
    l->accept (this);
  for (auto s : node->statements)
    s->accept (this);
}

void
SemanticAnalysisVisitor::visit (IfStatementNode* node)
{
  node->conditionalExpression->accept (this);
  node->thenStatement->accept (this);
  
  if (node->elseStatement != nullptr)
    node->elseStatement->accept (this);
}

void
SemanticAnalysisVisitor::visit (WhileStatementNode* node)
{
  node->conditionalExpression->accept (this);
  node->body->accept (this);
}

void
SemanticAnalysisVisitor::visit (ForStatementNode* node)
{
  node->initializer->accept (this);
  node->condition->accept (this);
  node->updater->accept (this);
  node->body->accept (this);
}

void
SemanticAnalysisVisitor::visit (ReturnStatementNode* node)
{
  if (node->expression != nullptr)
  {
    node->expression->accept (this);

    if (node->expression->evalType != expectedReturnType)
      emitReturnTypeError (node, node->expression->evalType);
  }
  else if (expectedReturnType != ValueType::VOID)
    emitReturnTypeError (node, ValueType::VOID);

  returnCalled = true;
}

void
SemanticAnalysisVisitor::visit (ExpressionStatementNode* node)
{
  if (node->expression != nullptr)
    node->expression->accept (this);
}

/********************************************************************/
// ExpressionNode visit methods

void
SemanticAnalysisVisitor::visit (ExpressionNode* node) {}

void
SemanticAnalysisVisitor::visit (AssignmentExpressionNode* node)
{
  node->variable->accept (this);
  node->expression->accept (this);

  if (node->variable->evalType != ValueType::INT ||
      node->expression->evalType != ValueType::INT)
    emitAssignmentError (node);

  node->evalType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (AdditiveExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);

  if (node->left->evalType != ValueType::INT ||
      node->right->evalType != ValueType::INT)
    emitAdditiveOperationError (node);

  node->evalType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (MultiplicativeExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);

  if (node->left->evalType != ValueType::INT ||
      node->right->evalType != ValueType::INT)
    emitMultiplicativeOperationError (node);

  node->evalType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (RelationalExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);

  if (node->left->evalType != ValueType::INT ||
      node->right->evalType != ValueType::INT)
    emitRelationalOperationError (node);

  node->evalType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (UnaryExpressionNode* node)
{
  node->variable->accept (this);

  if (node->variable->evalType != ValueType::INT)
    emitUnaryOperationError (node);

  node->evalType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (IntegerLiteralExpressionNode* node)
{
  node->evalType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (ReferenceNode* node) {}

void
SemanticAnalysisVisitor::visit (VariableExpressionNode* node)
{
  node->evalType = node->declaration->evalType;

  if (isFunction (node->evalType))
    emitFunctionAsVariableError (node);
}

void
SemanticAnalysisVisitor::visit (SubscriptExpressionNode* node)
{
  if (!isArray (node->declaration->evalType))
    emitSubscriptOperationError (node);

  node->index->accept (this);

  if (node->index->evalType != ValueType::INT)
    emitSubscriptTypeError (node);

  // this evaluates as array element type (valueType)
  node->evalType = node->declaration->valueType;
}

void
SemanticAnalysisVisitor::visit (CallExpressionNode* node)
{
  for (auto a : node->arguments)
    a->accept (this);

  FunctionDeclarationNode* decl =
    dynamic_cast<FunctionDeclarationNode*> (node->declaration);
  
  if (decl == nullptr)
  {
    emitNotAFunctionError (node);
  }
  else
  {
    if (decl->parameters.size () != node->arguments.size ())
    {
      emitArgumentCountError (node, decl);
    }

    int least = std::min(decl->parameters.size (),
			 node->arguments.size ());
    for (int i = 0; i < least; ++i)
    {
      if (decl->parameters[i]->isArray)
      {
	if (!isArray (node->arguments[i]->evalType))
	  emitArgumentTypeError (node, decl, i);
      }
      else if (decl->parameters[i]->evalType != node->arguments[i]->evalType)
      	emitArgumentTypeError (node, decl, i);
    }
  }

  // this evaluates as function return type (valueType)
  node->evalType = node->declaration->valueType;
}
