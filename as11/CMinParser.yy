/*
  Filename   : CMinParser.yy
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 11, Semantic Analyzer
  Description: Bison-based implementation of C- parser, building AST's
*/

%{
  // Prologue section

  #include "CMinusAst.h"
  
  extern "C"
  int
  yylex ();

  extern int lineCount;
  extern int colCount;

  void
  yyerror (ProgramNode* &root, const char*);
%}

/** Declarations **/ 

%code requires
{
  #include "CMinusAst.h"
}

%parse-param
{
  ProgramNode* &root
}

// YYSTYPE
%union
{
  // literals
  char* name;
  int	intValue;

  // symbols
  ValueType		     valType;
  AdditiveOperatorType       addType;
  RelationalOperatorType     relType;
  MultiplicativeOperatorType mulType;

  // node pointers
  Node*			   nodePtr;
  DeclarationNode* 	   declPtr;
  StatementNode*   	   stmtPtr;
  ExpressionNode*	   exprPtr;
  ParameterNode*	   paramPtr;
  VariableDeclarationNode* vardPtr;
  VariableExpressionNode*  varePtr;
  ExpressionStatementNode* exprStmtPtr;
  CompoundStatementNode*   cmpdStmtPtr;
  
  // vector pointers
  vector<DeclarationNode*>*	    declVect;
  vector<VariableDeclarationNode*>* vardVect;
  vector<ExpressionNode*>* 	    exprVect;
  vector<ParameterNode*>* 	    paramVect;
  vector<StatementNode*>* 	    stmtVect;
  
}
  

/* Declare tokens, with precedence and assoc. if necessary */
%token ERROR
%token IF ELSE INT VOID RETURN WHILE FOR
%token PLUS MINUS TIMES DIVIDE
%token LT LTE GT GTE EQ NEQ
%token INCREMENT DECREMENT ASSIGN
%token SEMI COMMA LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE
%token<name> ID
%token<intValue> NUM

/***********************************************************************/
// Declare Non-terminal value types

%type<nodePtr>     program
%type<declPtr>     declaration fun-declaration
%type<declVect>    declaration-list
%type<vardPtr>	   var-declaration
%type<vardVect>	   local-declarations
%type<stmtPtr>     selection-stmt iteration-stmt for-stmt return-stmt statement
%type<stmtVect>    statement-list
%type<exprStmtPtr> expression-stmt
%type<cmpdStmtPtr> compound-stmt
%type<exprPtr>     expression simple-expression additive-expression term factor call
%type<varePtr>	   var
%type<exprVect>    arg-list args
%type<paramPtr>    param
%type<paramVect>   params param-list
%type<valType>     type-specifier
%type<relType>     relop
%type<addType>     addop
%type<mulType>     mulop

// Explicitly resolve dangling ELSE
%right RPAREN ELSE

// Include found / expected tokens in error message
%define parse.error verbose

/* Declare non-terminals if necessary */

/* Declare start symbol */
%start program

%%

/* Grammar rules */

program
	: declaration-list
	{
	  root = new ProgramNode (*$1);
	}
	;

declaration-list
	: declaration-list declaration
	{
	  $$ = $1;
	  $$->push_back ($2);
	}
	| declaration
	{
	  $$ = new vector<DeclarationNode*> ();
	  $$->push_back ($1);
	}
	;

declaration
	: var-declaration
	{
	  $$ = $1;
	}
	| fun-declaration
	{
	  $$ = $1;
	}
	;

var-declaration
	: type-specifier ID SEMI
	{
	  $$ = new VariableDeclarationNode ($1, $2, lineCount, colCount);
	  free ($2);
	}
	| type-specifier ID LBRACK NUM RBRACK SEMI
	{
	  $$ = new ArrayDeclarationNode ($1, $2, $4, lineCount, colCount);
	  free ($2);
	}
	;

type-specifier
	: INT
	{
	  $$ = ValueType::INT;
	}
	| VOID
	{
	  $$ = ValueType::VOID;
	}
	;

fun-declaration
	: type-specifier ID LPAREN params RPAREN compound-stmt
	{
	  $$ = new FunctionDeclarationNode ($1, $2, *$4, $6, lineCount, colCount);
	  free ($2);
	}
	;

params
	: param-list
	{
	  $$ = $1;
	}
	| VOID
	{
	  $$ = new vector<ParameterNode*> ();
	}
	;

param-list
	: param-list COMMA param
	{
	  $$ = $1;
	  $$->push_back ($3);
	}
	| param
	{
	  $$ = new vector<ParameterNode*> ();
	  $$->push_back ($1);
	}
	;

param
	: type-specifier ID
	{
	  $$ = new ParameterNode ($1, $2, false, lineCount, colCount);
	  free ($2);
	}
	| type-specifier ID LBRACK RBRACK
	{
	  $$ = new ParameterNode ($1, $2, true, lineCount, colCount);
	  free ($2);
	}
	;

compound-stmt
	: LBRACE local-declarations statement-list RBRACE
	{
	  $$ = new CompoundStatementNode (*$2, *$3, lineCount, colCount);
	}
	;

local-declarations
	: local-declarations var-declaration
	{
	  $$ = $1;
	  $$->push_back ($2);
	}
	| %empty
	{
	  $$ = new vector<VariableDeclarationNode*> ();
	}
	;

statement-list
	: statement-list statement
	{
	  $$ = $1;
	  $$->push_back ($2);
	}
	| %empty
	{
	  $$ = new vector<StatementNode*> ();
	}
	;

