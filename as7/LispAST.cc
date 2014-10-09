/* 
  Filename   : LispAST.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : #7 - Tree Lisperer
  Description: Implements a RD parser for a LISP subset language, outputting
                 AST's
  Grammar:
    lexp     --> number | ( op lexp-seq )
    op       --> + | - | *
    lexp-seq --> lexp { lexp }
*/

/****************************************************/
// System includes 

#include <cstdio>
#include <cstdlib>
#include <cctype>

/****************************************************/
// Function declarations

TreeNode*
parse ();

TreeNode *
lexp ();

TreeNode *
op ();

TreeNode *
lexp-seq ();

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
  Tree t = parse ();
  
  return EXIT_SUCCESS;
}

/****************************************************/

TreeNode *
parse ()
{
  TreeNode * t;
  g_token = getToken ();
  t = lexp ();
  if (token != EOF)
    error ("parse");

  return t;
}

/****************************************************/

TreeNode *
lexp ()
{
  // To handle production
  // lexp --> number | ( op lexp-seq )

  TreeNode * t;
  
  if (isdigit (g_token))
  {
    int num;
    putback (g_token);
    std::cin >> num;
    
    t = newExpNode (NumberK);
    t.value = num;
  }
  else if (g_token == '(')
  {
    match ('(');
    t = newOpNode ();

  }
  else
    error ("lexp");

  return t;  
}

/****************************************************/

TreeNode *
op ()
{
  // To handle production
  // op -->

  TreeNode * t;
  
  return t;  
}

/****************************************************/

TreeNode *
lexp-seq ()
{
  // To handle production
  // lexp-seq -->

  TreeNode * t;
  
  return t;  
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
