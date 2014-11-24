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
  // insert stub 'input ()' method into global scope
  vector<ParameterNode*> params;
  FunctionDeclarationNode fInput (ValueType::INT, "input", params, nullptr);
  symbolTable.insert (&fInput);

  // insert stub 'output (int value)' method into global scope
  ParameterNode* pValue = new ParameterNode ("value", false);
  params.push_back (pValue);
  FunctionDeclarationNode fOutput (ValueType::VOID, "output", params, nullptr);
  symbolTable.insert (&fOutput);
}

SemanticAnalysisVisitor::~SemanticAnalysisVisitor () {}

// void
// SemanticAnalysisVisitor::emitMultipleDeclaration (DeclarationNode* node)
// {
//   DeclarationNode* prev = symbolTable.lookup (node->identifier);
  
//   cout << "Error: multiple declarations: "
//        << node->identifier << " at ("
//        << node->rowNumber << ", "
//        << node->columnNumber << ") previously declared at ("
//        << prev->rowNumber << ","
//        << prev->columnNumber << ")\n";

//   errorEmitted = true;
// }

// void
// SemanticAnalysisVisitor::emitUndeclaredReference (ReferenceNode* node)
// {
//   cout << "Error: undeclared reference: "
// 	 << node->identifier << " at ("
// 	 << node->rowNumber << ", "
// 	 << node->columnNumber << ")\n";

//   errorEmitted = true;
// }

/********************************************************************/
// Visit methods

void
SemanticAnalysisVisitor::visit (ProgramNode* node)
{
  for (DeclarationNode* d : node->children)
    d->accept (this);

  node->isValid = !errorEmitted;
}
  
void
SemanticAnalysisVisitor::visit (DeclarationNode* node) {}

void
SemanticAnalysisVisitor::visit (FunctionDeclarationNode* node)
{
  for (ParameterNode* p : node->parameters)
    p->accept (this);

  returnType = node->valueType;
  node->functionBody->accept (this);
}

void
SemanticAnalysisVisitor::visit (VariableDeclarationNode* node) {}

void
SemanticAnalysisVisitor::visit (ArrayDeclarationNode* node) {}

void
SemanticAnalysisVisitor::visit (ParameterNode* node) {}

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
    node->expression->accept (this);
}

void
SemanticAnalysisVisitor::visit (ExpressionStatementNode* node)
{
  if (node->expression != nullptr)
    node->expression->accept (this);
}

void
SemanticAnalysisVisitor::visit (ExpressionNode* node) {}

void
SemanticAnalysisVisitor::visit (AssignmentExpressionNode* node)
{
  node->variable->accept (this);
  node->expression->accept (this);
}

void
SemanticAnalysisVisitor::visit (AdditiveExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);
}

void
SemanticAnalysisVisitor::visit (MultiplicativeExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);
}

void
SemanticAnalysisVisitor::visit (RelationalExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);
}

void
SemanticAnalysisVisitor::visit (UnaryExpressionNode* node)
{
  node->variable->accept (this);
}

void
SemanticAnalysisVisitor::visit (IntegerLiteralExpressionNode* node) {}

void
SemanticAnalysisVisitor::visit (ReferenceNode* node) {}

void
SemanticAnalysisVisitor::visit (VariableExpressionNode* node)
{
  
}

void
SemanticAnalysisVisitor::visit (SubscriptExpressionNode* node)
{
  node->index->accept (this);
}

void
SemanticAnalysisVisitor::visit (CallExpressionNode* node)
{
  for (auto a : node->arguments)
    a->accept (this);
}
