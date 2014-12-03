/*
  Filename   : AssemblyEmitter.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 12, Code Generation
  Description: Utility to write assembly instructions to a file.
*/

/********************************************************************/
// System includes

#include <iostream>
#include <iomanip>

/********************************************************************/
// Local includes

#include "AssemblyEmitter.h"

/********************************************************************/
// Using declarations

using std::setw;
using std::setfill;
using std::endl;

/********************************************************************/

AssemblyEmitter::AssemblyEmitter (std::ofstream &strm) : outFile (strm) {}

AssemblyEmitter::~AssemblyEmitter () {}

void
AssemblyEmitter::emitComment (const string comment)
{
  outFile << setw (36) << " " << "# " << comment << endl;
}

void
AssemblyEmitter::emitSeparator (int numDividers)
{
  outFile << setfill ('#') << setw (80) << "#" << endl;
}

void
AssemblyEmitter::emitLabel (const string label, const string comment)
{
  outFile << setw (36) << label + ":" << "# " << comment << endl;
}

void
AssemblyEmitter::emitInstruction (const string operation, const string operands,
				  const string comment)
{
  outFile << setw (10) << " " << setw (10) << operation << setw (16) << operands
	  << "# " << comment << endl;
}
