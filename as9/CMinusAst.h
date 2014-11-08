/********************************************************************/
// C- AST Header File
// Header file by Daniel J. Rabiega & Mervin Fansler
// Design by CSCI 435: Compilers class
// Fall 2014

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
struct VariableExpressionNode;
struct SubscriptExpressionNode;
struct CallExpressionNode;
struct AdditiveExpressionNode;
struct MultiplicativeExpressionNode;
struct RelationalExpressionNode;
struct UnaryExpressionNode;
struct IntegerLiteralExpressionNode;

// Other
struct ParameterNode;

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
  virtual void visit (StatementNode* node) = 0;
  virtual void visit (ExpressionNode* node) = 0;
  virtual void visit (ParameterNode* node) = 0;
};

struct Node
{
  virtual ~Node ();
  
  virtual void
  accept (IVisitor* visitor) = 0;
};

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
  virtual ~DeclarationNode ();

  void
  accept (IVisitor* visitor);
  
  ValueType valueType;
  string identifier;
};

struct FunctionDeclarationNode : DeclarationNode
{
  FunctionDeclarationNode (ValueType t, string id,
    vector<ParameterNode*> params, CompoundStatementNode* csNode);

  ~FunctionDeclarationNode ();
  
  ValueType returnType;
  vector<ParameterNode*> parameters;
  CompoundStatementNode* functionBody;
};

struct VariableDeclarationNode : DeclarationNode
{
  VariableDeclarationNode (string id);
  
  ~VariableDeclarationNode ();
};

struct ArrayDeclarationNode : VariableDeclarationNode
{
  ArrayDeclarationNode (string id, size_t size);

  ~ArrayDeclarationNode ();

  size_t size;
};

struct ParameterNode : DeclarationNode
{
  ParameterNode (string id, bool array);
  ~ParameterNode ();

  bool isArray;
};

/********************************************************************/
// STATEMENT NODES

struct StatementNode : Node
{
  virtual ~StatementNode ();

  void
  accept (IVisitor* visitor);
};

struct CompoundStatementNode : StatementNode
{
  CompoundStatementNode (vector<VariableDeclarationNode*> decls,
			 vector<StatementNode*> stmts);
  ~CompoundStatementNode ();
  
  vector<VariableDeclarationNode*> localDeclarations;
  vector<StatementNode*> statements;
};

struct IfStatementNode : StatementNode
{
  IfStatementNode (ExpressionNode* expr,
                   StatementNode* thenStmt,
                   StatementNode* elseStmt = nullptr);
  
  ~IfStatementNode ();
  
  ExpressionNode* conditionalExpression;
  StatementNode* thenStatement;
  StatementNode* elseStatement;
};

struct WhileStatementNode : StatementNode
{
  WhileStatementNode (ExpressionNode* expr, StatementNode* stmt);
  
  ~WhileStatementNode ();
  
  ExpressionNode* conditionalExpression;
  StatementNode* body;
};

struct ForStatementNode : StatementNode
{
  ForStatementNode (ExpressionNode* e1,
                    ExpressionNode* e2,
                    ExpressionNode* e3,
                    StatementNode* s);
  
  ~ForStatementNode ();
  
  ExpressionNode* initializer;
  ExpressionNode* condition;
  ExpressionNode* updater;
  StatementNode*  body;
};

struct ReturnStatementNode : StatementNode
{
  ReturnStatementNode (ExpressionNode* expr = nullptr);
  
  ~ReturnStatementNode ();
  
  ExpressionNode* expression;
};

struct ExpressionStatementNode : StatementNode
{
  ExpressionStatementNode (ExpressionNode* expr);
  ~ExpressionStatementNode ();
  
  ExpressionNode* expression; 
};

/********************************************************************/
// EXPRESSION NODES

struct ExpressionNode : Node
{
  virtual ~ExpressionNode ();

  void
  accept (IVisitor* visitor);
};

struct AssignmentExpressionNode : ExpressionNode
{
  AssignmentExpressionNode (VariableExpressionNode* v, ExpressionNode* e);
  
  ~AssignmentExpressionNode ();
  
  VariableExpressionNode* variable;
  ExpressionNode* expression;
};

struct VariableExpressionNode : ExpressionNode
{
  VariableExpressionNode (string id);
  ~VariableExpressionNode ();
  
  string identifier;
};

struct SubscriptExpressionNode : VariableExpressionNode
{
  SubscriptExpressionNode (string id, ExpressionNode* index);
  ~SubscriptExpressionNode ();

  ExpressionNode* index;
};

struct CallExpressionNode : ExpressionNode
{
  CallExpressionNode (string id, vector<ExpressionNode*> args);
  ~CallExpressionNode ();
  
  string identifier;
  vector<ExpressionNode*> arguments;
};

struct AdditiveExpressionNode : ExpressionNode
{
  AdditiveExpressionNode (AdditiveOperatorType addop,
			  ExpressionNode* l,
			  ExpressionNode* r);
  ~AdditiveExpressionNode ();
  
  AdditiveOperatorType addOperator;
  ExpressionNode* left;
  ExpressionNode* right;
};

struct MultiplicativeExpressionNode : ExpressionNode
{
  MultiplicativeExpressionNode (MultiplicativeOperatorType multop,
                                        ExpressionNode* l,
                                        ExpressionNode* r);
  ~MultiplicativeExpressionNode ();
  
  MultiplicativeOperatorType multOperator;
  ExpressionNode* left;
  ExpressionNode* right;
};

struct RelationalExpressionNode : ExpressionNode
{
  RelationalExpressionNode (RelationalOperatorType relop,
			    ExpressionNode* l,
			    ExpressionNode* r);
  ~RelationalExpressionNode ();
  
  RelationalOperatorType relationalOperator;
  ExpressionNode* left;
  ExpressionNode* right;
};


struct UnaryExpressionNode : ExpressionNode
{
  UnaryExpressionNode (UnaryOperatorType unop,
		       VariableExpressionNode* v);
  ~UnaryExpressionNode ();
  
  UnaryOperatorType unaryOperator;
  VariableExpressionNode* variable;
};

struct IntegerLiteralExpressionNode : ExpressionNode
{
  IntegerLiteralExpressionNode (int v);
  ~IntegerLiteralExpressionNode ();

  int value;
};
