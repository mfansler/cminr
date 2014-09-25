/* 
   Filename    : CMinTokens.hpp
   Author      : Merv Fansler
   Course      : CSCI 435
   Assignment  : Assignment 4, Lex Luthor vs C-
   Description : Defines Tokens for C- Language
*/

#ifndef __CMINTOKENS_HPP_INCLUDED__
#define __CMINTOKENS_HPP_INCLUDED__

enum TokenType
{
  ERROR = 1,

  IF, ELSE, INT, VOID, RETURN, WHILE, FOR,

  PLUS, MINUS, TIMES, DIVIDE, LT, LTE, GT, GTE, EQ, NEQ,

  INCREMENT, DECREMENT,

  ASSIGN, SEMI, COMMA, LPAREN, RPAREN, LBRACK, RBRACK, LBRACE, RBRACE,

  ID, NUM
};

#endif
