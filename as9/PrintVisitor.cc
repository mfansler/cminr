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
  cout << indent () << "Function: " << node->identifier << endl;

  ++depth;
  for (ParameterNode* p : node->parameters)
    p->accept (this);

  node->functionBody->accept (this);
  --depth;
}

void PrintVisitor::visit (VariableDeclarationNode* node)
{
  cout  << indent () << "Variable: " << node->identifier << endl;
}

void PrintVisitor::visit (ArrayDeclarationNode* node)
{
  cout << indent () << "Variable: " << node->identifier
       << "[" << node->size << "]\n";
}

void PrintVisitor::visit (StatementNode* node)
{
  cout << indent () << "Statement" << endl;
}

void PrintVisitor::visit (ExpressionNode* node)
{
  cout << indent () << "Expression" << endl;
}

void PrintVisitor::visit (ParameterNode* node)
{
  cout << indent () << "Parameter: " << node->identifier;
  if (node->isArray)
    cout << "[]";
  cout << endl;
}
