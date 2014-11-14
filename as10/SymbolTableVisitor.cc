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

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

/********************************************************************/
// Class Methods

SymbolTableVisitor::SymbolTableVisitor () {}

SymbolTableVisitor::~SymbolTableVisitor () {
  symbolTable.clear ();
}

void SymbolTableVisitor::visit (ProgramNode* node)
{
  level = 0;
  
  for (DeclarationNode* d : node->children)
    d->accept (this);
}
  
void SymbolTableVisitor::visit (DeclarationNode* node) {}

void SymbolTableVisitor::visit (FunctionDeclarationNode* node)
{
  outFile << indent () << "Function: " << node->identifier << ": ";
  switch (node->valueType)
  {
  case ValueType::INT:
    outFile << "Int type\n";
    break;
  case ValueType::VOID:
    outFile << "Void type\n";
    break;
  case ValueType::ARRAY:
    outFile << "Array type\n";
    break;
  }
  
  ++depth;
  for (ParameterNode* p : node->parameters)
    p->accept (this);

  node->functionBody->accept (this);
  --depth;
}

void SymbolTableVisitor::visit (VariableDeclarationNode* node)
{
  outFile  << indent () << "VariableDeclaration: " << node->identifier << ": ";
  switch (node->valueType)
  {
  case ValueType::INT:
    outFile << "Int type\n";
    break;
  case ValueType::VOID:
    outFile << "Void type\n";
    break;
  case ValueType::ARRAY:
    outFile << "Array type\n";
    break;
  }
}

void SymbolTableVisitor::visit (ArrayDeclarationNode* node)
{
  outFile << indent () << "Variable: " << node->identifier
       << "[" << node->size << "]: ";
  switch (node->valueType)
  {
  case ValueType::INT:
    outFile << "Int type\n";
    break;
  case ValueType::VOID:
    outFile << "Void type\n";
    break;
  case ValueType::ARRAY:
    outFile << "Array type\n";
    break;
  }
  
}

void SymbolTableVisitor::visit (ParameterNode* node)
{
  outFile << indent () << "Parameter: " << node->identifier;
  if (node->isArray)
    outFile << "[]";
  switch (node->valueType)
  {
  case ValueType::INT:
    outFile << ": Int type\n";
    break;
  case ValueType::VOID:
    outFile << ": Void type\n";
    break;
  case ValueType::ARRAY:
    outFile << ": Array type\n";
    break;
  }
}

void SymbolTableVisitor::visit (StatementNode* node)
{
  outFile << indent () << "Statement" << endl;
}

void SymbolTableVisitor::visit (CompoundStatementNode* node)
{
  outFile << indent () << "CompoundStatement" << endl;

  ++depth;
  for (auto l : node->localDeclarations)
    l->accept (this);
  for (auto s : node->statements)
    s->accept (this);
  --depth;
}

void SymbolTableVisitor::visit (IfStatementNode* node)
{
  outFile << indent () << "If\n";

  ++depth;
  node->conditionalExpression->accept (this);
  node->thenStatement->accept (this);
  if (node->elseStatement != nullptr)
    node->elseStatement->accept (this);
  --depth;
}

void SymbolTableVisitor::visit (WhileStatementNode* node)
{
  outFile << indent () << "While\n";

  ++depth;
  node->conditionalExpression->accept (this);
  node->body->accept (this);
  --depth;
}

void SymbolTableVisitor::visit (ForStatementNode* node)
{
  outFile << indent () << "For\n";

  ++depth;
  node->initializer->accept (this);
  node->condition->accept (this);
  node->updater->accept (this);
  node->body->accept (this);
  --depth;
}

void SymbolTableVisitor::visit (ReturnStatementNode* node)
{
  outFile << indent () << "Return\n";

  if (node->expression != nullptr)
  {
    ++depth;
    node->expression->accept (this);
    --depth;
  }
}

void SymbolTableVisitor::visit (ExpressionStatementNode* node)
{
  outFile << indent () << "ExpressionStatement\n";

  if (node->expression != nullptr)
  {
    ++depth;
    node->expression->accept (this);
    --depth;
  }
}