statement
	: expression-stmt
	{
	  $$ = $1;
	}
	| compound-stmt
	{
	  $$ = $1;
	}
	| selection-stmt
	{
	  $$ = $1;
	}
	| iteration-stmt
	{
	  $$ = $1;
	}
	| for-stmt
	{
	  $$ = $1;
	}
	| return-stmt
	{
	  $$ = $1;
	}
	;

expression-stmt
	: expression SEMI
	{
	  $$ = new ExpressionStatementNode ($1, lineCount, colCount);
	}
	| SEMI
	{
	  $$ = new ExpressionStatementNode (nullptr, lineCount, colCount);
	}
	;

selection-stmt
	: IF LPAREN expression RPAREN statement
	{
	  $$ = new IfStatementNode ($3, $5, nullptr, lineCount, colCount);
	}
	| IF LPAREN expression RPAREN statement ELSE statement
	{
	  $$ = new IfStatementNode ($3, $5, $7, lineCount, colCount);
	}
	;

iteration-stmt
	: WHILE LPAREN expression RPAREN statement
	{
	  $$ = new WhileStatementNode ($3, $5, lineCount, colCount);
	}
	;

for-stmt
	: FOR LPAREN expression-stmt expression-stmt expression RPAREN statement
	{
	  $$ = new ForStatementNode ($3->expression, $4->expression, $5, $7, lineCount, colCount);
	}
	| FOR LPAREN expression-stmt expression-stmt RPAREN statement
	{
	  $$ = new ForStatementNode ($3->expression, $4->expression, nullptr, $6, lineCount, colCount); 
	}
	;

return-stmt
	: RETURN SEMI
	{
	  $$ = new ReturnStatementNode (nullptr, lineCount, colCount);
	}
	| RETURN expression SEMI
	{
	  $$ = new ReturnStatementNode ($2, lineCount, colCount);
	}
	;

expression
	: var ASSIGN expression
	{
	  $$ = new AssignmentExpressionNode ($1, $3, lineCount, colCount);
	}
	| simple-expression
	{
	  $$ = $1;
	}
	;

var
	: ID
	{
	  $$ = new VariableExpressionNode ($1, lineCount, colCount);
	  free ($1);
	}
	| ID LBRACK expression RBRACK
	{
	  $$ = new SubscriptExpressionNode ($1, $3, lineCount, colCount);
	  free ($1);
	}
	;

simple-expression
	: additive-expression relop additive-expression
	{
	  $$ = new RelationalExpressionNode ($2, $1, $3, lineCount, colCount);
	}
	| additive-expression
	{
	  $$ = $1;
	}
	;

relop
	: LTE
	{
	  $$ = RelationalOperatorType::LTE;
	}
	| LT
	{
	  $$ = RelationalOperatorType::LT;
	}
	| GT
	{
	  $$ = RelationalOperatorType::GT;
	}
	| GTE
	{
	  $$ = RelationalOperatorType::GTE;
	}
	| EQ
	{
	  $$ = RelationalOperatorType::EQ;
	}
	| NEQ
	{
	  $$ = RelationalOperatorType::NEQ;
	}
	;

additive-expression
	: additive-expression addop term
	{
	  $$ = new AdditiveExpressionNode ($2, $1, $3, lineCount, colCount);
	}
	| term
	{
	  $$ = $1;
	}
	;

addop
	: PLUS
	{
	  $$ = AdditiveOperatorType::PLUS;
	}
	| MINUS
	{
	  $$ = AdditiveOperatorType::MINUS;
	}
	;

term
	: term mulop factor
	{
	  $$ = new MultiplicativeExpressionNode ($2, $1, $3, lineCount, colCount);
	}
	| factor
	{
	  $$ = $1;
	}
	;

mulop
	: TIMES
	{
	  $$ = MultiplicativeOperatorType::TIMES;
	}
	| DIVIDE
	{
	  $$ = MultiplicativeOperatorType::DIVIDE;
	}
	;

factor
	: LPAREN expression RPAREN
	{
	  $$ = $2;
	}
	| var
	{
	  $$ = $1;
	}
	| call
	{
	  $$ = $1;
	}
	| INCREMENT var
	{
	  $$ = new UnaryExpressionNode (UnaryOperatorType::INCREMENT, $2, lineCount, colCount);
	}
	| DECREMENT var
	{
	  $$ = new UnaryExpressionNode (UnaryOperatorType::DECREMENT, $2, lineCount, colCount);
	}
	| NUM
	{
	  $$ = new IntegerLiteralExpressionNode ($1, lineCount, colCount);
	}
	;

call
	: ID LPAREN args RPAREN
	{
	  $$ = new CallExpressionNode ($1, *$3, lineCount, colCount);
	  free ($1);
	}
	;

args
	: arg-list
	{
	  $$ = $1;
	}
	| %empty
	{
	  $$ = new vector<ExpressionNode*> ();
	}
	;

arg-list
	: arg-list COMMA expression
	{
	  $$ = $1;
	  $$->push_back ($3);
	}
	| expression
	{
	  $$ = new vector<ExpressionNode*> ();
	  $$->push_back ($1);
	}
	;

%%

/*********************************************************************/
// Epilogue

void
yyerror (ProgramNode* &root, const char* s)
{
  fprintf (stderr, "%s\nLine %d, Column %d\n", s, lineCount, colCount);
}

