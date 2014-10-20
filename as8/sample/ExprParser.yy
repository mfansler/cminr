%{
  // Prologue section
  #include <cstdio>
  #include <cctype>
  #include <cmath>
  
  extern "C"
  int
  yylex ();

  void
  yyerror (const char* s);

  // Type of "yylval"
  #define YYSTYPE int

  // For debugging must do the following:
     #define YYDEBUG 1
  //   Set "yydebug" to 1 in driver
%}

/* 
   Understand bison spec file; run a couple times
   Separate code into driver, parser, and lexer C++ source files
   Write Makefile

   Modify grammar:
     (done) Add mod (%)
     (done) Add integer division (/) 
     (done) Add unary minus (higher precedence than term)
     (done) Add exponentiation (^) (highest prec, right associative)
     (done) Allow multiple commands to be entered

   Finally, use Flex to generate the lexer
     (Use "-d" option for Bison)
*/

/** Declarations **/ 

/* Declare tokens, with precedence and assoc. if necessary */
%token NUMBER

/* Declare non-terminals if necessary */

/* Declare start symbol */
%start input

%%

/* Grammar rules */

input :
        input command
      |
        command
;

command : 
          exp '\n'
          { 
            printf ("\t%d\n", $1);
          }
        | '\n'
;

exp : 
      exp '+' term
      {
        $$ = $1 + $3;
      }
    |
      exp '-' term
      {
        $$ = $1 - $3;
      }
    | term
      {
        $$ = $1;
      }
;

term :
       term '*' pow
       {
	 $$ = $1 * $3;
       }
     |
       term '/' pow
       {
	 $$ = $1 / $3;
       }
     |
       term '%' pow
       {
	 $$ = $1 % $3;
       }
     |
       pow
       {
	 $$ = $1;
       }
;

pow :
      factor '^' pow
      {
        $$ = std::pow (static_cast<double> ($1), $3);
      }
    |
      factor
;

factor :
         NUMBER
         {
	   $$ = $1;
         }
       | 
         '-' NUMBER
         {
	   $$ = -$2;
         }
       | 
         '(' exp ')'
         {
	   $$ = $2;
         }
;         


%%

/*********************************************************************/
// Epilogue

int
main ()
{
  // Uncomment to show parser actions (shifts and reductions)
  //extern int yydebug;
  //yydebug = 1;

  int parseResult = yyparse ();

  return parseResult;
}

/*********************************************************************/

int
yylex ()
{
  int c;
  // Eat spaces and tabs
  while ((c = getchar ()) == ' ' || c == '\t')
    ;
  
  // Pick up ints
  if (isdigit (c))
  {
    ungetc (c, stdin);
    scanf ("%d", &yylval);
    return NUMBER;
  }

  // Pick up operators and parens
  return c;
}

/*********************************************************************/

void
yyerror (const char* s)
{
  fprintf (stderr, "%s\n", s);
}
