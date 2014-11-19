/*
  Filename   : SymbolTableVisitor.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 10,  
  Description: Structure used to traverse C- AST's via Visitor Pattern,
                 building a symbol table and annotating usages
		 (expressions) with corresponding declarations, or
		 returning error information.
*/

/********************************************************************/
// System Includes

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

/********************************************************************/
// Local Includes

#include "SymbolTableVisitor.h"

/********************************************************************/
// Using declarations


/********************************************************************/
// Class Methods

SymbolTableVisitor::SymbolTableVisitor () {}

SymbolTableVisitor::~SymbolTableVisitor () {
  symbolTable.clear ();
}

void SymbolTableVisitor::visit (ProgramNode* node)
{
  for (DeclarationNode* d : node->children)
    d->accept (this);
}
  
void SymbolTableVisitor::visit (DeclarationNode* node) {}

void SymbolTableVisitor::visit (FunctionDeclarationNode* node)
{
  if (!symbolTable.insert (node))
  {
    cout << "Multiple declaration error: "
	 << node->identifier << " at ("
	 << node->rowNumber << ", "
	 << node->columnNumber << ") previously declared\n";
  }
  
  symbolTable.enterScope ();

  for (ParameterNode* p : node->parameters)
    p->accept (this);

  inFunctionBody = true;
  node->functionBody->accept (this);
  inFunctionBody = false;

  symbolTable.exitScope ();
}

void SymbolTableVisitor::visit (VariableDeclarationNode* node)
{
  if (!symbolTable.insert (node))
  {
    cout << "Multiple declaration error: "
	 << node->identifier << " at ("
	 << node->rowNumber << ", "
	 << node->columnNumber << ") previously declared\n";
  }
}

void SymbolTableVisitor::visit (ArrayDeclarationNode* node)
{
  if (!symbolTable.insert (node))
  {
    cout << "Multiple declaration error: "
	 << node->identifier << " at ("
	 << node->rowNumber << ", "
	 << node->columnNumber << ") previously declared\n";
  }
}

void SymbolTableVisitor::visit (ParameterNode* node)
{
  if (!symbolTable.insert (node))
  {
    cout << "Multiple declaration error: "
	 << node->identifier << " at ("
	 << node->rowNumber << ", "
	 << node->columnNumber << ") previously declared\n";
  }
}

void SymbolTableVisitor::visit (StatementNode* node) {}

void SymbolTableVisitor::visit (CompoundStatementNode* node)
{
  if (!isFunctionBody)
    symbolTable.enterScope ();
  
  for (auto l : node->localDeclarations)
    l->accept (this);
  for (auto s : node->statements)
    s->accept (this);
  
  if (!isFunctionBody)
    symbolTable.exitScope ();
}

void SymbolTableVisitor::visit (IfStatementNode* node)
{
  node->conditionalExpression->accept (this);
  node->thenStatement->accept (this);
  
  if (node->elseStatement != nullptr)
    node->elseStatement->accept (this);
}

void SymbolTableVisitor::visit (WhileStatementNode* node)
{
  node->conditionalExpression->accept (this);
  node->body->accept (this);
}

void SymbolTableVisitor::visit (ForStatementNode* node)
{
  node->initializer->accept (this);
  node->condition->accept (this);
  node->updater->accept (this);
  node->body->accept (this);
}

void SymbolTableVisitor::visit (ReturnStatementNode* node)
{
  if (node->expression != nullptr)
    node->expression->accept (this);
}

void SymbolTableVisitor::visit (ExpressionStatementNode* node)
{
  if (node->expression != nullptr)
    node->expression->accept (this);
}

void SymbolTableVisitor::visit (ExpressionNode* node) {}

void SymbolTableVisitor::visit (AssignmentExpressionNode* node)
{
  node->variable->accept (this);
  node->expression->accept (this);
}

void SymbolTableVisitor::visit (VariableExpressionNode* node)
{
  node->declaration = symbolTable.lookup (node->identifier);
  if (node->declaration == nullptr)
  {
    cout << "Undeclared reference error: "
	 << node->identifier << " at ("
	 << node->rowNumber << ", "
	 << node->columnNumber << ")\n";
  }
}

void SymbolTableVisitor::visit (SubscriptExpressionNode* node)
{
  node->index->accept (this);
}

void SymbolTableVisitor::visit (CallExpressionNode* node)
{
  node->declaration = symbolTable.lookup (node->identifier);
  if (node->declaration == nullptr)
  {
    cout << "Error: Call to undeclared function: "
	 << node->identifier << " at ("
	 << node->rowNumber << ", "
	 << node->columnNumber << ")\n";
  }
  
  for (auto a : node->arguments)
    a->accept (this);
}

void SymbolTableVisitor::visit (AdditiveExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);
}

void SymbolTableVisitor::visit (MultiplicativeExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);
}

void SymbolTableVisitor::visit (RelationalExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);
}

void SymbolTableVisitor::visit (UnaryExpressionNode* node)
{
  node->variable->accept (this);
}

void SymbolTableVisitor::visit (IntegerLiteralExpressionNode* node) {}
