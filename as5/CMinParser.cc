/*
  Filename   : CMinParser.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 5, C- Parser_1
  Description: Implements predictive recursive descent parsing of C-
                 tokens according to grammar specified in Louden;
*/

/******************************************************************************/
// System Includes

#include <iostream>
#include <map>
#include <string>
#include <functional>

/******************************************************************************/
// Local Includes

#include "CMinTokens.h"

/******************************************************************************/
// External references

extern "C"
int
yylex ();

extern FILE* yyin;

extern int lineCount;
extern int colCount;

/******************************************************************************/
// Function declarations

int
getToken ();

void
error (std::string msg);

std::function<void(int)>
createMatch (std::string callee);

// Non-terminals

void
program ();

void
declaration ();

void
functionOrVariableDeclaration ();

void
functionDeclaration ();

void
parameterList ();

void
parameter ();

void
compoundStatement ();

void
localVariableList ();

void
statement ();

void
ifStatement ();

void
whileStatement ();

void
returnStatement ();

void
expressionStatement ();

void
expression ();

void
functionCallOrVariable ();

void
assignmentOrMathExpression ();

void
mathematicalExpression ();

void
argumentList ();

void
additiveExpression ();

void
term ();

void
factor ();

void
factorFunctionCallOrVariable ();

void
relationalOperator ();

void
additiveOperator ();

void
multiplicativeOperator ();

/******************************************************************************/
// Global vars

int g_token;

std::map<int, std::string> tokenNames = 
  {
    {ERROR, "ERROR"},
    {IF, "IF"},
    {ELSE, "ELSE"},
    {INT, "INT"},
    {VOID, "VOID"},
    {RETURN, "RETURN"},
    {WHILE, "WHILE"},
    { FOR, "FOR"},
    {PLUS, "PLUS"},
    {MINUS, "MINUS"},
    {TIMES, "TIMES"},
    {DIVIDE, "DIVIDE"},
    {LT, "LT"},
    {LTE, "LTE"},
    {GT, "GT"},
    {GTE, "GTE"},
    {EQ, "EQ"},
    {NEQ, "NEQ"},
    {INCREMENT, "INCREMENT"},
    {DECREMENT, "DECREMENT"},
    {ASSIGN, "ASSIGN"},
    {SEMI, "SEMI"},
    {COMMA, "COMMA"},
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {LBRACK, "LBRACK"},
    {RBRACK, "RBRACK"},
    {LBRACE, "LBRACE"},
    {RBRACE, "RBRACE"},
    {ID, "ID"},
    {NUM, "NUM"} 
  };

/******************************************************************************/

int
main (int argc, char* argv[])
{
  ++argv, --argc;
  if (argc > 0)
  {
    yyin = fopen (argv[0], "r");
  }
  else
  {
    yyin = stdin;
  }
  
  g_token = getToken ();
  program ();
  if (g_token == 0)
    std::cout << "Successful parse\n\n";
  else
    error ("main");
  
  return EXIT_SUCCESS;
}

/******************************************************************************/

int
getToken ()
{
  return yylex ();
}

/******************************************************************************/

void
error (std::string msg)
{
  std::cout << "Error in " + msg << std::endl
	    << "Line " << lineCount << ", Column " << colCount
	    << std::endl << std::endl;
  exit (1);
}

/******************************************************************************/

std::function<void(int)>
createMatch (std::string callee)
{
  return [callee] (int expectedToken)
  {
    if (g_token == expectedToken)
      g_token = getToken ();
    else
    {
      std::cout << "Expected " << tokenNames[expectedToken]
		<< ", found " << tokenNames[g_token] << std::endl;
      error (callee);
    }
  };
}

/******************************************************************************/
// program --> { declaration }

void
program ()
{
  while (g_token != 0)
    declaration ();
}

/******************************************************************************/
// declaration --> VOID ID functionDeclaration | INT ID functionOrVariableDeclaration

void
declaration ()
{
  auto match = createMatch ("declaration");
  
  if (g_token == VOID)
  { // must be functionDeclaration (function) declaration
    match (VOID);
    match (ID);
    functionDeclaration ();
  }
  else if (g_token == INT)
  { // could still be functionDeclaration or V
    match (INT);
    match (ID);
    functionOrVariableDeclaration ();
  }
  else
    error ("declaration: invalid declaration");
}

/******************************************************************************/
// functionOrVariableDeclaration --> functionDeclaration | [ LBRACK NUM RBRACK ] SEMI

