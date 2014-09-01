#include <iostream>

#include <cstdio>
#include <cstdlib>

//**

extern FILE* yyin;

int  yylex ();

//**

#define IF 10

//**

int
main (int argc, char* argv[])
{
  ++argv, --argc;  
  if (argc > 0)
  {
    yyin = fopen (argv[0], "r");
  }
  else
  {
    yyin = stdin;
  }

  int result;
  do
  {
    result = yylex ();
    if (result == IF)
    {
      printf ("A keyword: if\n");
    }
  } while (result != 0);

  return EXIT_SUCCESS;
}
