/*A
  Filename   : CMinLexerDriver.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 4, Lex Luthor vs C-
  Description: Driver for C- lexer that accepts an C- source input and outputs
                 a list of the resulting tokens
*/

// System Includes

#include <iostream>
#include <map>
#include <string>

#include <cstdio>
#include <cstdlib>

// Local Includes

#include "CMinTokens.hpp"

//**

extern "C"
int
yylex ();

extern FILE* yyin;

extern char* yytext;

extern int lineCount;
extern int colCount;

//**

std::map<int, std::string> tokenNames = 
  {
    {
      ERROR, "ERROR"
    },
    {
      IF, "IF"
    },
    {
      ELSE, "ELSE"
    },
    {
      INT, "INT"
    },
    {
      VOID, "VOID"
    },
    {
      RETURN, "RETURN"
    },
    {
      WHILE, "WHILE"
    },
    {
      FOR, "FOR"
    },
    {
      PLUS, "PLUS"
    },
    {
      MINUS, "MINUS"
    },
    {
      TIMES, "TIMES"
    },
    {
      DIVIDE, "DIVIDE"
    },
    {
      LT, "LT"
    },
    {
      LTE, "LTE"
    },
    {
      GT, "GT"
    },
    {
      GTE, "GTE"
    },
    {
      EQ, "EQ"
    },
    {
      NEQ, "NEQ"
    },
    {
      INCREMENT, "INCREMENT"
    },
    {
      DECREMENT, "DECREMENT"
    },
    {
      ASSIGN, "ASSIGN"
    },
    {
      SEMI, "SEMI"
    },
    {
      COMMA, "COMMA"
    },
    {
      LPAREN, "LPAREN"
    },
    {
      RPAREN, "RPAREN"
    },
    {
      LBRACK, "LBRACK"
    },
    {
      RBRACK, "RBRACK"
    },
    {
      LBRACE, "LBRACE"
    },
    {
      RBRACE, "RBRACE"
    },
    {
      ID, "ID"
    },
    {
      NUM, "NUM"
    } 
  };


int
main (int argc, char* argv[])
{
  ++argv, --argc;
  if (argc > 0)
  {
    yyin = fopen (argv[0], "r");
  }
  else
  {
    yyin = stdin;
  }

  int result;

  printf ("TOKEN\tLEXEME\tVALUE\n=====\t======\t=====\n");
  do
  {
    result = yylex ();
    std::cout << tokenNames[result] << "\t\"" << yytext << '"'; 

    if (result == NUM)
    {
      printf ("\t%i", std::stoi (yytext));
    }
    else if (result == ID)
    {
      printf ("\t\"%s\"", yytext);
    }
    else if (result == ERROR)
    {
      printf ("Line: %i\tColumn: %i", lineCount, colCount);
    }

    printf ("\n");

  } while (result != 0);

  return EXIT_SUCCESS;
}
