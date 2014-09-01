/* Simple integer arithmetic calculator
   according to the EBNF:

   <expr> -> <term> { <addop> <term> }
   <addop> -> + | -
   <term> -> <factor> { <mulop> <factor> }
   <mulop> -> *
   <factor> -> ( <expr> ) | Number

   Inputs a line of text from stdin
   Outputs "error" or the result.
*/

/*********************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cctype>

/*********************************************************************/

// Global token variable
int g_token; 

/*********************************************************************/

int  getToken ();
void error (const char* error);
void match (char expectedToken);

int  expr   ();
int  term   ();
int  factor ();

/*********************************************************************/

int 
main () 
{
  int result;
  // Load token with first character of lookahead
  g_token = getToken ();
  
  result = expr ();
  if (g_token == '$') 
    printf ("Result = %d\n", result);
  else
    // Extraneous chars on line
    error ("main"); 

  return EXIT_SUCCESS;
}

/*********************************************************************/

int
getToken () 
{
  g_token = getchar ();
  while (isspace (g_token))
    g_token = getchar ();

  return g_token;
}

/*********************************************************************/

void
error (const char* error) 
{
  fprintf (stderr, "Error: %s\n", error);
  exit (1);
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

int
expr () 
{
  int temp = term ();

  while ((g_token == '+') || (g_token == '-'))
    switch (g_token)
    {
      case '+':
	match ('+');
	temp += term ();
	break;
      case '-':
	match ('-');
	temp -= term ();
	break;
    }
  
  return temp;
}

/*********************************************************************/

int
term () 
{
  int temp = factor ();
  while (g_token == '*')
  {
    match ('*');
    temp *= factor ();
  }
  return temp;
}

/*********************************************************************/

int
factor ()
{
  int temp;

  if (g_token == '(')
  {
    match ('(');
    temp = expr ();
    match (')');
  }
  else if (isdigit (g_token))
  {
    ungetc (g_token, stdin);
    scanf ("%d", &temp);
    g_token = getToken ();
  }
  else 
    error ("factor");
  
  return temp;
}

