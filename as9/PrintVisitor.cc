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
#include <fstream>

/********************************************************************/
// Local Includes

#include "PrintVisitor.h"

/********************************************************************/
// Using declarations

using std::endl;

/********************************************************************/
// Class Methods

PrintVisitor::PrintVisitor (std::string ofname)
{
  outFile.open (ofname);
}

PrintVisitor::~PrintVisitor ()
{
  outFile.close ();
}

std::string PrintVisitor::indent ()
{
  return std::string (depth*2, ' ');
}

void PrintVisitor::visit (ProgramNode* node)
{
  depth = 0;
  outFile << "Program Node\n";
  
  ++depth;
  for (DeclarationNode* d : node->children)
    d->accept (this);
  --depth;
}
  
void PrintVisitor::visit (DeclarationNode* node)
{
  outFile << indent () << "Declaration: " << node->identifier << endl;
}

void PrintVisitor::visit (FunctionDeclarationNode* node)
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

void PrintVisitor::visit (VariableDeclarationNode* node)
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

void PrintVisitor::visit (ArrayDeclarationNode* node)
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

void PrintVisitor::visit (ParameterNode* node)
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

void PrintVisitor::visit (StatementNode* node)
{
  outFile << indent () << "Statement" << endl;
}

void PrintVisitor::visit (CompoundStatementNode* node)
{
  outFile << indent () << "CompoundStatement" << endl;

  ++depth;
  for (auto l : node->localDeclarations)
    l->accept (this);
  for (auto s : node->statements)
    s->accept (this);
  --depth;
}

void PrintVisitor::visit (IfStatementNode* node)
{
  outFile << indent () << "If\n";

  ++depth;
  node->conditionalExpression->accept (this);
  node->thenStatement->accept (this);
  if (node->elseStatement != nullptr)
    node->elseStatement->accept (this);
  --depth;
}

void PrintVisitor::visit (WhileStatementNode* node)
{
  outFile << indent () << "While\n";

  ++depth;
  node->conditionalExpression->accept (this);
  node->body->accept (this);
  --depth;
}

void PrintVisitor::visit (ForStatementNode* node)
{
  outFile << indent () << "For\n";

  ++depth;
  node->initializer->accept (this);
  node->condition->accept (this);
  node->updater->accept (this);
  node->body->accept (this);
  --depth;
}

void PrintVisitor::visit (ReturnStatementNode* node)
{
  outFile << indent () << "Return\n";

  if (node->expression != nullptr)
  {
    ++depth;
    node->expression->accept (this);
    --depth;
  }
}

void PrintVisitor::visit (ExpressionStatementNode* node)
{
  outFile << indent () << "ExpressionStatement\n";

  ++depth;
  node->expression->accept (this);
  --depth;
}

void PrintVisitor::visit (ExpressionNode* node)
{
  outFile << indent () << "Expression" << endl;
}

void PrintVisitor::visit (AssignmentExpressionNode* node)
{
  outFile << indent () << "Assignment\n";

  ++depth;
  node->variable->accept (this);
  node->expression->accept (this);
  --depth;
}

void PrintVisitor::visit (VariableExpressionNode* node)
{
  outFile << indent () << "Variable: " << node->identifier << endl;
}

void PrintVisitor::visit (SubscriptExpressionNode* node)
{
  outFile << indent () << "Subscript: " << node->identifier << endl;

  ++depth;
  outFile << indent () << "Index:\n";
  ++depth;
  node->index->accept (this);
  depth -= 2;
}

void PrintVisitor::visit (CallExpressionNode* node)
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

void PrintVisitor::visit (AdditiveExpressionNode* node)
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

void PrintVisitor::visit (MultiplicativeExpressionNode* node)
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

void PrintVisitor::visit (RelationalExpressionNode* node)
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

void PrintVisitor::visit (UnaryExpressionNode* node)
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

void PrintVisitor::visit (IntegerLiteralExpressionNode* node)
{
  outFile << indent () << "Integer: " << node->value << endl;
}
