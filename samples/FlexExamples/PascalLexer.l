/* Scanner for a Pascal-like language 
   Definition section 
*/

%{
  #include <iostream>
  #include <cmath>   

  using std::cout;
  using std::endl;

  #define IF 10
%}

DIGIT    [0-9]
ID       [a-z][a-z0-9]*

/* Rules section follows */
%%

{DIGIT}+    {
              cout << "An integer: " << yytext << '(' << atoi (yytext)
		   << ')' << endl;
            }

{DIGIT}+"."{DIGIT}* {
                      cout << "A float: " << yytext << '(' << atof (yytext)
			   << ')' << endl;
                    }

if                  { return IF; }

then                |
begin               |
end                 |
procedure           |
function            {
                      cout << "A keyword: " << yytext << endl;
                    }

{ID}                cout << "An identifier: " << yytext << endl;

"+"|"-"|"*"|"/"     cout << "An operator: " << yytext << endl;

"{"[^}\n]*"}"       // Eat up one-line comments

[ \t\n]+            // Eat up whitespace

.                   {
                      cout << "Unrecognized character: " 
                           << yytext << endl;
                    }

%%
/* Functions section */
