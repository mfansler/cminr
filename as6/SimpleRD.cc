/* 
  Filename   : SimpleRD.cc
  Author     : Merv Fansler
  Course     : CSCI 435
	Assignment : #6 - The Character Language
	Description: Implements a predictive recursive descent parser for
							   the language given by the following grammar; parser
								 either accepts input string or returns parse error
  Grammar:
    M   -> { S } $
		S   -> I | W | A | P | C | G
		I   -> '[' E ? { S } : { S } ']' | '[' E ? { S } ']'
		W   -> '{' E ? { S } '}'
		A   -> id = E ;
		P   -> '<' E ;
		C   -> '<' ( 'B' | 'T' | 'N' ) ;
		G   -> '>' id ;
		E   -> E + T | E - T | T
		T   -> T * U | T / U | T % U | U
		U   -> F ^ U | F
		F   -> '(' E ')' | id | num
		id  -> lowercaseLetter
		num -> digit
*/

/****************************************************/
// System includes 

#include <cstdio>
#include <cstdlib>
#include <cctype>

/****************************************************/
// Function declarations

void
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
match (char token, const char* callee);

void
error (const char* error);

char
getToken ();

/****************************************************/
// global vars

char g_token;

/****************************************************/

int
main ()
{
  g_token = getToken ();
  M ();
  if (g_token != '$')
    error("main");
  else
		printf ("String accepted\n");

  return EXIT_SUCCESS;
}

/****************************************************/

void
M ()
{
  // to handle production
  // M --> { S } $

  while (g_token != '$')
  {
    S ();
  }
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
  else if (g_token == '<')
	{ // either C or P
		match ('<', "S");
		// check case C lookaheads
		if (g_token == 'B')
			match ('B', "S");
		else if (g_token == 'T')
			match ('T', "S");
		else if (g_token == 'N')
			match ('N', "S");
		else
	  { // must be case P
				E ();
		}
		match (';', "S");
	} else
	{
	  error ("S");
	}
}

/****************************************************/

void
I ()
{
  // to handle production
  // I -> '[' E ? { S } : { S } ']' | '[' E ? { S } ']'

  match ('[', "I");
  E ();
  match ('?', "I");
  while (g_token != ':' && g_token != ']')
    S ();
  if (g_token == ':')
	{
		match (':', "I");
		while (g_token != ']')
			S ();
		match (']', "I");
	}
  else
    match (']', "I");
}

/****************************************************/

void
W ()
{
  // to handle production
  // W --> '{' E ? { S } '}'

  match ('{', "W");
  E ();
  match ('?', "W");
  while (g_token != '}')
    S ();
  match ('}', "W");
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

  match ('=', "A");
  E ();
  match (';', "A");
}

/****************************************************/

void
G ()
{
  // to handle production
  // G --> '>' id ;

  match ('>', "G");
  if (islower (g_token))
    g_token = getToken ();
  else
    error ("G, missing identifier");
  match (';', "G");
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
		match ('^', "U");
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
		match ('(', "F");
		E ();
		match (')', "F");
	}
  else if (islower (g_token))
    g_token = getToken ();
  else if (isdigit (g_token))
    g_token = getToken ();
  else
    error ("F");
}

/****************************************************/
// matches token and advances input
void
match (char token, const char* callee)
{
  if (g_token == token)
    g_token = getToken ();
  else
	{
		printf ("Expected %c, found %c\n", token, g_token);
		error (callee);
	}
}

/****************************************************/

void
error (const char* error)
{
  printf ("\nParse error in %s\n", error);
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
