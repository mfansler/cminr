/*
  Filename   : SymbolTableVisitor.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 10,  
  Description: Structure used to traverse C- AST's via Visitor Pattern,
                 building a symbol table and annotating usages
		 (expressions) with corresponding declarations, or
		 returning error information.
*/

/********************************************************************/
// Local Includes

#include "SymbolTable.h"

/********************************************************************/
// SymbolTable Methods

SymbolTable::SymbolTable ()
{
  std::unique_ptr<ScopeTable> globalScope (new ScopeTable);
  m_table.push_back (std::move (globalScope));
}

SymbolTable::~SymbolTable ()
{
  m_table.clear ();
}

// Adjust the nest level; add a new scope table
void
SymbolTable::enterScope ()
{
  ++m_nestLevel;
  
  std::unique_ptr<ScopeTable> scope (new ScopeTable);
  m_table.push_back (std::move (scope));
}


// Adjust the nest level; remove most recent scope table
void
SymbolTable::exitScope ()
{
  m_table.pop_back ();
  --m_nestLevel;
}

// Add a (name, declarationPtr) entry to table
// If successful set nest level in *declarationPtr
// Return true if successful, false o/w
bool
SymbolTable::insert (DeclarationNode* declarationPtr)
{
  declarationPtr->nestLevel = m_nestLevel;
  
  auto result = m_table.back ()->insert ({declarationPtr->identifier, declarationPtr});
  return result.second;
}

// Lookup a name corresponding to a Use node
// Return corresponding declaration pointer on success,
//   nullptr o/w
DeclarationNode* 
SymbolTable::lookup (std::string name)
{
  for (auto scope = m_table.rbegin (); scope != m_table.rend (); ++scope)
  {
    auto result = (*scope)->find (name);
    if ( result != (*scope)->end ())
      return result->second;
  }

  return nullptr;
}