void
functionOrVariableDeclaration ()
{
  auto match = createMatch ("functionOrVariable");
 
  if (g_token == LPAREN)
  { // must be function declaration
    functionDeclaration ();
  }
  else if (g_token == LBRACK)
  {
    match (LBRACK);
    match (NUM);
    match (RBRACK);
    match (SEMI);
  }
  else if (g_token == SEMI)
  {
    match (SEMI);
  }
  else
    error ("functionOrVariableDeclaration: invalid declaration");
}

/******************************************************************************/
// functionDeclaration --> LPAREN parameterList RPAREN compoundStatement

void
functionDeclaration ()
{
  auto match = createMatch ("functionDeclaration");
 
  match (LPAREN);
  parameterList ();
  match (RPAREN);
  compoundStatement ();
}

/******************************************************************************/
// parameterList --> VOID | parameter { COMMA parameter }

void
parameterList ()
{
  auto match = createMatch ("parameterList");
 
  if (g_token == VOID)
    match (VOID);
  else if (g_token == INT)
  {
    parameter ();
    while (g_token == COMMA)
    {
      match (COMMA);
      parameter ();
    }
  }
  else
    error ("parameterList: invalid parameter syntax");
}

/******************************************************************************/
// parameter --> INT ID [ LBRACK RBRACK ]

void
parameter ()
{
  auto match = createMatch ("parameter");

  match (INT);
  match (ID);
  if (g_token == LBRACK)
  {
    match (LBRACK);
    match (RBRACK);
  }
}

/******************************************************************************/
// compoundStatement --> LBRACE localVariableList { statement } RBRACE

void
compoundStatement ()
{
  auto match = createMatch ("compoundStatement");
 
  match (LBRACE);
  localVariableList ();
  while (g_token != RBRACE)
    statement ();
  match (RBRACE);
}

/******************************************************************************/
// localVariableList --> { INT ID [ LBRACK NUM RBRACK ] SEMI }

void
localVariableList ()
{
  auto match = createMatch ("localVariableList");
 
  while (g_token == INT)
  {
    match (INT);
    match (ID);
    if (g_token == LBRACK)
    {
      match (LBRACK);
      match (NUM);
      match (RBRACK);
    }
    match (SEMI);
  }
}

/******************************************************************************/
// statement --> compoundStatement | ifStatement | whileStatement |
//               returnStatement | expressionStatement

void
statement ()
{
  if (g_token == LBRACE)
    compoundStatement ();
  else if (g_token == IF)
    ifStatement ();
  else if (g_token == WHILE)
    whileStatement ();
  else if (g_token == RETURN)
    returnStatement ();
  else
    expressionStatement ();
}

/******************************************************************************/
// ifStatement --> IF LPAREN expression RPAREN statement [ ELSE statement ]

void
ifStatement ()
{
  auto match = createMatch ("ifStatement");
 
  match (IF);
  match (LPAREN);
  expression ();
  match (RPAREN);
  statement ();
  if (g_token == ELSE)
  {
    match (ELSE);
    statement ();
  }
}

/******************************************************************************/
// whileStatement --> WHILE LPAREN expression RPAREN statement

void
whileStatement ()
{
  auto match = createMatch ("whileStatement");
 
  match (WHILE);
  match (LPAREN);
  expression ();
  match (RPAREN);
  statement ();
}

/******************************************************************************/
// returnStatement --> RETURN [ expression ] SEMI

void
returnStatement ()
{
  auto match = createMatch ("returnStatement");
 
  match (RETURN);
  if (g_token != SEMI)
    expression ();
  match (SEMI);
}

/******************************************************************************/
// expressionStatement --> [ expression ] SEMI

void
expressionStatement ()
{
  auto match = createMatch ("expressionStatement");
  
  if (g_token != SEMI)
    expression ();
  match (SEMI);
}

/******************************************************************************/
// expression --> NUM mathematicalExpression |
//                LPAREN expression RPAREN mathematicalExpression |
//                ID functionCallOrVariable

void
expression ()
{
  auto match = createMatch ("expression");
 
  if (g_token == NUM)
  {
    match (NUM);
    mathematicalExpression ();
  }
  else if (g_token == LPAREN)
  {
    match (LPAREN);
    expression ();
    match (RPAREN);
    mathematicalExpression ();
  }
  else if (g_token == ID)
  {
    match (ID);
    functionCallOrVariable ();
  }
  else
    error ("expression, invalid expression");
}

/******************************************************************************/
// functionCallOrVariable -->
//   LPAREN argumentList RPAREN mathematicalExpression |
//   [ LBRACK expression RBRACK ] assignmentOrMathExpression

void
functionCallOrVariable ()
{
  auto match = createMatch ("functionCallOrVariable");
 
  if (g_token == LPAREN)
  { // function call
    match (LPAREN);
    argumentList ();
    match (RPAREN);
    mathematicalExpression ();
  }
  else
  { // assignment or mathematical expression
    if (g_token == LBRACK)
    { // array
      match (LBRACK);
      expression ();
      match (RBRACK);
    }
    assignmentOrMathExpression ();
  }
}

