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

DeclarationNode::DeclarationNode (ValueType t, string id, int row, int col)
  : Node (row, col)
  , valueType (t)
  , identifier (id)
{}

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
						  CompoundStatementNode* csNode,
						  int row, int col)
  : DeclarationNode (t, id, row, col)
  , parameters (params)
  , functionBody (csNode)
{}

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

VariableDeclarationNode::VariableDeclarationNode (string id, int row, int col)
  : DeclarationNode (ValueType::INT, id, row, col)
{}

VariableDeclarationNode::~VariableDeclarationNode () {}

void
VariableDeclarationNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// ArrayDeclarationNode methods

ArrayDeclarationNode::ArrayDeclarationNode (string id, size_t size,
					    int row, int col)
  : VariableDeclarationNode (id, row, col), size (size)
{}

ArrayDeclarationNode::~ArrayDeclarationNode () {}

void
ArrayDeclarationNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// ParameterNode Methods

ParameterNode::ParameterNode (string id, bool array, int row, int col)
  : DeclarationNode (ValueType::INT, id, row, col), isArray (array)
{}

ParameterNode::~ParameterNode () {}

void
ParameterNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// StatementNode Methods

StatementNode::StatementNode (int row, int col) : Node (row, col) {}

StatementNode::~StatementNode () {}

void
StatementNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// CompoundStatementNode Methods

CompoundStatementNode::CompoundStatementNode (vector<VariableDeclarationNode*> decls,
					      vector<StatementNode*> stmts,
					      int row, int col)
  : StatementNode (row, col), localDeclarations (decls), statements (stmts)
{}

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
				  StatementNode* elseStmt,
				  int row, int col)
  : StatementNode (row, col)
  , conditionalExpression (expr)
  , thenStatement (thenStmt)
  , elseStatement (elseStmt)
{}

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
					StatementNode* stmt,
					int row, int col)
  : StatementNode (row, col)
  , conditionalExpression (expr)
  , body (stmt)
{}

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
				    StatementNode* s,
				    int row, int col)
  : StatementNode (row, col)
  , initializer (e1)
  , condition (e2)
  , updater (e3)
  , body (s)
{}

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

ReturnStatementNode::ReturnStatementNode (ExpressionNode* expr,
					  int row, int col)
  : StatementNode (row, col), expression (expr)
{}

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

ExpressionStatementNode::ExpressionStatementNode (ExpressionNode* expr,
						  int row, int col)
  : StatementNode (row, col), expression (expr)
{}

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

ExpressionNode::ExpressionNode (int row, int col) : Node (row, col) {}

ExpressionNode::~ExpressionNode () {}

void
ExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// AssignmentExpressionNode Methods

AssignmentExpressionNode::AssignmentExpressionNode (VariableExpressionNode* v,
						    ExpressionNode* e,
						    int row, int col)
  : ExpressionNode (row, col), variable (v), expression (e)
{}

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
						ExpressionNode* r,
						int row, int col)
  : ExpressionNode (row, col), addOperator (addop), left (l), right (r)
{}

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
							    ExpressionNode* r,
							    int row, int col)
  : ExpressionNode (row, col), multOperator (multop), left (l), right (r)
{}

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
						    ExpressionNode* r,
						    int row, int col)
  : ExpressionNode (row, col), relationalOperator (relop), left (l), right (r)
{}

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
					  VariableExpressionNode* v,
					  int row, int col)
  : ExpressionNode (row, col), unaryOperator (unop), variable (v)
{}

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

IntegerLiteralExpressionNode::IntegerLiteralExpressionNode (int v, int row, int col)
  : ExpressionNode (row, col), value (v)
{}

IntegerLiteralExpressionNode::~IntegerLiteralExpressionNode () {}

void
IntegerLiteralExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// ReferenceNode Methods

ReferenceNode::ReferenceNode (string id, int row, int col)
  : ExpressionNode (row, col), identifier (id)
{}
    
ReferenceNode::~ReferenceNode () {
  // deleting reference nodes should NOT trigger declaration deletion
  // delete declaration;
}

void
ReferenceNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// VariableExpressionNode Methods

VariableExpressionNode::VariableExpressionNode (string id, int row, int col)
  : ReferenceNode (id, row, col)
{}

VariableExpressionNode::~VariableExpressionNode () {}

void
VariableExpressionNode::accept (IVisitor* visitor)
{
  visitor->visit (this);
}

/********************************************************************/
// SubscriptExpressionNode Methods

SubscriptExpressionNode::SubscriptExpressionNode (string id,
						  ExpressionNode* index,
						  int row, int col)
  : VariableExpressionNode (id, row, col), index (index)
{}

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

CallExpressionNode::CallExpressionNode (string id, vector<ExpressionNode*> args,
					int row, int col)
  : ReferenceNode (id, row, col), arguments (args)
{}

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

