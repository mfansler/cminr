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
F ();

void
S1 ();

void
P1 ();

void
P2 ();

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
// D --> void id F | int id D2

void
D ()
{
  if (g_token == VOID)
  { // must be F declaration
    match (VOID);
    match (ID);
    F ();
  }
  else if (g_token == INT)
  { // could still be F or V
    match (INT);
    match (ID);
    D2 ();
  }
  else
    error ("D: invalid declaration");
}

/******************************************************************************/
// D2 --> F | [ '[' num ']' ] ';'

void
D2 ()
{
  if (g_token == LPAREN)
  { // must be function declaration
    F ();
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
// F --> id lparen P1 rparen S1

void
F ()
{
  match (ID);
  match (LPAREN);
  P1 ();
  match (RPAREN);
  S1 ();
}

/******************************************************************************/
// P1 --> void | P2 { semi P2 }

void
P1 ()
{
  if (g_token == VOID)
    match (VOID);
  else if (g_token == INT)
  {
    P2 ();
    while (g_token == SEMI)
    {
      match (SEMI);
      P2 ();
    }
  }
  else
    error ("P1: invalid parameter syntax");
}

/******************************************************************************/
// P2 --> int id [ lbrack rbrack ]

void
P2 ()
{
  match (INT);
  match (ID);
  if (g_token == LBRACK)
  {
    match (LBRACK);
    match (RBRACK);
  }
}

/******************************************************************************/
// S1 -->

void
S1 ()
{

}
