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

const uint INDENT_WIDTH = 10;
const uint INSTRUCTION_WIDTH = 10;
const uint OPERANDS_WIDTH = 22;
const uint COMMENT_INDENT_WIDTH = INDENT_WIDTH + INSTRUCTION_WIDTH + OPERANDS_WIDTH;
const uint FULL_WIDTH = 80;

AssemblyEmitter::AssemblyEmitter (std::ofstream &strm) : outFile (strm)
{
  outFile << std::left;
}

AssemblyEmitter::~AssemblyEmitter () {}

void
AssemblyEmitter::emitComment (const string& comment)
{
  outFile << setw (COMMENT_INDENT_WIDTH) << " " << "# " << comment << endl;
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
	  << setw (FULL_WIDTH) << "#" << endl
	  << setfill (' ');
}

void
AssemblyEmitter::emitLabel (const string& label, const string& comment)
{
  outFile << setw (COMMENT_INDENT_WIDTH) << label + ":" << "# " << comment << endl;
}

void
AssemblyEmitter::emitInstruction (const string& operation, const string& operands,
				  const string& comment)
{
  outFile << setw (INDENT_WIDTH) << " " << setw (10) << operation << setw (22) << operands
	  << "# " << comment << endl;
}

void
AssemblyEmitter::emitFunctionDeclaration (const string& name)
{
  outFile << ".globl " << name << endl;
  emitInstruction (".type", name + ", @function", "\"" + name + "\" is type function");
}

void
AssemblyEmitter::emitConstDeclaration (const string& name, const string& type,
				       const string& value)
{
  outFile << setw (INDENT_WIDTH) << name + ":"
	  << setw (INSTRUCTION_WIDTH) << type
	  << setw (OPERANDS_WIDTH) << value << endl;
}

void
AssemblyEmitter::emitEnter (const string& a, const string& b)
{
  emitInstruction ("enter", "$" + a + ", $" + b, "save stack & frame ptrs");
}
