/* Simple parser for an expression grammar
 *
 * Grammar:
 *   prog   ---> expr '$'
 *   expr   ---> term { ('+'|'-') term }
 *   term   ---> super { ('*'|'/') super }
 *   super  ---> factor [ '^' super ]
 *   factor ---> NUM | '(' expr ')'
 */

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>

/*********************************************************************/

int
expr ();

int
term ();

int
super ();

int
factor ();

void
match (char token);

void
error (const char* error);

char
getToken ();

void
enter (char name);

void
leave (char name);

void
printSpaces (int level);

/*********************************************************************/

char g_token;
// For indenting trace output
int  g_level = 0;

/*********************************************************************/

int 
main ()
{
  g_token = getToken ();
  int result = expr ();
  if (g_token != '$') 
    error ("main");
  else
  {
    printf ("Successful parse\n");
    printf ("  Result = %d\n", result);
  }

  return EXIT_SUCCESS;
}

/*********************************************************************/

int 
expr ()
{
  enter ('E');
  int result = term ();
  while (g_token == '+' || g_token == '-') 
  {
    if (g_token == '+')
    {
      match ('+');
      result += term ();
    }
    else 
    {
      match ('-');
      result -= term ();
    }
  }
  leave ('E');

  return result;
}

/*********************************************************************/

int
term ()
{
  enter ('T');
  int result = super ();
  while (g_token == '*' || g_token == '/') 
  {
    if (g_token == '*')
    {
      match ('*');
      result *= super ();
    }
    else
    {
      match ('/');
      result /= super ();
    }
  }
  leave ('T');

  return result;
}

/*********************************************************************/

int
super ()
{
  enter ('S');
  int result = factor ();
  if (g_token == '^') 
  {
    match ('^');
    int power = super ();
    result = static_cast<int> (pow (result, power));
  }
  leave ('S');

  return result;
}

/*********************************************************************/

int
factor ()
{
  enter ('F');
  int result;
  if (isdigit (g_token)) 
  {
    ungetc (g_token, stdin);
    scanf ("%d", &result);
    g_token = getToken ();
  }
  else if (g_token == '(') 
  {
    match ('(');
    result = expr ();
    match (')');
  }
  else
  {
    error ("factor");
  }
  leave ('F');

  return result;
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
  printf ("\n*** ERROR: %s\n", error);
  exit (1);
}

/*********************************************************************/

void 
enter (char name)
{
  printSpaces (g_level++);
  printf ("+-%c: Enter, \t", name);
  printf ("Token == %c\n", g_token);
}

/*********************************************************************/

void 
leave (char name)
{
  printSpaces (--g_level);
  printf ("+-%c: Leave, \t", name);
  printf ("Token == %c\n", g_token);
}

/*********************************************************************/

void
printSpaces (int level)
{
  while (level-- > 0)
    printf ("| ");
}