/******************************************************************************/
// assignmentOrMathExpression --> ASSIGN expression | mathematicalExpression

void
assignmentOrMathExpression ()
{
  auto match = createMatch ("assignmentOrMathExpression");
 
  if (g_token == ASSIGN)
  { // must be assignment 
    match (ASSIGN);
    expression ();
  }
  else // must be math (or epsilon)
    mathematicalExpression ();
}

/******************************************************************************/
// mathematicalExpression --> [ multiplicativeOperator term ]
//                            [ additiveOperator additiveExpression ]
//                            { relationalOperator additiveExpression }

void
mathematicalExpression ()
{
  auto match = createMatch ("mathematicalExpression");
 
  if (g_token == TIMES || g_token == DIVIDE)
  { // found multiplicative expression
    multiplicativeOperator ();
    term ();
  }
  if (g_token == PLUS || g_token == MINUS)
  {
    additiveOperator ();
    additiveExpression ();
  }
  while (g_token == LT || g_token == LTE || g_token == EQ ||
	 g_token == GT || g_token == GTE || g_token == NEQ)
  {
    relationalOperator ();
    additiveExpression ();
  }
}

/******************************************************************************/
// argumentList --> [ expression { COMMA expression } ]

void
argumentList ()
{
  auto match = createMatch ("argumentList");
 
  if (g_token == NUM || g_token == LPAREN || g_token == ID)
  { // found an argument
    expression ();
    while (g_token == COMMA)
    { // and another
      match (COMMA);
      expression ();
    }
  }
  else if (g_token == RPAREN)
  {
    // epsilon
  }
  else
    error ("argumentList, argument syntax invalid");
}

/******************************************************************************/
// additiveExpression --> term { ( PLUS | MINUS ) additiveExpression }

void
additiveExpression ()
{
  auto match = createMatch ("additiveExpression");
 
  term ();
  while (g_token == PLUS || g_token == MINUS)
  { // more expressions
    match (g_token);
    additiveExpression ();
  }
}

/******************************************************************************/
// term --> factor { multiplicativeOperator term }

void
term ()
{
  auto match = createMatch ("term");
  
  factor ();
  while (g_token == TIMES || g_token == DIVIDE)
  { // more terms
    match (g_token);
    term ();
  }
}

/******************************************************************************/
// factor -> LPAREN expression RPAREN | NUM | ID F2

void
factor ()
{
  auto match = createMatch ("factor");
 
  if (g_token == LPAREN)
  {
    match (LPAREN);
    expression ();
    match (RPAREN);
  }
  else if (g_token == NUM)
    match (NUM);
  else if (g_token == ID)
  {
    match (ID);
    factorFunctionCallOrVariable ();
  }
  else
    error ("factor, expected factor");
}

/******************************************************************************/
// factorFunctionCallOrVariable --> LPAREN args RPAREN | [ LBRACK expression RBRACK ]

void
factorFunctionCallOrVariable ()
{
  auto match = createMatch ("factorFunctionCallOrVariable");
 
  if (g_token == LPAREN)
  {
    match (LPAREN);
    argumentList ();
    match (RPAREN);
  }
  else if (g_token == LBRACK)
  {
    match (LBRACK);
    expression ();
    match (RBRACK);
  }
  // else => empty
}

/******************************************************************************/
// relationalOperator --> LT | LTE | GT | GTE | EQ | NEQ

void
relationalOperator ()
{
  auto match = createMatch ("relationalOperator");
 
  switch (g_token)
  {
  case LT:
    match (LT);
    break;
  case LTE:
    match (LTE);
    break;
  case GT:
    match (GT);
    break;
  case GTE:
    match (GTE);
    break;
  case EQ:
    match (EQ);
    break;
  case NEQ:
    match (NEQ);
    break;
  default:
    error ("relationOperator, operator was expected");
  }
}

/******************************************************************************/
// additiveOperator --> PLUS | MINUS

void
additiveOperator ()
{
  auto match = createMatch ("additiveOperator");
 
  if (g_token == PLUS)
    match (PLUS);
  else if (g_token == MINUS)
    match (MINUS);
  else
    error ("additiveOperator, operator was expected");
}

/******************************************************************************/
// multiplicativeOperator --> TIMES | DIVIDE

void
multiplicativeOperator ()
{
  auto match = createMatch ("multiplicativeOperator");
 
  if (g_token == TIMES)
    match (TIMES);
  else if (g_token == DIVIDE)
    match (DIVIDE);
  else
    error ("multiplicativeOperator, operator was expected");
}
