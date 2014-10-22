%{
  // Prologue section
  #include <cstdio>
  #include <cctype>
  #include <cmath>
  
  extern "C"
  int
  yylex ();

  extern "C"
  void
  yyerror (const char*);

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
%token NUM
%token PLUS
%token MINUS
%token TIMES
%token DIVIDE
%token MODULUS
%token LPAREN
%token RPAREN
%token CARET
%token NEWLINE


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
          exp NEWLINE
          { 
            printf ("\t%d\n", $1);
          }
        | NEWLINE
;

exp : 
      exp PLUS term
      {
        $$ = $1 + $3;
      }
    |
      exp MINUS term
      {
        $$ = $1 - $3;
      }
    | term
      {
        $$ = $1;
      }
;

term :
       term TIMES pow
       {
	 $$ = $1 * $3;
       }
     |
       term DIVIDE pow
       {
	 $$ = $1 / $3;
       }
     |
       term MODULUS pow
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
      factor CARET pow
      {
        $$ = std::pow (static_cast<double> ($1), $3);
      }
    |
      factor
;

factor :
         NUM
         {
	   $$ = $1;
         }
       | 
         MINUS NUM
         {
	   $$ = -$2;
         }
       | 
         LPAREN exp RPAREN
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
/*
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
*/
/*********************************************************************/

void
yyerror (const char* s)
{
  fprintf (stderr, "%s\n", s);
}

