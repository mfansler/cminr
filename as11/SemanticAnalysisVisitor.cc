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

SemanticAnalysisVisitor::SemanticAnalysisVisitor ()
{
  
}

SemanticAnalysisVisitor::~SemanticAnalysisVisitor () {}

/********************************************************************/
// Error printing methods

void
SemanticAnalysisVisitor::emitUnaryOperationError (UnaryExpressionNode* node)
{
  cout << "Error: unary operator "
       << uOpString[node->unaryOperator] << " requires INT variable; found "
       << node->variable->identifier << " of type "
       << vtString[node->variable->valueType] << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitAssignmentError (AssignmentExpressionNode* node)
{
  cout << "Error: invalid assignment of expression of type "
       << vtString[node->expression->valueType] << " to variable of type "
       << vtString[node->variable->valueType] << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitAdditiveOperationError (AdditiveExpressionNode* node)
{
  cout << "Error: invalid additive operation; found "
       << vtString[node->left->valueType] << " "
       << aOpString[node->addOperator] << " "
       << vtString[node->right->valueType] << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitMultiplicativeOperationError (MultiplicativeExpressionNode* node)
{
  cout << "Error: invalid multiplicative operation; found "
       << vtString[node->left->valueType] << " "
       << mOpString[node->multOperator] << " "
       << vtString[node->right->valueType] << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitRelationalOperationError (RelationalExpressionNode* node)
{
  cout << "Error: invalid relational operation; found "
       << vtString[node->left->valueType] << " "
       << rOpString[node->relationalOperator] << " "
       << vtString[node->right->valueType] << " at ("
       << node->rowNumber << ","
       << node->columnNumber << ")\n";

  errorEmitted = true;
}

void
SemanticAnalysisVisitor::emitSubscriptTypeError (SubscriptExpressionNode* node)
{
  cout << "Error: invalid index type: found index type "
       << vtString[node->index->valueType] << " expected type INT at ("
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
  ValueType expected;
  if (decl->parameters[index]->isArray)
    expected = ValueType::ARRAY;
  else
    expected = decl->parameters[index]->valueType;
  
  cout << "Error: invalid argument type: expected "
       << vtString[expected]  << ", found "
       << vtString[node->arguments[index]->valueType] << " at ("
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
SemanticAnalysisVisitor::isArray (DeclarationNode* node)
{
  ParameterNode* p = dynamic_cast<ParameterNode*> (node);
  ArrayDeclarationNode* a = dynamic_cast<ArrayDeclarationNode*> (node);
  return a || (p && p->isArray);
}

// Tests whether a declaration is a function
bool
SemanticAnalysisVisitor::isFunction (DeclarationNode* node)
{
  FunctionDeclarationNode* f =
    dynamic_cast<FunctionDeclarationNode*> (node);
  
  return (f != nullptr);
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
}

void
SemanticAnalysisVisitor::visit (ArrayDeclarationNode* node)
{
  if (node->valueType == ValueType::VOID)
    emitVoidError (node);
}

void
SemanticAnalysisVisitor::visit (ParameterNode* node)
{
  if (node->valueType == ValueType::VOID)
    emitVoidError (node);
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

    if (node->expression->valueType != expectedReturnType)
      emitReturnTypeError (node, node->expression->valueType);
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

  if (node->variable->valueType != ValueType::INT ||
      node->expression->valueType != ValueType::INT)
    emitAssignmentError (node);

  node->valueType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (AdditiveExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);

  if (node->left->valueType != ValueType::INT ||
      node->right->valueType != ValueType::INT)
    emitAdditiveOperationError (node);

  node->valueType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (MultiplicativeExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);

  if (node->left->valueType != ValueType::INT ||
      node->right->valueType != ValueType::INT)
    emitMultiplicativeOperationError (node);

  node->valueType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (RelationalExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);

  if (node->left->valueType != ValueType::INT ||
      node->right->valueType != ValueType::INT)
    emitRelationalOperationError (node);

  node->valueType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (UnaryExpressionNode* node)
{
  node->variable->accept (this);

  if (node->variable->valueType != ValueType::INT)
    emitUnaryOperationError (node);

  node->valueType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (IntegerLiteralExpressionNode* node)
{
  node->valueType = ValueType::INT;
}

void
SemanticAnalysisVisitor::visit (ReferenceNode* node) {}

void
SemanticAnalysisVisitor::visit (VariableExpressionNode* node)
{
  if (isArray (node->declaration))
    node->valueType = ValueType::ARRAY;
  else
    node->valueType = node->declaration->valueType;

  if (isFunction (node->declaration))
    emitFunctionAsVariableError (node);
}

void
SemanticAnalysisVisitor::visit (SubscriptExpressionNode* node)
{
  node->index->accept (this);

  if (!isArray (node->declaration))
    emitSubscriptOperationError (node);

  if (node->index->valueType != ValueType::INT)
    emitSubscriptTypeError (node);

  node->valueType = node->declaration->valueType;
}

void
SemanticAnalysisVisitor::visit (CallExpressionNode* node)
{
  for (auto a : node->arguments)
    a->accept (this);

  FunctionDeclarationNode* decl = dynamic_cast<FunctionDeclarationNode*> (node->declaration);
  
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
	if (node->arguments[i]->valueType != ValueType::ARRAY)
	  emitArgumentTypeError (node, decl, i);
      }
      else if (decl->parameters[i]->valueType != node->arguments[i]->valueType)
      	emitArgumentTypeError (node, decl, i);
    }
  }

  node->valueType = node->declaration->valueType;
}
