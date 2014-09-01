/* Parser for simple lisp, with debug output
 *
 * Grammar:  start  --->  sexpr '$'
 *           sexpr  --->  alphanum   |   '('    tail
 *           tail   --->  ')'        |   sexpr  tail
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

void sexpr ();
void tail ();

char getToken ();
void error (int errNum);
void printSpaces (int n);
void enter (char* name);
void leave (char* name);
void match (char ch);

/* Next token */
char g_token;	

/* Produce debug output if non-zero */
int g_debug = 1;

/* Used for debug output */
int g_level;	

int
main ()
{
  g_token = getToken ();
  sexpr ();
  match ('$');

  return 0;
}

// Recognize a lisp s-expression
void
sexpr ()
{
  if (g_debug)
    enter ("sexpr");

  if (isalnum (g_token))
    match (g_token);
  else if (g_token == '(')
  {
    match ('(');
    tail ();
  }
  else
    error (0);

  if (g_debug)
    leave ("sexpr");
}

// Recognize tail end of a lisp s-expression
void
tail ()
{
  if (g_debug)
    enter ("tail");
  
  if (g_token == ')')
    match (')');
  else if (isalnum (g_token) || g_token == '(')
  {
    sexpr ();
    tail ();
  }
  else
    error (0);
  
  if (g_debug)
    leave ("tail");
}

//**

void
error (int errNum)
{
  printf ("Error number: %ld\n", errNum);
  exit (1);
}

void
match (char ch)
{
  if (g_token == ch)
    g_token = getToken ();
  else
    error (0);
}

// Fetch next token (here just a char)
char
getToken ()
{
  char ch;

  if (g_token == '$')
    return EOF;

  while (isspace (ch = getchar ()))
    ;

  return ch;
}

void
printSpaces (int level)
{
  while (level-- > 0)
    printf ("| ");
}

void 
enter (char* name)
{
  if (g_debug)
  {
    printSpaces (g_level++);
    printf ("+-%s: Enter, \t", name);
    printf ("Token == %c\n", g_token);
  }
}

void 
leave (char* name)
{
  if (g_debug)
  {
    printSpaces (--g_level);
    printf ("+-%s: Leave, \t", name);
    printf ("Token == %c\n", g_token);
  }
}
