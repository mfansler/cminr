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
AssemblyEmitter::emitComment (const string& comment)
{
  outFile << setw (42) << " " << "# " << comment << endl;
}

void
AssemblyEmitter::emitComment (std::initializer_list<string> comments)
{
  for (auto c : comments)
    emitComment (c);
}

void
AssemblyEmitter::emitSeparator (int numDividers)
{
  outFile << setfill ('#')
	  << setw (80) << "#" << endl
	  << setfill (' ');
}

void
AssemblyEmitter::emitLabel (const string& label, const string& comment)
{
  outFile << setw (42) << label + ":" << "# " << comment << endl;
}

void
AssemblyEmitter::emitInstruction (const string& operation, const string& operands,
				  const string& comment)
{
  outFile << setw (10) << " " << setw (10) << operation << setw (22) << operands
	  << "# " << comment << endl;
}

void
AssemblyEmitter::emitDeclaration (const string& name)
{
  outFile << ".globl " << name << endl;
}
