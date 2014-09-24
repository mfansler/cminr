/* Scanner for C- language 
   Definition Section
*/

%{
  #include <iostream>
  #include <cmath>

  #include "CMinTokens.hpp"

  extern "C"
  int
  yylex ();

  int colCount = 0;
  int lineCount = 1;

%}

DIGIT     [0-9]
IDENT     [[:alpha:]][[:alnum:]]*
LCOM      "/*"
RCOM      "*/"
COMMENT   {LCOM}[^{RCOM}]*{RCOM}

%%

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

for          {
               colCount += 3;
               return FOR;
             }

"+"          {
               ++colCount;
               return PLUS;
             }

"-"          {
               ++colCount;
               return MINUS;
             }

"*"          {
               ++colCount;
               return TIMES;
             }

"/"          {
               ++colCount;
               return DIVIDE;
             }

"<"          {
               ++colCount;
               return LT;
             }

"<="         {
               colCount += 2;
               return LTE;
             }

">"          {
               ++colCount;
               return GT;
             }

">="         {
               colCount += 2;
               return GTE;
             }

"=="         {
               colCount += 2;
               return EQ;
             }

"!="         {
               colCount += 2;
               return NEQ;
             }

"++"         {
               colCount += 2;
               return INCREMENT;
             }

"--"         {
               colCount += 2;
               return DECREMENT;
             }

"="          {
               ++colCount;
               return ASSIGN;
             }

";"          {
               ++colCount;
               return SEMI;
             }

","          {
               ++colCount;
               return COMMA;
             }

"("          {
               ++colCount;
               return LPAREN;
             }

")"          {
               ++colCount;
               return RPAREN;
             }

"["          {
               ++colCount;
               return LBRACK;
             }

"]"          {
               ++colCount;
               return RBRACK;
             }

"{"          {
               ++colCount;
               return LBRACE;
             }

"}"          {
               ++colCount;
               return RBRACE;
             }

{IDENT}      {
               colCount += yyleng;
               return ID;
             }

{DIGIT}+     {
               colCount += yyleng;
               return NUM;
             }

{COMMENT}    {
               colCount += yyleng;
             }

\n           {
               ++lineCount;
               colCount = 0;
             } 

[ \t]+       { // consume whitespace
               colCount += yyleng;
             }

.            {
               ++colCount;
               return ERROR;
             }

%%
/* Functions section */