void SymbolTableVisitor::visit (ExpressionNode* node)
{
  outFile << indent () << "Expression" << endl;
}

void SymbolTableVisitor::visit (AssignmentExpressionNode* node)
{
  outFile << indent () << "Assignment\n";

  ++depth;
  node->variable->accept (this);
  node->expression->accept (this);
  --depth;
}

void SymbolTableVisitor::visit (VariableExpressionNode* node)
{
  outFile << indent () << "Variable: " << node->identifier << endl;
}

void SymbolTableVisitor::visit (SubscriptExpressionNode* node)
{
  outFile << indent () << "Subscript: " << node->identifier << endl;

  ++depth;
  outFile << indent () << "Index:\n";
  ++depth;
  node->index->accept (this);
  depth -= 2;
}

void SymbolTableVisitor::visit (CallExpressionNode* node)
{
  outFile << indent () << "FunctionCall: " << node->identifier;

  if (node->arguments.size() > 0)
  {
    ++depth;
    outFile << endl << indent () << "Arguments:\n";
    ++depth;
    for (auto a : node->arguments)
      a->accept (this);
    depth -= 2;
  }
  else
    outFile << "()\n";
}

void SymbolTableVisitor::visit (AdditiveExpressionNode* node)
{
  outFile << indent () << "AdditiveExpression: ";

  switch (node->addOperator)
  {
  case AdditiveOperatorType::PLUS:
    outFile << "+\n";
    break;
  case AdditiveOperatorType::MINUS:
    outFile << "-\n";
    break;
  }

  ++depth;
  outFile << indent () << "Left:\n";
  ++depth;
  node->left->accept (this);
  --depth;
  outFile << indent () << "Right:\n";
  ++depth;
  node->right->accept (this);
  depth -= 2;
}

void SymbolTableVisitor::visit (MultiplicativeExpressionNode* node)
{
  outFile << indent () << "MultiplicativeExpression: ";

  switch (node->multOperator)
  {
  case MultiplicativeOperatorType::TIMES:
    outFile << "*\n";
    break;
  case MultiplicativeOperatorType::DIVIDE:
    outFile << "/\n";
    break;
  }

  ++depth;
  outFile << indent () << "Left:\n";
  ++depth;
  node->left->accept (this);
  --depth;
  outFile << indent () << "Right:\n";
  ++depth;
  node->right->accept (this);
  depth -= 2;
}

void SymbolTableVisitor::visit (RelationalExpressionNode* node)
{
  outFile << indent () << "RelationalExpression: ";

  switch (node->relationalOperator)
  {
  case RelationalOperatorType::EQ:
    outFile << "==\n";
    break;
  case RelationalOperatorType::NEQ:
    outFile << "!=\n";
    break;
  case RelationalOperatorType::LT:
    outFile << "<\n";
    break;
  case RelationalOperatorType::LTE:
    outFile << "<=\n";
    break;
  case RelationalOperatorType::GT:
    outFile << ">\n";
    break;
  case RelationalOperatorType::GTE:
    outFile << ">=\n";
    break;
  }

  ++depth;
  outFile << indent () << "Left:\n";
  ++depth;
  node->left->accept (this);
  --depth;
  outFile << indent () << "Right:\n";
  ++depth;
  node->right->accept (this);
  depth -= 2;
}

void SymbolTableVisitor::visit (UnaryExpressionNode* node)
{
  outFile << indent () << "UnaryExpression: ";

  switch (node->unaryOperator)
  {
  case UnaryOperatorType::INCREMENT:
    outFile << "++\n";
    break;
  case UnaryOperatorType::DECREMENT:
    outFile << "--\n";
    break;
  }

  ++depth;
  node->variable->accept (this);
  --depth;
}

void SymbolTableVisitor::visit (IntegerLiteralExpressionNode* node)
{
  outFile << indent () << "Integer: " << node->value << endl;
}
