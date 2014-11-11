/*
  Filename   : PrintVisitor.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 9, A Happy Little AST
  Description: Implements the IVisitor interface, printing Node information
                 as it traverse the AST's built by the Bison parser.
*/

/********************************************************************/
// System Includes

#include <string>
#include <iostream>

/********************************************************************/
// Local Includes

#include "PrintVisitor.h"

/********************************************************************/
// Using declarations

using std::cout;
using std::endl;

/********************************************************************/
// Class Methods

PrintVisitor::PrintVisitor () {}
PrintVisitor::~PrintVisitor () {}

std::string PrintVisitor::indent ()
{
  return std::string (depth*2, ' ');
}

void PrintVisitor::visit (ProgramNode* node)
{
  depth = 0;
  cout << "Program Node\n";
  
  ++depth;
  for (DeclarationNode* d : node->children)
    d->accept (this);
  --depth;
}
  
void PrintVisitor::visit (DeclarationNode* node)
{
  cout << indent () << "Declaration: " << node->identifier << endl;
}

void PrintVisitor::visit (FunctionDeclarationNode* node)
{
  cout << indent () << "Function: " << node->identifier << ": ";
  switch (node->valueType)
  {
  case ValueType::INT:
    cout << "Int type\n";
    break;
  case ValueType::VOID:
    cout << "Void type\n";
    break;
  case ValueType::ARRAY:
    cout << "Array type\n";
    break;
  }
  
  ++depth;
  for (ParameterNode* p : node->parameters)
    p->accept (this);

  node->functionBody->accept (this);
  --depth;
}

void PrintVisitor::visit (VariableDeclarationNode* node)
{
  cout  << indent () << "VariableDeclaration: " << node->identifier << ": ";
  switch (node->valueType)
  {
  case ValueType::INT:
    cout << "Int type\n";
    break;
  case ValueType::VOID:
    cout << "Void type\n";
    break;
  case ValueType::ARRAY:
    cout << "Array type\n";
    break;
  }
}

void PrintVisitor::visit (ArrayDeclarationNode* node)
{
  cout << indent () << "Variable: " << node->identifier
       << "[" << node->size << "]: ";
  switch (node->valueType)
  {
  case ValueType::INT:
    cout << "Int type\n";
    break;
  case ValueType::VOID:
    cout << "Void type\n";
    break;
  case ValueType::ARRAY:
    cout << "Array type\n";
    break;
  }
  
}

void PrintVisitor::visit (ParameterNode* node)
{
  cout << indent () << "Parameter: " << node->identifier;
  if (node->isArray)
    cout << "[]";
  switch (node->valueType)
  {
  case ValueType::INT:
    cout << ": Int type\n";
    break;
  case ValueType::VOID:
    cout << ": Void type\n";
    break;
  case ValueType::ARRAY:
    cout << ": Array type\n";
    break;
  }
}

void PrintVisitor::visit (StatementNode* node)
{
  cout << indent () << "Statement" << endl;
}

void PrintVisitor::visit (CompoundStatementNode* node)
{
  cout << indent () << "CompoundStatement" << endl;

  ++depth;
  for (auto l : node->localDeclarations)
    l->accept (this);
  for (auto s : node->statements)
    s->accept (this);
  --depth;
}

void PrintVisitor::visit (IfStatementNode* node)
{
  cout << indent () << "If\n";

  ++depth;
  node->conditionalExpression->accept (this);
  node->thenStatement->accept (this);
  if (node->elseStatement != nullptr)
    node->elseStatement->accept (this);
  --depth;
}

void PrintVisitor::visit (WhileStatementNode* node)
{
  cout << indent () << "While\n";

  ++depth;
  node->conditionalExpression->accept (this);
  node->body->accept (this);
  --depth;
}

void PrintVisitor::visit (ForStatementNode* node)
{
  cout << indent () << "For\n";

  ++depth;
  node->initializer->accept (this);
  node->condition->accept (this);
  node->updater->accept (this);
  node->body->accept (this);
  --depth;
}

