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
 
/********************************************************************/
// Local Includes

#include "SymbolTableVisitor.h"

/********************************************************************/
// Using declarations

using std::cout;

/********************************************************************/
// Class Methods

SymbolTableVisitor::SymbolTableVisitor ()
{
  // insert stub 'input ()' method into global scope
  vector<ParameterNode*> params;
  FunctionDeclarationNode fInput (ValueType::INT, "input", params, nullptr);
  symbolTable.insert (&fInput);

  // insert stub 'output (int value)' method into global scope
  ParameterNode* pValue = new ParameterNode (ValueType::INT, "value", false);
  params.push_back (pValue);
  FunctionDeclarationNode fOutput (ValueType::VOID, "output", params, nullptr);
  symbolTable.insert (&fOutput);
}

SymbolTableVisitor::~SymbolTableVisitor () {}

void
SymbolTableVisitor::emitMultipleDeclaration (DeclarationNode* node)
{
  DeclarationNode* prev = symbolTable.lookup (node->identifier);
  
  cout << "Error: multiple declarations: "
       << node->identifier << " at ("
       << node->rowNumber << ", "
       << node->columnNumber << ") previously declared at ("
       << prev->rowNumber << ","
       << prev->columnNumber << ")\n";

  errorEmitted = true;
}

void
SymbolTableVisitor::emitUndeclaredReference (ReferenceNode* node)
{
  cout << "Error: undeclared reference: "
	 << node->identifier << " at ("
	 << node->rowNumber << ", "
	 << node->columnNumber << ")\n";

  errorEmitted = true;
}

/********************************************************************/
// Visit methods

void
SymbolTableVisitor::visit (ProgramNode* node)
{
  for (DeclarationNode* d : node->children)
    d->accept (this);

  node->isValid = !errorEmitted;
}
  
void
SymbolTableVisitor::visit (DeclarationNode* node) {}

void
SymbolTableVisitor::visit (FunctionDeclarationNode* node)
{
  if (!symbolTable.insert (node))
    emitMultipleDeclaration (node);
  
  symbolTable.enterScope ();

  for (ParameterNode* p : node->parameters)
    p->accept (this);

  // set flag so compound statement does not generate new scope
  isFunctionBody = true;
  node->functionBody->accept (this);
  
  symbolTable.exitScope ();
}

void
SymbolTableVisitor::visit (VariableDeclarationNode* node)
{
  if (!symbolTable.insert (node))
    emitMultipleDeclaration (node);
}

void
SymbolTableVisitor::visit (ArrayDeclarationNode* node)
{
  if (!symbolTable.insert (node))
    emitMultipleDeclaration (node);
}

void
SymbolTableVisitor::visit (ParameterNode* node)
{
  if (!symbolTable.insert (node))
    emitMultipleDeclaration (node);
}

void
SymbolTableVisitor::visit (StatementNode* node) {}

void
SymbolTableVisitor::visit (CompoundStatementNode* node)
{
  bool newScope = !isFunctionBody;

  if (newScope)
    symbolTable.enterScope ();

  // nested compound statements can create new scopes
  isFunctionBody = false;
  
  for (auto l : node->localDeclarations)
    l->accept (this);
  for (auto s : node->statements)
    s->accept (this);
  
  if (newScope)
    symbolTable.exitScope ();
}

void
SymbolTableVisitor::visit (IfStatementNode* node)
{
  node->conditionalExpression->accept (this);
  node->thenStatement->accept (this);
  
  if (node->elseStatement != nullptr)
    node->elseStatement->accept (this);
}

void
SymbolTableVisitor::visit (WhileStatementNode* node)
{
  node->conditionalExpression->accept (this);
  node->body->accept (this);
}

void
SymbolTableVisitor::visit (ForStatementNode* node)
{
  node->initializer->accept (this);
  node->condition->accept (this);
  node->updater->accept (this);
  node->body->accept (this);
}

void
SymbolTableVisitor::visit (ReturnStatementNode* node)
{
  if (node->expression != nullptr)
    node->expression->accept (this);
}

void
SymbolTableVisitor::visit (ExpressionStatementNode* node)
{
  if (node->expression != nullptr)
    node->expression->accept (this);
}

void
SymbolTableVisitor::visit (ExpressionNode* node) {}

void
SymbolTableVisitor::visit (AssignmentExpressionNode* node)
{
  node->variable->accept (this);
  node->expression->accept (this);
}

void
SymbolTableVisitor::visit (AdditiveExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);
}

void
SymbolTableVisitor::visit (MultiplicativeExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);
}

void
SymbolTableVisitor::visit (RelationalExpressionNode* node)
{
  node->left->accept (this);
  node->right->accept (this);
}

void
SymbolTableVisitor::visit (UnaryExpressionNode* node)
{
  node->variable->accept (this);
}

void
SymbolTableVisitor::visit (IntegerLiteralExpressionNode* node) {}

void
SymbolTableVisitor::visit (ReferenceNode* node) {}

void
SymbolTableVisitor::visit (VariableExpressionNode* node)
{
  node->declaration = symbolTable.lookup (node->identifier);
  if (node->declaration == nullptr)
    emitUndeclaredReference (node);
}

void
SymbolTableVisitor::visit (SubscriptExpressionNode* node)
{
  node->declaration = symbolTable.lookup (node->identifier);
  if (node->declaration == nullptr)
    emitUndeclaredReference (node);
  
  node->index->accept (this);
}

void
SymbolTableVisitor::visit (CallExpressionNode* node)
{
  node->declaration = symbolTable.lookup (node->identifier);
  if (node->declaration == nullptr)
    emitUndeclaredReference (node);
  
  for (auto a : node->arguments)
    a->accept (this);
}
