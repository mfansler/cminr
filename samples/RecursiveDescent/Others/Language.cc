/* Simple integer arithmetic calculator
   
M  --->  { S }
S  --->  I  |  W  |  A  |  P  |  C  |  G
I  --->  '[' E ? { S } : { S } ']'  |  '[' E ? { S } ']'
W  --->  '{' E ? { S } '}'
A  --->  id = E ;
P  --->  <  E  ;
C  --->  < ( 'B' | 'T' | 'N' ) ;
G  --->  >  id ;
E  --->  T { (+ | -) T }
T  --->  U { (* | / | %) U }
U  --->  F ^ U | F
F  --->  '(' E ')'  |  id  |  num

id  ---> letter 
num ---> digit

*/

/*********************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

/*********************************************************************/

// Global token variable
int g_token; 

/*********************************************************************/
// Function prototypes for recursive calls 

void M ();
void S ();
void SS ();
void I ();
void W ();
void A ();
void PorC ();
void P ();
void C ();
void G ();
void E ();
void T ();
void U ();
void F ();


int  getToken ();
void error (char* errorString);
void match (char expectedToken);

/*********************************************************************/

int 
main ()
{
  // Load token with first character of lookahead 
  g_token = getToken (); 
  
  M ();
  
  if (g_token == '$')
    printf ("Valid.\n");
  else
    // Extraneous chars on line
    error ("$"); 

  return EXIT_SUCCESS;
}

/*********************************************************************/

void 
M () 
{
  SS ();

  if (g_token != '$')
    error ("M");
}

/*********************************************************************/

void
SS ()
{
  while (strchr ("[{<>", g_token) || isalpha (g_token))
    S ();
}

/*********************************************************************/

void
S () 
{
  if (g_token == '[') 
    I ();
  else if (g_token == '{')
    W ();
  else if (g_token == '<')
    PorC ();
  else if (g_token == '>')
    G ();
  else if (isalpha (g_token))
    A ();
  else
    error ("S");
}

/*********************************************************************/

void 
I () 
{
  match ('[');
  E ();
  match ('?');
  SS ();
  if (g_token == ':')
  {
    match (':');
    SS ();
  }
  match (']');
}    

/*********************************************************************/

void 
W () 
{
  match ('{');
  E ();
  match ('?');
  SS ();
  match ('}');
}

/*********************************************************************/

void 
A () 
{
  if (isalpha (g_token))
  {
    g_token = getToken ();
    match ('=');
    E ();
    match (';');
  }
  else
    error ("A");
}
  
/*********************************************************************/

void 
PorC () 
{
  match ('<');
  if (g_token == '(' || isdigit (g_token) || isalpha (g_token))
    P ();
  else if (strchr ("BTN", g_token))
    C ();
  else
    error ("P or C");
}

/*********************************************************************/

void 
P () 
{
  E ();
  match (';');
}

/*********************************************************************/

void 
C () 
{
  switch (g_token) 
  {
    case 'B':
      match ('B');
      break;
    case 'T':
      match ('T');
      break;
    case 'N':
      match ('N');
      break;
    default:
      error ("C");
  }
  
  match (';');
}

/*********************************************************************/

void 
G () 
{
  match ('>');
  if (isalpha (g_token))
    g_token = getToken ();
  else
    error ("G");
  match (';');
}

/*********************************************************************/

void 
E () 
{
  T ();
  while (g_token == '+' || g_token == '-') 
  {
    match (g_token);
    T ();
  }
}

/*********************************************************************/

void 
T () 
{
  U ();
  if (strchr ("*/%", g_token))
  {
    match (g_token);
    T ();
  }
}

/*********************************************************************/

void 
U () 
{
  F ();
  if (g_token == '^') 
  { 
    match ('^');
    U ();
  }
}

/*********************************************************************/

void 
F () 
{
  if (g_token == '(') 
  {
    match ('(');
    E ();
    match (')');
  } 
  else if (isalpha (g_token))
    g_token = getToken ();
  else if (isdigit (g_token))
    g_token = getToken ();
  else
    error ("F");
}

/*********************************************************************/

void
error (char* errorString)
{
  fprintf (stderr, "Error: Parsing %s, token %c\n", errorString, g_token);
  exit (1);
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
match (char expectedToken)
{
  if (g_token == expectedToken) 
    g_token = getToken ();
  else
    error ("Token Match");
}
