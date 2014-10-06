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
#include <iomanip>
#include <map>
#include <string>

/******************************************************************************/
// Local Includes

#include "../as4/CMinTokens.h"

/******************************************************************************/
// Namespace declarations

/*using std::cout;
using std::endl;
using std::setw;
*/
/******************************************************************************/
// External references

extern "C"
int
yylex ();

extern FILE* yyin;

extern char* yytext;

/******************************************************************************/
// Function declarations

int
getToken ();

void
error (const char* msg);

void
match (int token);

void
P ();

void
D ();

void
D2 ();

void
U ();

void
P1 ();

void
P2 ();

void
Y ();

void
C ();

void
V ();

void
S ();

void
I ();

void
W ();

void
R ();

void
E ();

void
X ();

void
X2 ();

void
H ();

void
G ();

void
Q ();

void
T ();

void
F ();

void
F2 ();

void
L ();

void
A ();

void
M ();

/******************************************************************************/
// Global vars

int g_token;

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
  P ();
  if (g_token == 0)
    printf ("Successful parse\n");
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
error (const char* msg)
{
  printf ("Error in %s", msg);
  exit (1);
}

/******************************************************************************/

void
match (int expectedToken)
{
  if (g_token == expectedToken)
    g_token = getToken ();
  else
    error ("match");
}

/******************************************************************************/
// P --> { D }

void
P ()
{
  while (g_token != 0)
    D ();
}

/******************************************************************************/
// D --> VOID ID U | INT ID D2

void
D ()
{
  if (g_token == VOID)
  { // must be U (function) declaration
    match (VOID);
    match (ID);
    U ();
  }
  else if (g_token == INT)
  { // could still be U or V
    match (INT);
    match (ID);
    D2 ();
  }
  else
    error ("D: invalid declaration");
}

/******************************************************************************/
// D2 --> U | [ LBRACK NUM RBRACK ] SEMI

