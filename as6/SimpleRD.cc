/* 
 * Filename: SimpleRD.cc
 * Author  : Merv Fansler

  Grammar:
    M -> {S} $
    S -> I | W | A | P | C | G
    I -> '[' E ? {S} : {S} ']' | '[' E ? {S} ']'
    
*/

#include <cstdio>
#include <cstdlib>
#include <cctype>

/****************************************************/

bool
M ();

void
S ();

void
I ();

void
W ();

void
A ();

void
P ();

void
C ();

void
G ();

void
E ();

void
T ();

void
U ();

void
F ();

void
match (char token);

void
error (const char* error);

char
getToken ();

/****************************************************/

char g_token;

/****************************************************/

int
main ()
{
  g_token = getToken ();
  bool result = M ();
  if (g_token != '$')
    error("main");
  else
    {
      printf ("String accepted\n");
    }

  return EXIT_SUCCESS;
}

/****************************************************/

bool
M ()
{
  // to handle production
  // M --> { S } $

  while (g_token != '$')
  {
    S ();
  }
  return true;
}

/****************************************************/

void
S ()
{
  // To handle production
  // S --> I | W | A | P | C | G

  if (g_token == '[')
    {
      I ();
    }
  else if (g_token == '{')
    {
      W ();
    }
  else if (islower (g_token))
    {
      A ();
    }
  else if (g_token == '>')
    {
      G ();
    }
  else
    {
      match ('<');
      // check case C lookaheads
      if (g_token == 'B')
        match ('B');
      else if (g_token == 'T')
        match ('T');
      else if (g_token == 'N')
        match ('N');
      else 
        { // must be case P
          E ();
        }
      match (';');
    }
}

/****************************************************/

void
I ()
{
  // to handle production
  // I -> '[' E ? { S } : { S } ']' | '[' E ? { S } ']'

  match ('[');
  E ();
  match ('?');
  while (g_token != ':' && g_token != ']')
    S ();
  if (g_token == ':')
    {
      match (':');
      while (g_token != ']')
        S ();
      match (']');
    }
  else
    match (']');
}

/****************************************************/

void
W ()
{
  // to handle production
  // W --> '{' E ? { S } '}'

  match ('{');
  E ();
  match ('?');
  while (g_token != '}')
    S ();
  match ('}');
}

/****************************************************/

void
A ()
{
  // to handle production
  // A --> id = E ;

  if (islower (g_token))
    g_token = getToken ();
  else 
    error ("A, missing identifier");

  match ('=');
  E ();
  match (';');
}

/****************************************************/

void
P ()
{
  // to handle production
  // P --> '<' E ;

  match ('<');
  E ();
  match (';');
}

/****************************************************/

void 
C ()
{
  // to handle production
  // C --> '<' ( 'B' | 'T' | 'N' ) ;

  match ('<');
  if (g_token == 'B')
    match ('B');
  else if (g_token == 'T')
    match ('T');
  else if (g_token == 'N')
    match ('N');
  else
    error ("C");

  match (';');
}

/****************************************************/

void
G ()
{
  // to handle production
  // G --> '>' id ;

  match ('>');
  if (islower (g_token))
    g_token = getToken ();
  else
    error ("G, missing identifier");
  match (';');
}

/****************************************************/

void
E ()
{
  // to handle production
  // E --> E + T | E - T | T
  
  T ();
  while (g_token == '+' || g_token == '-')
    {
      g_token = getToken ();
      T ();
    }
}

/****************************************************/

void
T ()
{
  // to handle production
  // T --> T * U | T / U | T % U | U

  U ();
  while (g_token == '*' || g_token == '/' || g_token == '%')
    {
      g_token = getToken ();
      U ();
    }
}

/****************************************************/

void
U ()
{
  // to handle production
  // U -> F ^ U | F

  F ();
  if (g_token == '^')
    {
      match ('^');
      U ();
    }
}

/****************************************************/

void
F ()
{
  // to handle production
  // F --> '(' E ')' | id | num

  if (g_token == '(')
    {
      match ('(');
      E ();
      match (')');
    }
  else if (islower (g_token))
    g_token = getToken ();
  else if (isdigit (g_token))
    g_token = getToken ();
  else
    error ("F");
}

/****************************************************/


void
match (char token)
{
  if (g_token == token)
    g_token = getToken ();
  else
    {
      printf ("Expected %c, found %c\n", token, g_token);
      error ("match");
    }
}

/****************************************************/

void
error (const char* error)
{
  printf ("\n*** ERROR: %s\n", error);
  exit (1);
}

/****************************************************/

char
getToken ()
{
  char ch;
  while (isspace (ch = getchar ()))
    ;

  return ch;
}
