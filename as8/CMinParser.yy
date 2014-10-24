/*
  Filename   : CMinParser.yy
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 8, C- Parser_2
  Description: Bison-based implementation of C- parser; acceptence only version
*/

%{
  // Prologue section
  
  extern "C"
  int
  yylex ();

  extern int lineCount;
  extern int colCount;

  void
  yyerror (const char*);

  // Type of "yylval"
  #define YYSTYPE int

  // For debugging must do the following:
     #define YYDEBUG 1
  //   Set "yydebug" to 1 in driver
%}

/** Declarations **/ 

/* Declare tokens, with precedence and assoc. if necessary */
%token ERROR
%token IF
%token ELSE
%token INT
%token VOID
%token RETURN
%token WHILE
%token FOR
%token PLUS
%token MINUS
%token TIMES
%token DIVIDE
%token LT
%token LTE
%token GT
%token GTE
%token EQ
%token NEQ
%token INCREMENT
%token DECREMENT
%token ASSIGN
%token SEMI
%token COMMA
%token LPAREN
%token RPAREN
%token LBRACK
%token RBRACK
%token LBRACE
%token RBRACE
%token ID
%token NUM

// Explicitly resolve dangling ELSE
%right RPAREN ELSE

// Include found / expected tokens in error message
%define parse.error verbose

/* Declare non-terminals if necessary */

/* Declare start symbol */
%start program

%%

/* Grammar rules */

program :
	declaration-list
;

declaration-list :
		   declaration-list declaration
		 |
		   declaration
;

declaration :
	      var-declaration
	    |
	      fun-declaration
;

var-declaration :
		  type-specifier ID SEMI
		|
		  type-specifier ID LBRACK NUM RBRACK SEMI
;

type-specifier :
	         INT
	       |
		 VOID
;

fun-declaration :
		  type-specifier ID LPAREN params RPAREN compound-stmt
;

params :
         param-list
       |
	 VOID
;

param-list :
	     param-list COMMA param
       	   |
	     param
;

param :
        type-specifier ID
      |
	type-specifier ID LBRACK RBRACK
;

compound-stmt :
	        LBRACE local-declarations statement-list RBRACE
;

local-declarations :
		     local-declarations var-declaration
		   |
		     %empty
;

statement-list :
	         statement-list statement
	       |
		 %empty
;

statement :
	    expression-stmt
	  | 
	    compound-stmt
	  | 
	    selection-stmt
	  | 
	    iteration-stmt
	  |
	    for-stmt
	  | 
	    return-stmt
;

expression-stmt :
		  expression SEMI
		|
		  SEMI
;

selection-stmt :
	         IF LPAREN expression RPAREN statement
	       |
		 IF LPAREN expression RPAREN statement ELSE statement
;

iteration-stmt :
	         WHILE LPAREN expression RPAREN statement
;

for-stmt :
	   FOR LPAREN expression-stmt expression-stmt expression RPAREN statement
	 |
	   FOR LPAREN expression-stmt expression-stmt RPAREN statement
;

return-stmt :
	      RETURN SEMI
	    |
	      RETURN expression SEMI
;

expression :
	     var ASSIGN expression
	   |
	     INCREMENT var
	   |
	     DECREMENT var
	   |
	     simple-expression
;

var :
      ID
    |
      ID LBRACK expression RBRACK
;

simple-expression :
		    additive-expression relop additive-expression
		  |
		    additive-expression
;

relop :
        LTE
      | 
        LT
      | 
        GT
      | 
        GTE
      | 
        EQ
      | 
        NEQ
;

additive-expression :
		       additive-expression addop term
		     |
		       term
;

addop :
        PLUS
      |
        MINUS
;

term :
       term mulop factor
     |
       factor
;

mulop :
        TIMES
      |
	DIVIDE
;

factor :
         LPAREN expression RPAREN
       |
         var
       |
         call
       |
         NUM
;

call :
       ID LPAREN args RPAREN
;

args :
       arg-list
     |
       %empty
;

arg-list :
	   arg-list COMMA expression
	 |
	   expression
;

%%

/*********************************************************************/
// Epilogue

void
yyerror (const char* s)
{
  fprintf (stderr, "%s\nLine %d, Column %d\n", s, lineCount, colCount);
}