void PrintVisitor::visit (ReturnStatementNode* node)
{
  cout << indent () << "Return\n";

  if (node->expression != nullptr)
  {
    ++depth;
    node->expression->accept (this);
    --depth;
  }
}

void PrintVisitor::visit (ExpressionStatementNode* node)
{
  cout << indent () << "ExpressionStatement\n";

  ++depth;
  node->expression->accept (this);
  --depth;
}

void PrintVisitor::visit (ExpressionNode* node)
{
  cout << indent () << "Expression" << endl;
}

void PrintVisitor::visit (AssignmentExpressionNode* node)
{
  cout << indent () << "Assignment\n";

  ++depth;
  node->variable->accept (this);
  node->expression->accept (this);
  --depth;
}

void PrintVisitor::visit (VariableExpressionNode* node)
{
  cout << indent () << "Variable: " << node->identifier << endl;
}

void PrintVisitor::visit (SubscriptExpressionNode* node)
{
  cout << indent () << "Subscript: " << node->identifier << endl;

  ++depth;
  cout << indent () << "Index:\n";
  ++depth;
  node->index->accept (this);
  depth -= 2;
}

void PrintVisitor::visit (CallExpressionNode* node)
{
  cout << indent () << "FunctionCall: " << node->identifier;

  if (node->arguments.size() > 0)
  {
    ++depth;
    cout << endl << indent () << "Arguments:\n";
    ++depth;
    for (auto a : node->arguments)
      a->accept (this);
    depth -= 2;
  }
  else
    cout << "()\n";
}

void PrintVisitor::visit (AdditiveExpressionNode* node)
{
  cout << indent () << "AdditiveExpression: ";

  switch (node->addOperator)
  {
  case AdditiveOperatorType::PLUS:
    cout << "+\n";
    break;
  case AdditiveOperatorType::MINUS:
    cout << "-\n";
    break;
  }

  ++depth;
  cout << indent () << "Left:\n";
  ++depth;
  node->left->accept (this);
  --depth;
  cout << indent () << "Right:\n";
  ++depth;
  node->right->accept (this);
  depth -= 2;
}

void PrintVisitor::visit (MultiplicativeExpressionNode* node)
{
  cout << indent () << "MultiplicativeExpression: ";

  switch (node->multOperator)
  {
  case MultiplicativeOperatorType::TIMES:
    cout << "*\n";
    break;
  case MultiplicativeOperatorType::DIVIDE:
    cout << "/\n";
    break;
  }

  ++depth;
  cout << indent () << "Left:\n";
  ++depth;
  node->left->accept (this);
  --depth;
  cout << indent () << "Right:\n";
  ++depth;
  node->right->accept (this);
  depth -= 2;
}

void PrintVisitor::visit (RelationalExpressionNode* node)
{
  cout << indent () << "RelationalExpression: ";

  switch (node->relationalOperator)
  {
  case RelationalOperatorType::EQ:
    cout << "==\n";
    break;
  case RelationalOperatorType::NEQ:
    cout << "!=\n";
    break;
  case RelationalOperatorType::LT:
    cout << "<\n";
    break;
  case RelationalOperatorType::LTE:
    cout << "<=\n";
    break;
  case RelationalOperatorType::GT:
    cout << ">\n";
    break;
  case RelationalOperatorType::GTE:
    cout << ">=\n";
    break;
  }

  ++depth;
  cout << indent () << "Left:\n";
  ++depth;
  node->left->accept (this);
  --depth;
  cout << indent () << "Right:\n";
  ++depth;
  node->right->accept (this);
  depth -= 2;
}

void PrintVisitor::visit (UnaryExpressionNode* node)
{
  cout << indent () << "UnaryExpression: ";

  switch (node->unaryOperator)
  {
  case UnaryOperatorType::INCREMENT:
    cout << "++\n";
    break;
  case UnaryOperatorType::DECREMENT:
    cout << "--\n";
    break;
  }

  ++depth;
  node->variable->accept (this);
  --depth;
}

void PrintVisitor::visit (IntegerLiteralExpressionNode* node)
{
  cout << indent () << "Integer: " << node->value << endl;
}
