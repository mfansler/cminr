/********************************************************************/
// Symbol Table Header File
// CSCI 435: Compilers class
// Fall 2014

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

/********************************************************************/
// System Includes

#include <vector>
#include <string>
#include <unordered_map>
// For unique_ptr
#include <memory>

/********************************************************************/
// Local Includes

#include "CMinusAst.h"

/********************************************************************/
// Using Declarations

using ScopeTable = std::unordered_map<std::string, DeclarationNode*>;

/********************************************************************/

class SymbolTable 
{
public:

  SymbolTable  ();
  ~SymbolTable ();
  
  // Adjust the nest level; add a new scope table
  void
  enterScope   ();

  // Adjust the nest level; remove most recent scope table
  void
  exitScope    ();

  // Add a (name, declarationPtr) entry to table
  // If successful set nest level in *declarationPtr
  // Return true if successful, false o/w
  bool 
  insert       (DeclarationNode* declarationPtr);
  
  // Lookup a name corresponding to a Use node
  // Return corresponding declaration pointer on success,
  //   nullptr o/w
  DeclarationNode* 
  lookup       (std::string name);

private:
  
  // Current nest level; 0 is global
  int  m_nestLevel;

  // The symbol table is a vector of scope tables
  std::vector<std::unique_ptr<ScopeTable>> m_table;
};

#endif
