/*
  Filename   : AssemblyEmitter.h
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 12, Code Generation
  Description: Utility to write assembly instructions to a file.
*/

#ifndef __C_MINUS_ASSEMBLY_EMITTER_H__
#define __C_MINUS_ASSEMBLY_EMITTER_H__

/********************************************************************/
// System includes

#include <string>
#include <fstream>
#include <initializer_list>

/********************************************************************/
// Using declarations

using std::string;

/********************************************************************/
// Class declaration

class AssemblyEmitter
{
  std::ofstream &outFile;
  int labelCounter;

public:

  AssemblyEmitter (std::ofstream &strm);
  ~AssemblyEmitter ();

  // utility
  string
  createUniqueLabel ();

  // generic emission methods
  void
  emitComment (const string& comment);

  void
  emitComment (std::initializer_list<string> comments);

  void
  emitLabel (const string& label, const string& comment = "");

  void
  emitInstruction (const string& operation, const string& operands = "",
		   const string& comment = "");

  void
  emitFunctionDeclaration (const string& name);

  void
  emitEnter (const string& a = "0", const string& b = "0");

  void
  emitConstDeclaration (const string& name, const string& type,
			const string& value);

  // concrete emission methods
  void
  emitSeparator (int numDividers = 1);

  void
  emitInputFunction ();

  void
  emitOutputFunction ();

};
  
#endif