void
D2 ()
{
  if (g_token == LPAREN)
  { // must be function declaration
    U ();
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
    error ("D2: invalid declaration");
}

/******************************************************************************/
// U --> LPAREN P RPAREN C

void
U ()
{
  match (LPAREN);
  P1 ();
  match (RPAREN);
  C ();
}

/******************************************************************************/
// P1 --> VOID | P2 { COMMA P2 }

void
P1 ()
{
  if (g_token == VOID)
    match (VOID);
  else if (g_token == INT)
  {
    P2 ();
    while (g_token == COMMA)
    {
      match (COMMA);
      P2 ();
    }
  }
  else
    error ("P1: invalid parameter syntax");
}

/******************************************************************************/
// P2 --> Y ID [ LBRACK RBRACK ]

void
P2 ()
{
  Y ();
  match (ID);
  if (g_token == LBRACK)
  {
    match (LBRACK);
    match (RBRACK);
  }
}

/******************************************************************************/
// Y --> VOID | INT
void
Y ()
{
  if (g_token == VOID)
    match (VOID);
  else if (g_token == INT)
    match (INT);
  else
    error ("Y, type unspecified");
}


/******************************************************************************/
// C --> LBRACE V { S } RBRACE

void
C ()
{
  match (LBRACE);
  V ();
  while (g_token != RBRACE)
    S ();
  match (RBRACE);
}

/******************************************************************************/
// V --> { INT ID [ LBRACK NUM RBRACK ] SEMI }

void
V ()
{
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
// S --> C | I | W | R | E

void
S ()
{
  if (g_token == LBRACE)
    C ();
  else if (g_token == IF)
    I ();
  else if (g_token == WHILE)
    W ();
  else if (g_token == RETURN)
    R ();
  else
    E ();
}

/******************************************************************************/

void
I ()
{
  match (IF);
  match (LPAREN);
  X ();
  match (RPAREN);
  S ();
  if (g_token == ELSE)
  {
    match (ELSE);
    S ();
  }
}

/******************************************************************************/
// W --> WHILE LPAREN X RPAREN S

void
W ()
{
  match (WHILE);
  match (LPAREN);
  X ();
  match (RPAREN);
  S ();
}

/******************************************************************************/
// R --> RETURN [ X ] SEMI

void
R ()
{
  match (RETURN);
  if (g_token != SEMI)
    X ();
  match (SEMI);
}

/******************************************************************************/
// E --> [ X ] SEMI

void
E ()
{
  if (g_token != SEMI)
    X ();
  match (SEMI);
}

/******************************************************************************/
// X --> NUM H | LPAREN X RPAREN H | ID X2

void
X ()
{
  if (g_token == NUM)
  {
    match (NUM);
    H ();
  }
  else if (g_token == LPAREN)
  {
    match (LPAREN);
    X ();
    match (RPAREN);
    H ();
  }
  else if (g_token == ID)
  {
    match (ID);
    X2 ();
  }
  else
    error ("X, invalid expression");
}

/******************************************************************************/
// X2 --> LPAREN G RPAREN H | ASSIGN X | [ LBRACK X RBRACK ] H

void
X2 ()
{
  if (g_token == LPAREN)
  {
    match (LPAREN);
    G ();
    match (RPAREN);
    H ();
  }
  else if (g_token == ASSIGN)
  {
    match (ASSIGN);
    X ();
  }
  else
  {
    if (g_token == LBRACK)
    {
      match (LBRACK);
      X ();
      match (RBRACK);
    }
    H ();
  }
}

/******************************************************************************/
// H --> { M T } { A Q } { L Q }

void
H ()
{
  while (g_token == TIMES || g_token == DIVIDE)
  {
    M ();
    T ();
  }
  while (g_token == PLUS || g_token == MINUS)
  {
    A ();
    Q ();
  }
  while (g_token == LT || g_token == LTE || g_token == EQ ||
	 g_token == GT || g_token == GTE || g_token == NEQ)
  {
    L ();
    Q ();
  }
}

/******************************************************************************/
// G --> [ X { COMMA X } ]

void
G ()
{
  if (g_token == NUM || g_token == LPAREN || g_token == ID)
  {
    X ();
    while (g_token == COMMA)
    {
      match (COMMA);
      X ();
    }
  }
  else if (g_token == RPAREN)
  {
    // empty
  }
  else
    error ("G, argument syntax invalid");
}

/******************************************************************************/
// Q --> T { A Q }

void
Q ()
{
  T ();
  while (g_token == PLUS || g_token == MINUS)
  {
    A ();
    Q ();
  }
}

/******************************************************************************/
// T --> F { M T }

void
T ()
{
  F ();
  while (g_token == TIMES || g_token == DIVIDE)
  {
    M ();
    T ();
  }
}

/******************************************************************************/
// F -> LPAREN X RPAREN | NUM | ID F2

void
F ()
{
  if (g_token == LPAREN)
  {
    match (LPAREN);
    X ();
    match (RPAREN);
  }
  else if (g_token == NUM)
    match (NUM);
  else if (g_token == ID)
  {
    match (ID);
    F2 ();
  }
  else
    error ("F, missing factor");
}

/******************************************************************************/
// F2 --> LPAREN args RPAREN | [ LBRACK X RBRACK ]

void
F2 ()
{
  if (g_token == LPAREN)
  {
    match (LPAREN);
    G ();
    match (RPAREN);
  }
  else if (g_token == LBRACK)
  {
    match (LBRACK);
    X ();
    match (RBRACK);
  }
  // else => empty
}

/******************************************************************************/
// L --> LT | LTE | GT | GTE | EQ | NEQ

void
L ()
{
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
    error ("L, Logical operation missing");
  }
}

/******************************************************************************/
// A --> PLUS | MINUS

void
A ()
{
  if (g_token == PLUS)
    match (PLUS);
  else if (g_token == MINUS)
    match (MINUS);
  else
    error ("A, Additive operator missing");
}

/******************************************************************************/
// M --> TIMES | DIVIDE

void
M ()
{
  if (g_token == TIMES)
    match (TIMES);
  else if (g_token == DIVIDE)
    match (DIVIDE);
  else
    error ("M, Multiplicative operator missing");
}
