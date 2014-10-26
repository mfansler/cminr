#include <string>

using std::string;

// Root Node
class ProgramNode;

// Declaration Nodes
class FunctionDeclarationNode;
class VariableDeclarationNode;

// Statement Nodes
class CompoundStatementNode;
class IfStatementNode;
class WhileStatementNode;
class ForStatementNode;
class ReturnStatementNode;

// Expression Nodes
class AssignmentExpressionNode;
class VariableExpressionNode;
class CallExpressionNode;
class BinaryOperatorExpressionNode;
class UnaryOperatorExpressionNode;
class ConstantExpressionNode;

// Other
class ParameterNode;

struct IVisitor
{
	virtual void visit (ProgramNode* node) = 0;
	virtual void visit (DeclarationNode* node) = 0;
	virtual void visit (ExpressionNode* node) = 0;
	virtual void visit (FunctionParameterNode* node) = 0;
};

struct Node
{
  virtual ~Node ();
	
	virtual void
	accept (IVisitor* visitor) = 0;
};

struct ProgramNode : Node
{
	ProgramNode (DeclarationNode* node);
	
	virtual ~ProgramNode ();
	
	vector<DeclarationNode*> children;
};

/******************************************************************************/
// DECLARATION NODES

struct DeclarationNode : Node
{
	virtual ~DeclarationNode ();
	
	string identifier;
};

struct FunctionDeclarationNode : DeclaratonNode
{
	FunctionDeclarationNode (string t, string id,
		vector<ParameterNode*> params, CompoundStatementNode* csNode);

	virtual ~FunctionDeclarationNode ();
	
	string returnType;
	vector<ParameterNode*> parameters;
	CompoundStatementNode* functionBody;
};

struct VariableDeclarationNode : DeclarationNode
{
	VariableDeclarationNode (string id, int size = 0);
	
	virtual ~VariableDeclarationNode ();
	
	int arraySize = 0;
};

/******************************************************************************/
// STATEMENT NODES

struct StatementNode : Node
{
	virtual ~StatementNode ();
};

struct CompoundStatementNode : StatementNode
{
	CompoundStatementNode ();
	virtual ~CompoundStatementNode ();
	
	vector<VariableDeclarationNode*> localDeclarations;
	vector<StatementNode*> statements;
};

struct IfStatementNode : StatementNode
{
	IfStatementNode (ExpressionNode* expr, StatementNode* thenStmt, StatementNode* elseStmt = nullptr);
	
	virtual ~IfStatementNode ();
	
	ExpressionNode* conditionalExpression;
	StatementNode* thenStatement;
	StatementNode* elseStatement;
};

struct WhileStatementNode : StatementNode
{
	WhileStatementNode (ExpressionNode* expr, StatementNode* stmt);
	
	virtual ~WhileStatementNode ();
	
	ExpressionNode* conditionalExpression;
	StatementNode* body;
};

struct ForStatementNode : StatementNode
{
	ForStatementNode (ExpressionNode* e1, ExpressionNode* e2, ExpressionNode* e3, StatementNode* s);
	
	virtual ~ForStatementNode ();
	
	ExpressionNode* expression1;
	ExpressionNode* expression2;
	ExpressionNode* expression3;
	StatementNode* body;
	
};

struct ReturnStatementNode : StatementNode
{
  ReturnStatementNode (ExpressionNode* expr = nullptr);
	
	virtual ~ReturnStatementNode ();
	
	ExpressionNode* expression;
};

/******************************************************************************/
// EXPRESSION NODES

struct ExpressionNode : Node
{
  virtual ~ExpressionNode ();
};

struct AssignmentExpressionNode : ExpressionNode
{
	AssignmentExpressionNode (VariableExpressionNode* v, ExpressionNode* e);
	
	virtual ~AssignmentExpressionNode ();
	
	VariableExpressionNode* variable;
	ExpressionNode* expression;
};

struct VariableExpressionNode : ExpressionNode
{
	VariableExpressionNode (string id, int i = -1);
	virtual ~VariableExpressionNode ();
	
	string identifier;
	int index;
};

struct CallExpressionNode : ExpressionNode
{
	CallExpressionNode (string id, vector<ExpressionNode*> args = NULL);
	virtual ~CallExpressionNode ();
	
	string identifier;
	vector<ExpressionNode*> arguments;
};

struct BinaryOperatorExpressionNode : ExpressionNode
{
	BinaryOperatorExpressionNode (CMinTokenType op, ExpressionNode* l, ExpressionNode* r);
	
	CMinTokenType operation;
	ExpressionNode* left;
	ExpressionNode* right;
};

struct UnaryOperatorExpressionNode : ExpressionNode
{
	UnaryOperatorExpressionNode (bool incr, VariableExpressionNode* v);
	
	bool isIncrement;
	VariableExpressionNode* variable;
};

struct ConstantExpressionNode : ExpressionNode
{
	ConstantExpressionNode (int v);
	
	int value;
};

// Other
struct ParameterNode : Node
{
	ParameterNode (string id, bool array);
	
	string identifier;
	bool isArray;
};