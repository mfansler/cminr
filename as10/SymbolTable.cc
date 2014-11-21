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
// System Includes

#include <vector>
#include <string>
#include <unordered_map>
// For unique_ptr
#include <memory>

/********************************************************************/
// Local Includes

#include "SymbolTable.h"

/********************************************************************/
// Using Declarations

using ScopeTable = std::unordered_map<std::string, DeclarationNode*>;

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

void
SymbolTable::enterScope ()
{
  ++m_nestLevel;
  
  std::unique_ptr<ScopeTable> scope (new ScopeTable);
  m_table.push_back (std::move (scope));
}

void
SymbolTable::exitScope ()
{
  m_table.pop_back ();
  --m_nestLevel;
}

bool
SymbolTable::insert (DeclarationNode* declarationPtr)
{
  declarationPtr->nestLevel = m_nestLevel;
  
  auto result = m_table.back ()->insert ({declarationPtr->identifier, declarationPtr});
  return result.second;
}

DeclarationNode* 
SymbolTable::lookup (std::string name)
{
  auto scope = m_table.rbegin ();
  for (; scope != m_table.rend (); ++scope)
  {
    auto result = (*scope)->find (name);
    if ( result != (*scope)->end ())
      return result->second;
  }

  return nullptr;
}
