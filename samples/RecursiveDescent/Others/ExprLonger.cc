/* Simple parser -- no output
 *
 * Grammar:
 *   P ---> E '$'
 *   E ---> T { ('+'|'-') T }
 *   T ---> S { ('*'|'/') S }
 *   S ---> F '^' S | F
 *   F ---> NUM | '(' E ')'
 */

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>

char g_token;
int  g_level = 0;

int E ();
int T ();
int S ();
int F ();

void match (char token);
void error (const char* errString);
void getToken ();
void enter (char name);
void leave (char name);
void printSpaces (int level);

int 
main ()
{
  getToken ();
  int result = E ();
  if (g_token != '$') 
  {
    error ("main");
  }
  else
  {
    printf ("Successful parse\n");
    printf ("  Result = %d\n", result);
  }

  return 0;
}

int 
E ()
{
  enter ('E');
  int result = T ();
  while (g_token == '+' || g_token == '-') 
  {
    if (g_token == '+')
    {
      match ('+');
      result += T ();
    }
    else 
    {
      match ('-');
      result -= T ();
    }
  }
  leave ('E');

  return result;
}

int
T ()
{
  enter ('T');
  int result = S ();
  while (g_token == '*' || g_token == '/') 
  {
    if (g_token == '*')
    {
      match ('*');
      result *= S ();
    }
    else
    {
      match ('/');
      result /= S ();
    }
  }
  leave ('T');

  return result;
}

int
S ()
{
  enter ('S');
  int result = F ();
  if (g_token == '^') 
  {
    match ('^');
    int power = S ();
    result = static_cast<int> (pow (result, power));
  }
  leave ('S');

  return result;
}

int
F ()
{
  enter ('F');
  int result;
  if (isdigit (g_token)) 
  {
    ungetc (g_token, stdin);
    scanf ("%d", &result);
    getToken ();
  }
  else if (g_token == '(') 
  {
    match ('(');
    result = E ();
    match (')');
  }
  else
  {
    error ("F");
  }
  leave ('F');

  return result;
}

void
match (char token)
{
  if (g_token == token)
  {
    getToken ();
  }
  else
  {
    error ("match");
  }
}

void 
getToken ()
{
  while (isspace (g_token = getchar ()))
    ;
}

void 
error (const char* errString)
{
  printf ("\n*** ERROR: %s\n", errString);
  exit (1);
}

void 
enter (char name)
{
  printSpaces (g_level++);
  printf ("+-%c: Enter, \t", name);
  printf ("Token == %c\n", g_token);
}

void 
leave (char name)
{
  printSpaces (--g_level);
  printf ("+-%c: Leave, \t", name);
  printf ("Token == %c\n", g_token);
}

void
printSpaces (int level)
{
  while (level-- > 0)
    printf ("| ");
}
