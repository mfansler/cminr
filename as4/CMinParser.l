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

%}

DIGIT     [0-9]
IDENT     [[:alpha:]][[:alnum:]]*

  /* Rules section follows */
%%

{DIGIT}+  {
            return INT;
          }

if        {
            return IF;
          }

else      {
            return ELSE;
          }

void      {
            return VOID;
          }

return    {
            return RETURN;
          }

while     {
            return WHILE;
          }

for       {
            return FOR;
          }

\+        {
            return PLUS;
          }

{IDENT}   {
            return ID;
          }

%%
/* Functions section */
