/* 
   Filename    : CMinLexer.l
   Author      : Merv Fansler
   Course      : CSCI 435
   Assignment  : Assignment 4, Lex Luthor vs C-
   Description : Scanner for C- language as per Louden, "Compiler
                   Construction" specification
*/

/* Definitions Section */

%{
  #include "CMinTokens.h"

  extern "C"
  int
  yylex ();

  int colCount = 0;
  int lineCount = 1;
%}

DIGIT     [0-9]
IDENT     [[:alpha:]][[:alpha:]]*

%%
 /* Rules section */

int       {
            colCount += 3;
            return INT;
          }

if        {
            colCount += 2;
            return IF;
          }

else      {
            colCount += 4;
            return ELSE;
          }

void      {
            colCount += 4;
            return VOID;
          }

return    {
            colCount += 6;
            return RETURN;
          }

while     {
            colCount += 5;
            return WHILE;
          }

for       {
            colCount += 3;
            return FOR;
          }

"+"       {
            ++colCount;
            return PLUS;
          }

"-"       {
            ++colCount;
            return MINUS;
          }

"*"       {
            ++colCount;
            return TIMES;
          }

"/"       {
            ++colCount;
            return DIVIDE;
          }

"<"       {
            ++colCount;
            return LT;
          }

"<="      {
            colCount += 2;
            return LTE;
          }

">"       {
            ++colCount;
            return GT;
          }

">="      {
            colCount += 2;
            return GTE;
          }

"=="      {
            colCount += 2;
            return EQ;
          }

"!="      {
            colCount += 2;
            return NEQ;
          }

"++"      {
            colCount += 2;
            return INCREMENT;
          }

"--"      {
            colCount += 2;
            return DECREMENT;
          }

"="       {
            ++colCount;
            return ASSIGN;
          }

";"       {
            ++colCount;
            return SEMI;
          }

","       {
            ++colCount;
            return COMMA;
          }

"("       {
            ++colCount;
            return LPAREN;
          }

")"       {
            ++colCount;
            return RPAREN;
          }

"["       {
            ++colCount;
            return LBRACK;
          }

"]"       {
            ++colCount;
            return RBRACK;
          }

"{"       {
            ++colCount;
            return LBRACE;
          }

"}"       {
            ++colCount;
            return RBRACE;
          }

{IDENT}   {
            colCount += yyleng;
            return ID;
          }

{DIGIT}+  {
            colCount += yyleng;
            return NUM;
          }

"/*"      {
            bool foundAsterisk = false;
            bool foundCloseComment = false;
            char c;
            
            // save initial counts for error reporting
            int openLine = lineCount;
            int openCol = colCount;

            colCount += 2;

            while (!foundCloseComment)
            { 
              while(!foundAsterisk)
              {
                c = yyinput ();
                ++colCount;

                if (c == '*')
                {
                  foundAsterisk = true;
                }
                else if (c == '\n')
                {
                  ++lineCount;
                  colCount = 0;
                }
                else if (c == EOF)
                {
                  // reset info
                  lineCount = openLine;
                  colCount = openCol;
                  strncpy (yytext, "/* ... (unbalanced)", 19);

                  return ERROR;
                }
              }
                
              c = yyinput ();
              ++colCount;
                 
              switch (c)
              {
                case '/':
                  foundCloseComment = true;
                  break;

                case '*':
                  break;

                case EOF:
                  // reset info
                  lineCount = openLine;
                  colCount = openCol;
                  strncpy (yytext, "/* ... (unbalanced)", 19);

                  return ERROR;

                default:
                  foundAsterisk = false;
                  break;
              }
            }
          } 

\n        {
            ++lineCount;
            colCount = 0;
          } 

[ \t]+    {
            colCount += yyleng;
          }

.         {
            ++colCount;
            return ERROR;
          }

%%
/* Functions Section */
