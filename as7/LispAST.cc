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
// Class definitions

class TreeNode
{ // abstract
  protected:
    TreeNode* child = NULL;
    TreeNode* sibling = NULL;
  
  public:
    virtual int
    evaluate () {};

    void
    setSibling (TreeNode* s)
    {
      sibling = s;
    };

    TreeNode*
    getSibling ()
    {
      return sibling;
    };

    void
    setChild (TreeNode* c)
    {
      child = c;
    };

    TreeNode*
    getChild ()
    {
      return child;
    };
};

class NumberNode: public TreeNode
{
  int value;
  
  public:
    NumberNode (int v)
    {
      value = v;
    }

    int
    evaluate ()
    {
      return value;
    };
};

class AddNode: public TreeNode
{
  public:
    int
    evaluate ()
    {
      int sum = child->evaluate ();
      TreeNode* next = child->getSibling ();
      while (next != NULL)
      {
	sum += next->evaluate ();
	next = next->getSibling ();
      }
      return sum;
    };
};

class TimesNode: public TreeNode
{
  public:
    int
    evaluate ()
    {
      int product = child->evaluate ();
      TreeNode* next = child->getSibling ();
      while (next != NULL || product == 0)
      {
	product *= next->evaluate ();
	next = next->getSibling ();
      }
      return product;
    };
};

class SubtractNode: public TreeNode
{
  public:
    int
    evaluate ()
    {
      int difference = child->evaluate ();
      
      TreeNode* next = child->getSibling ();

      if (next == NULL)
	return -difference;
      
      while (next != NULL)
      {
	difference -= next->evaluate ();
	next = next->getSibling ();
      }
      return difference;
    };
};

/****************************************************/
// Function declarations

TreeNode*
parse ();

TreeNode*
lexp ();

TreeNode*
op ();

TreeNode*
lexpSeq ();

void
match (char token, const char* error);

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
  TreeNode* t = parse ();

  printf ("Valid LISP expression.\nValue = %d\n", t->evaluate ());
  
  return EXIT_SUCCESS;
}

/****************************************************/

TreeNode*
parse ()
{
  TreeNode* t;
  
  g_token = getToken ();
  t = lexp ();
  if (g_token != EOF)
    error ("parse, trailing characters found");

  return t;
}

/****************************************************/

TreeNode*
lexp ()
{
  // To handle production
  // lexp --> number | ( op lexpSeq )

  TreeNode* t;
  
  if (isdigit (g_token))
  {
    int num;
    ungetc (g_token, stdin);
    scanf ("%d", &num);
    
    t = new NumberNode (num);

    g_token = getToken ();
  }
  else if (g_token == '(')
  {
    match ('(', "lexp");
    t = op ();
    t->setChild (lexpSeq ());
    match (')', "lexp");
  }
  else
    error ("lexp, invalid start of expression");

  return t;  
}

/****************************************************/

TreeNode*
op ()
{
  // To handle production
  // op --> + | - | *
  
  TreeNode* t;

  switch (g_token)
  {
    case '*':
      match ('*', "op");
      t = new TimesNode ();
      break;
    case '+':
      match ('+', "op");
      t = new AddNode ();
      break;
    case '-':
      match ('-', "op");
      t = new SubtractNode ();
      break;
    default:
      error ("op, operator missing");
  }
  
  return t;  
}

/****************************************************/

TreeNode*
lexpSeq ()
{
  // To handle production
  // lexpSeq --> lexp { lexp }
  
  TreeNode* t;
  if (g_token == '(' || isdigit (g_token))
  {
    t = lexp ();
    TreeNode* next = t;
    while (g_token == '(' || isdigit (g_token))
    {
      next->setSibling (lexp ());
      next = next->getSibling ();
    }
  }
  else
    error ("lexpSeq, invalid expression start");
  
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
