/* 
   Filename    : ExprLexer.l
   Author      : Merv Fansler
   Course      : CSCI 435
   Assignment  : Assignment 8.0, Practice ExprParser
   Description : Practice lexer for scanning simple math expressions
*/

/* Definitions Section */

%{
  #include <string>

  #include "ExprParser.hh"

  extern "C"
  int
  yylex ();

%}

DIGIT     [0-9]

%%
 /* Rules section */

"+"       {
            return PLUS;
          }

"-"       {
            return MINUS;
          }

"*"       {
            return TIMES;
          }

"/"       {
            return DIVIDE;
          }

"%"       {
            return MODULUS;
          }

"("       {
            return LPAREN;
          }

")"       {
            return RPAREN;
          }

"^"       {
            return CARET;
          }

{DIGIT}+  {
            yylval = std::stoi (yytext);
            return NUM;
          }

\n        {
           // ++lineCount;
           // colCount = 0;
            return NEWLINE;
          } 

[ \t]+    {
            //colCount += yyleng;
          }

.         {
            //++colCount;
            return 0;
          }

%%
/* Functions Section */
