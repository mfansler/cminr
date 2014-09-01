%{
  #include <cstdio>
  #include <cstring>

  int numChars = 0;
  int numWords = 0;
  int numLines = 0;

  // C++ comments OK here
%}

delim      [ \t]+
wordChar   [^ \t\n]

%%

\n | 
{wordChar}+ |
{delim}         { char firstChar = yytext[0];
                  if (firstChar == '\n')
                    ++numLines; 
                  else if (strchr (" \t", firstChar) == NULL) 
                    ++numWords; 
                  numChars += yyleng;
                }

%%

int
main ()
{
  yylex ();
  printf ("%8d%8d%8d\n", numLines, numWords, numChars);

  return 0;
}
