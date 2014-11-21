/********************************************************************/
// C- AST Header File
// Header file by Daniel J. Rabiega & Mervin Fansler
// Design by CSCI 435: Compilers class
// Fall 2014

#ifndef __C_Minus_AST_Classes__
#define __C_Minus_AST_Classes__

/********************************************************************/
// System Includes

#include <string>
#include <vector>

/********************************************************************/
// Using Declarations

using std::string;
using std::vector;

/********************************************************************/
// Forward Class Declarations

// Visitor
struct IVisitor;

// Abstract Node
struct Node;

// Root Node
struct ProgramNode;

// Declaration Nodes
struct DeclarationNode;
struct FunctionDeclarationNode;
struct VariableDeclarationNode;
struct ArrayDeclarationNode;
struct ParameterNode;

// Statement Nodes
struct StatementNode;
struct CompoundStatementNode;
struct IfStatementNode;
struct WhileStatementNode;
struct ForStatementNode;
struct ReturnStatementNode;
struct ExpressionStatementNode;

// Expression Nodes
struct ExpressionNode;
struct AssignmentExpressionNode;
struct AdditiveExpressionNode;
struct MultiplicativeExpressionNode;
struct RelationalExpressionNode;
struct UnaryExpressionNode;
struct IntegerLiteralExpressionNode;

// Reference Nodes
struct ReferenceNode;
struct VariableExpressionNode;
struct SubscriptExpressionNode;
struct CallExpressionNode;

/********************************************************************/
//  Enum Classes

enum class AdditiveOperatorType
{
  PLUS, MINUS
};

enum class MultiplicativeOperatorType
{
  TIMES, DIVIDE
};

enum class RelationalOperatorType
{
  LT, LTE, GT, GTE, EQ, NEQ
};

enum class UnaryOperatorType
{
  INCREMENT, DECREMENT
};

enum class ValueType
{
  VOID, INT, ARRAY
};

/********************************************************************/
// Abstract Classes

class IVisitor
{
public:
  virtual void visit (ProgramNode* node) = 0;
  
  virtual void visit (DeclarationNode* node) = 0;
  virtual void visit (FunctionDeclarationNode* node) = 0;
  virtual void visit (VariableDeclarationNode* node) = 0;
  virtual void visit (ArrayDeclarationNode* node) = 0;
  virtual void visit (ParameterNode* node) = 0;

  virtual void visit (StatementNode* node) = 0;
  virtual void visit (CompoundStatementNode* node) = 0;
  virtual void visit (IfStatementNode* node) = 0;
  virtual void visit (WhileStatementNode* node) = 0;
  virtual void visit (ForStatementNode* node) = 0;
  virtual void visit (ReturnStatementNode* node) = 0;
  virtual void visit (ExpressionStatementNode* node) = 0;

  virtual void visit (ExpressionNode* node) = 0;
  virtual void visit (AssignmentExpressionNode* node) = 0;
  virtual void visit (AdditiveExpressionNode* node) = 0;
  virtual void visit (MultiplicativeExpressionNode* node) = 0;
  virtual void visit (RelationalExpressionNode* node) = 0;
  virtual void visit (UnaryExpressionNode* node) = 0;
  virtual void visit (IntegerLiteralExpressionNode* node) = 0;

  virtual void visit (ReferenceNode* node) = 0;
  virtual void visit (VariableExpressionNode* node) = 0;
  virtual void visit (SubscriptExpressionNode* node) = 0;
  virtual void visit (CallExpressionNode* node) = 0;
};

struct Node
{
  Node (int r = 1, int c = 0);
  
  virtual ~Node ();
  
  virtual void
  accept (IVisitor* visitor) = 0;

  int rowNumber;
  int columnNumber;
};

/********************************************************************/
// ROOT NODE CLASS

struct ProgramNode : Node
{
  ProgramNode (vector<DeclarationNode*> children);
  
  ~ProgramNode ();

  void
  accept (IVisitor* visitor);
  
  vector<DeclarationNode*> children;
};

/********************************************************************/
// DECLARATION NODES

struct DeclarationNode : Node
{
  DeclarationNode (ValueType t, string id, int row = 1, int col = 0);
  virtual ~DeclarationNode ();

  virtual void
  accept (IVisitor* visitor) = 0;
  
  ValueType valueType;
  string identifier;

  int nestLevel;
};

struct FunctionDeclarationNode : DeclarationNode
{
  FunctionDeclarationNode (ValueType t, string id,
			   vector<ParameterNode*> params,
			   CompoundStatementNode* csNode,
			   int row = 1, int col = 0);

  ~FunctionDeclarationNode ();

  void
  accept (IVisitor* visitor);
  
  vector<ParameterNode*> parameters;
  CompoundStatementNode* functionBody;
};

struct VariableDeclarationNode : DeclarationNode
{
  VariableDeclarationNode (string id, int row = 1, int col = 0);
  
  ~VariableDeclarationNode ();

  void
  accept (IVisitor* visitor);
};

struct ArrayDeclarationNode : VariableDeclarationNode
{
  ArrayDeclarationNode (string id, size_t size, int row = 1, int col = 0);

  ~ArrayDeclarationNode ();

  void
  accept (IVisitor* visitor);

  size_t size;
};

struct ParameterNode : DeclarationNode
{
  ParameterNode (string id, bool array, int row = 1, int col = 0);
  ~ParameterNode ();

  void
  accept (IVisitor* visitor);

  bool isArray;
};

/********************************************************************/
// STATEMENT NODES

struct StatementNode : Node
{
  StatementNode (int row = 1, int col = 0);
  virtual ~StatementNode ();

  void
  accept (IVisitor* visitor) = 0;
};

