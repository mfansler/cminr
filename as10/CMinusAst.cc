/*
  Filename   : CMinusAst.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 10
  Description: Implementation of AST classes for C- langauge.
*/

/********************************************************************/
// System Includes

#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>

/********************************************************************/
// Local Includes

#include "CMinusAst.h"

/********************************************************************/
// Using Declarations

using std::string;
using std::vector;

/********************************************************************/
// Node Methods

Node::Node (int r, int c) : rowNumber(r), columnNumber (c) {}

Node::~Node () {}

/********************************************************************/
// ProgramNode Methods

ProgramNode::ProgramNode (vector<DeclarationNode*> children)
{
  this->children = children;
}

ProgramNode::~ProgramNode ()
{
  for (DeclarationNode* d : children)
    delete d;

  children.clear ();
}

void
ProgramNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// DeclarationNode Methods

DeclarationNode::~DeclarationNode () {}

void
DeclarationNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// FunctionDeclarationNode methods

FunctionDeclarationNode::FunctionDeclarationNode (ValueType t,
						  string id,
						  vector <ParameterNode*> params,
						  CompoundStatementNode* csNode)
{
  valueType = t;
  identifier = id;
  parameters = params;
  functionBody = csNode;
}

FunctionDeclarationNode::~FunctionDeclarationNode ()
{
  delete functionBody;
  for (ParameterNode* p : parameters)
    delete p;
  parameters.clear ();
}

void
FunctionDeclarationNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// VariableDeclarationNode methods

VariableDeclarationNode::VariableDeclarationNode (string id)
{
  valueType = ValueType::INT;
  identifier = id;
}

VariableDeclarationNode::~VariableDeclarationNode () {}

void
VariableDeclarationNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// ArrayDeclarationNode methods

ArrayDeclarationNode::ArrayDeclarationNode (string id, size_t size)
  : VariableDeclarationNode (id)
{
  this->size = size;
}

ArrayDeclarationNode::~ArrayDeclarationNode () {}

void
ArrayDeclarationNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// ParameterNode Methods

ParameterNode::ParameterNode (string id, bool array) : DeclarationNode ()
{
  identifier = id;
  isArray = array;
  valueType = ValueType::INT;
}

ParameterNode::~ParameterNode () {}

void
ParameterNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// StatementNode Methods

StatementNode::~StatementNode () {}

void
StatementNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// CompoundStatementNode Methods

CompoundStatementNode::CompoundStatementNode (vector<VariableDeclarationNode*> decls,
					      vector<StatementNode*> stmts)
{
  localDeclarations = decls;
  statements = stmts;
}

CompoundStatementNode::~CompoundStatementNode ()
{
  for (VariableDeclarationNode* v : localDeclarations)
    delete v;
  localDeclarations.clear ();
  
  for (StatementNode* s : statements)
    delete s;
  statements.clear ();
}

void
CompoundStatementNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// IfStatementNode Methods

IfStatementNode::IfStatementNode (ExpressionNode* expr,
				  StatementNode* thenStmt,
				  StatementNode* elseStmt)
{
  conditionalExpression = expr;
  thenStatement = thenStmt;
  elseStatement = elseStmt;
}

IfStatementNode::~IfStatementNode ()
{
  delete conditionalExpression;
  delete thenStatement;
  delete elseStatement;
}

void
IfStatementNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// WhileStatementNode Methods

WhileStatementNode::WhileStatementNode (ExpressionNode* expr,
					StatementNode* stmt)
{
  conditionalExpression = expr;
  body = stmt;
}

WhileStatementNode::~WhileStatementNode ()
{
  delete conditionalExpression;
  delete body;
}

void
WhileStatementNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// ForStatementNode Methods


ForStatementNode::ForStatementNode (ExpressionNode* e1,
				    ExpressionNode* e2,
				    ExpressionNode* e3,
				    StatementNode* s)
{
  initializer = e1;
  condition = e2;
  updater = e3;
  body = s;
}

