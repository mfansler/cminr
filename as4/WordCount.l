%{
  // This "solution" needs fixing (exercise for student)

  #include <cstdio>

  int numChars = 0;
  int numWords = 0;
  int numLines = 0;

  extern "C" int yylex ();
  // C++ comments OK here
%}

word       [^ \t\n]+

%%

\n         { ++numChars; ++numLines; }
{word}     { numChars += yyleng; ++numWords; } 
.          { ++numChars; }

%%

int
main ()
{
  yylex ();
  printf ("%8d%8d%8d\n", numLines, numWords, numChars);

  return 0;
}
