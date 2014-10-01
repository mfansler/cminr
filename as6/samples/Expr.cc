/* Simple integer arithmetic calculator

   According to the EBNF:

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

void
match (char expectedToken);

int
getToken ();

void
error (const char* error);

int
expr ();

int
term ();

int
factor ();

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
    error ("main"); 

  return EXIT_SUCCESS;
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
  fprintf (stderr, "Error: %s\n", error);
  fprintf (stderr, "  token = %c\n", g_token);
  exit (1);
}

/*********************************************************************/
//   <addop> -> + | -
//   <expr>  -> <term> { <addop> <term> }

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
//   <mulop> -> *
//   <term>  -> <factor> { <mulop> <factor> }

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
//   <factor> -> ( <expr> ) | Number

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

