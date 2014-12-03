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
  emitComment (const string comment);

  void
  emitSeparator (int numDividers);

  void
  emitLabel (const string label, const string comment);

  void
  emitInstruction (const string operation, const string operands,
		   const string comment);

};
  
#endif