struct CompoundStatementNode : StatementNode
{
  CompoundStatementNode (vector<VariableDeclarationNode*> decls,
			 vector<StatementNode*> stmts,
			 int row = 1, int col = 0);
  ~CompoundStatementNode ();

  void
  accept (IVisitor* visitor);
  
  vector<VariableDeclarationNode*> localDeclarations;
  vector<StatementNode*> statements;
};

struct IfStatementNode : StatementNode
{
  IfStatementNode (ExpressionNode* expr,
                   StatementNode* thenStmt,
                   StatementNode* elseStmt = nullptr,
		   int row = 1, int col = 0);
  
  ~IfStatementNode ();

  void
  accept (IVisitor* visitor);
  
  ExpressionNode* conditionalExpression;
  StatementNode* thenStatement;
  StatementNode* elseStatement;
};

struct WhileStatementNode : StatementNode
{
  WhileStatementNode (ExpressionNode* expr, StatementNode* stmt,
		      int row = 1, int col = 0);
  
  ~WhileStatementNode ();

  void
  accept (IVisitor* visitor);
  
  ExpressionNode* conditionalExpression;
  StatementNode* body;
};

struct ForStatementNode : StatementNode
{
  ForStatementNode (ExpressionNode* e1,
                    ExpressionNode* e2,
                    ExpressionNode* e3,
                    StatementNode* s,
		    int row = 1, int col = 0);
  
  ~ForStatementNode ();

  void
  accept (IVisitor* visitor);
  
  ExpressionNode* initializer;
  ExpressionNode* condition;
  ExpressionNode* updater;
  StatementNode*  body;
};

struct ReturnStatementNode : StatementNode
{
  ReturnStatementNode (ExpressionNode* expr = nullptr, int row = 1, int col = 0);
  
  ~ReturnStatementNode ();

  void
  accept (IVisitor* visitor);
  
  ExpressionNode* expression;
};

struct ExpressionStatementNode : StatementNode
{
  ExpressionStatementNode (ExpressionNode* expr, int row = 1, int col = 0);
  ~ExpressionStatementNode ();

  void
  accept (IVisitor* visitor);
  
  ExpressionNode* expression; 
};

/********************************************************************/
// EXPRESSION NODES

struct ExpressionNode : Node
{
  ExpressionNode (int row = 1, int col = 0);
  virtual ~ExpressionNode ();

  void
  accept (IVisitor* visitor) = 0;
};

struct AssignmentExpressionNode : ExpressionNode
{
  AssignmentExpressionNode (VariableExpressionNode* v, ExpressionNode* e,
			    int row = 1, int col = 0);
  
  ~AssignmentExpressionNode ();

  void
  accept (IVisitor* visitor);
  
  VariableExpressionNode* variable;
  ExpressionNode* expression;
};

struct AdditiveExpressionNode : ExpressionNode
{
  AdditiveExpressionNode (AdditiveOperatorType addop,
			  ExpressionNode* l,
			  ExpressionNode* r,
			  int row = 1, int col = 0);
  ~AdditiveExpressionNode ();

  void
  accept (IVisitor* visitor);
  
  AdditiveOperatorType addOperator;
  ExpressionNode* left;
  ExpressionNode* right;
};

struct MultiplicativeExpressionNode : ExpressionNode
{
  MultiplicativeExpressionNode (MultiplicativeOperatorType multop,
				ExpressionNode* l,
				ExpressionNode* r,
				int row = 1, int col = 0);
  ~MultiplicativeExpressionNode ();

  void
  accept (IVisitor* visitor);
  
  MultiplicativeOperatorType multOperator;
  ExpressionNode* left;
  ExpressionNode* right;
};

struct RelationalExpressionNode : ExpressionNode
{
  RelationalExpressionNode (RelationalOperatorType relop,
			    ExpressionNode* l,
			    ExpressionNode* r,
			    int row = 1, int col = 0);
  ~RelationalExpressionNode ();

  void
  accept (IVisitor* visitor);
  
  RelationalOperatorType relationalOperator;
  ExpressionNode* left;
  ExpressionNode* right;
};


struct UnaryExpressionNode : ExpressionNode
{
  UnaryExpressionNode (UnaryOperatorType unop, VariableExpressionNode* v,
		       int row = 1, int col = 0);
  ~UnaryExpressionNode ();

  void
  accept (IVisitor* visitor);
  
  UnaryOperatorType unaryOperator;
  VariableExpressionNode* variable;
};

struct IntegerLiteralExpressionNode : ExpressionNode
{
  IntegerLiteralExpressionNode (int v, int row = 1, int col = 0);
  ~IntegerLiteralExpressionNode ();

  void
  accept (IVisitor* visitor);

  int value;
};

/********************************************************************/
// Reference Nodes

struct ReferenceNode : ExpressionNode
{
  ReferenceNode (string id, int row = 1, int col = 0);
  virtual ~ReferenceNode ();

  void
  accept (IVisitor* visitor) = 0;

  string identifier;
  DeclarationNode* declaration;
};

struct VariableExpressionNode : ReferenceNode
{
  VariableExpressionNode (string id, int row = 1, int col = 0);
  ~VariableExpressionNode ();

  void
  accept (IVisitor* visitor);
};

struct SubscriptExpressionNode : VariableExpressionNode
{
  SubscriptExpressionNode (string id, ExpressionNode* index,
			   int row = 1, int col = 0);
  ~SubscriptExpressionNode ();

  void
  accept (IVisitor* visitor);

  ExpressionNode* index;
};

struct CallExpressionNode : ReferenceNode
{
  CallExpressionNode (string id, vector<ExpressionNode*> args,
		      int row = 1, int col = 0);
  ~CallExpressionNode ();

  void
  accept (IVisitor* visitor);
  
  vector<ExpressionNode*> arguments;
};

#endif
