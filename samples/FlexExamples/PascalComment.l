/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <iostream>
#include <cmath>
using namespace std;
%}

DIGIT    [0-9]
ID       [a-z][a-z0-9]*

/* make <comment> an exclusive _start condition_ */
%x comment 

%%

{DIGIT}+    {
              cout << "An integer: " << yytext << '(' << atoi (yytext)
		   << ')' << endl;
            }

{DIGIT}+"."{DIGIT}* {
                      cout << "A float: " << yytext << '(' << atof (yytext)
			   << ')' << endl;
                    }

if|then|begin|end|procedure|function        {
            cout << "A keyword: " << yytext << endl;
          }

{ID}        cout << "An identifier: " << yytext << endl;

"+"|"-"|"*"|"/"   cout << "An operator: " << yytext << endl;

"{"[^}\n]*"}"     /* eat up one-line comments */

"/*"          BEGIN (comment);    /* handle C-style comments also */

<comment>[^*]*           /* munch anything that's not a '*' */
<comment>"*"+[^*/]*      /* eat up '*'s not followed by '*'s or '/'s */
<comment>"*"+"/"         BEGIN (INITIAL);   /* processed whole comment */

[ \t\n]+          /* eat up whitespace */

.           cout << "Unrecognized character: " << yytext << endl;

%%