ForStatementNode::~ForStatementNode ()
{
  delete initializer;
  delete condition;
  delete updater;
  delete body;
}

void
ForStatementNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// ReturnStatementNode Methods

ReturnStatementNode::ReturnStatementNode (ExpressionNode* expr)
{
  expression = expr;
}

ReturnStatementNode::~ReturnStatementNode ()
{
  delete expression;
}

void
ReturnStatementNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// ExpressionStatementNode Methods

ExpressionStatementNode::ExpressionStatementNode (ExpressionNode* expr)
{
  expression = expr;
}

ExpressionStatementNode::~ExpressionStatementNode ()
{
  delete expression;
}

void
ExpressionStatementNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// ExpressionNode Methods

ExpressionNode::~ExpressionNode () {}

void
ExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// AssignmentExpressionNode Methods

AssignmentExpressionNode::AssignmentExpressionNode (VariableExpressionNode* v,
						    ExpressionNode* e)
{
  variable = v;
  expression = e;
}

AssignmentExpressionNode::~AssignmentExpressionNode ()
{
  delete variable;
  delete expression;
}

void
AssignmentExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// AdditiveExpressionNode Methods

AdditiveExpressionNode::AdditiveExpressionNode (AdditiveOperatorType addop,
						ExpressionNode* l,
						ExpressionNode* r)
{
  addOperator = addop;
  left = l;
  right = r;
}

AdditiveExpressionNode::~AdditiveExpressionNode ()
{
  delete left;
  delete right;
}

void
AdditiveExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// MultiplicativeExpressionNode Methods

MultiplicativeExpressionNode::MultiplicativeExpressionNode (MultiplicativeOperatorType multop,
							    ExpressionNode* l,
							    ExpressionNode* r)
{
  multOperator = multop;
  left = l;
  right = r;
}

MultiplicativeExpressionNode::~MultiplicativeExpressionNode ()
{
  delete left;
  delete right;
}

void
MultiplicativeExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// RelationExpressionNode Methods

RelationalExpressionNode::RelationalExpressionNode (RelationalOperatorType relop,
						    ExpressionNode* l,
						    ExpressionNode* r)
{
  relationalOperator = relop;
  left = l;
  right = r;
}

RelationalExpressionNode::~RelationalExpressionNode ()
{
  delete left;
  delete right;
}

void
RelationalExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// UnaryExpressionNode Methods

UnaryExpressionNode::UnaryExpressionNode (UnaryOperatorType unop,
					  VariableExpressionNode* v)
{
  unaryOperator = unop;
  variable = v;
}

UnaryExpressionNode::~UnaryExpressionNode ()
{
  delete variable;
}

void
UnaryExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// IntegerLiteralExpressionNode Methods

IntegerLiteralExpressionNode::IntegerLiteralExpressionNode (int v)
{
  value = v;
}

IntegerLiteralExpressionNode::~IntegerLiteralExpressionNode () {}

void
IntegerLiteralExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// ReferenceNode Methods

ReferenceNode::~ReferenceNode () {
  // deleting reference nodes should not trigger declaration deletion
  // delete declaration;
}

void
ReferenceNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// VariableExpressionNode Methods

VariableExpressionNode::VariableExpressionNode (string id)
{
  identifier = id;
}

VariableExpressionNode::~VariableExpressionNode () {}

void
VariableExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// SubscriptExpressionNode Methods

SubscriptExpressionNode::SubscriptExpressionNode (string id,
						  ExpressionNode* index)
  : VariableExpressionNode (id)
{
  this->index = index;
}

SubscriptExpressionNode::~SubscriptExpressionNode ()
{
  delete index;
}

void
SubscriptExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// CallExpressionNode Methods

CallExpressionNode::CallExpressionNode (string id, vector<ExpressionNode*> args)
{
  identifier = id;
  arguments = args;
}

CallExpressionNode::~CallExpressionNode ()
{
  for (ExpressionNode* e : arguments)
    delete e;
  arguments.clear ();
}

void
CallExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

