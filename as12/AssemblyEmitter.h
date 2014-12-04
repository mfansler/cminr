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

public:

  AssemblyEmitter (std::ofstream &strm);
  ~AssemblyEmitter ();

  void
  emitComment (const string& comment);

  void
  emitComment (std::initializer_list<string> comments);

  void
  emitSeparator (int numDividers = 1);

  void
  emitLabel (const string& label, const string& comment = "");

  void
  emitInstruction (const string& operation, const string& operands = "",
		   const string& comment = "");

  void
  emitDeclaration (const string& name);

};
  
#endif
