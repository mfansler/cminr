%{
  #include <cstdio>

  int numChars = 0;
  int numWords = 0;
  int numLines = 0;

  // C++ comments OK here
%}

delim      [ \t]+
wordChar   [^ \t\n]

%%

\n           { ++numChars; ++numLines; }
{wordChar}+  { ++numWords; numChars += yyleng; }
{delim}      {   numChars += yyleng; } 

%%

int
main ()
{
  yylex ();
  printf ("%8d%8d%8d\n", numLines, numWords, numChars);

  return 0;
}
