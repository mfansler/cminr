/*
  A simple Lisp parser

  E -> A     | L
  A -> DIGIT | ALPHA
  L -> ( S )

  S  -> E S'
  S' -> E S' | e
  
  Original rule for S:
     S -> S E   | E
  Could rewrite using EBNF, but here we rewrite using
     right recursion to show how to handle an epsilon rule

*/

/*********************************************************************/
// System includes

#include <iostream>
#include <string>

#include <cctype>

/*********************************************************************/
// Local includes


/*********************************************************************/
// Using declarations

/*********************************************************************/
// Function prototypes/global vars/typedefs

void E  ();
void A  ();
void L  ();
void S  ();
void Sp ();

void
match (char expectedToken);

char
getToken ();

void
error (const char* error);

// Next token 
char g_token;	

/*********************************************************************/

int
main ()
{
  g_token = getToken ();
  E ();
  if (g_token == '$')
    printf ("Successful parse\n");
  else
    error ("main");

  return EXIT_SUCCESS;
}

/*********************************************************************/
//  E -> A     | L
//  A -> DIGIT | ALPHA

void
E ()
{
  if (isdigit (g_token) || isalpha (g_token))
    match (g_token);
  else if (g_token == '(')
    L ();
  else 
    error ("E");
}

/*********************************************************************/
//  L -> ( S )

void
L ()
{
  if (g_token == '(')
  {
    match ('(');
    S ();
    match (')');
  }
  else
    error ("L");
}

/*********************************************************************/
//  S  -> E S'

void
S ()
{
  if (isdigit (g_token) || isalpha (g_token) || g_token == '(')
  {
    E ();
    Sp ();
  }
  else 
    error ("S");
}

/*********************************************************************/
//  S' -> E S' | e

void
Sp ()
{
  if (isdigit (g_token) || isalpha (g_token) || g_token == '(')
  {
    E ();
    Sp ();
  }
  else if (g_token == ')')
  {
    // e
  }
  else
    error ("Sp");
}

/*********************************************************************/

void
match (char expectedToken)
{
  if (g_token == expectedToken)
    g_token = getToken ();
  else
    error ("match");
}

/*********************************************************************/
// Fetch next token (here just a char)

char
getToken ()
{
  char ch;
  while (isspace (ch = getchar ()))
    ;

  return ch;
}

/*********************************************************************/

void
error (const char* error)
{
  fprintf (stderr, "Error in %s\n", error);
  fprintf (stderr, "  token = %c\n", g_token);
  exit (-1);
}
