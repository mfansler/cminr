/*
  Filename   : CodeGeneratorVisitor.cc
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 12, Code Generator
  Description: Traverses annotated C- ASTs and generates inefficient but
                 semantically valid assembly code. Hopefully.
*/

/********************************************************************/
// System Includes

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

/********************************************************************/
// Local Includes

#include "CodeGeneratorVisitor.h"

/********************************************************************/
// Using declarations

using std::endl;
using std::to_string;

/********************************************************************/
// Constants

const int INT_SIZE = 4;
const int PARAMETER_BEGIN_OFFSET = 8;

/********************************************************************/
// Class Methods

CodeGeneratorVisitor::CodeGeneratorVisitor (std::ofstream &strm)
  : emitter (strm)
  , inputFunctionReferenced (false)
  , outputFunctionReferenced (false)
  , ebpOffset (0)
  , paramOffset (1)
{}

CodeGeneratorVisitor::~CodeGeneratorVisitor () {}

void
CodeGeneratorVisitor::visit (ProgramNode* node)
{
  emitter.emitSeparator ();
  emitter.emitComment ({"C- Compiled to IA-32 Assembly Instructions", "Compiler v. 0.1.0"});
  emitter.emitSeparator ();

  // function to test for VariableDeclarations
  auto isVariableDeclaration = [] (DeclarationNode* d)
    {
      return d->evalType == ValueType::INT || d->evalType == ValueType::INT_ARRAY;
    };

  // hoist global variable declarations, preserving relative order
  auto fnIter = std::stable_partition (node->children.begin (),
				       node->children.end (),
				       isVariableDeclaration);
  
  // declare variables
  emitter.emitComment ({"Global Variables", ""});
  
  for (auto varIter = node->children.begin (); varIter != fnIter; ++varIter)
    (*varIter)->accept (this);

  emitter.emitSeparator ();
  
  // declare functions
  for (; fnIter != node->children.end (); ++fnIter)
    (*fnIter)->accept (this);

  // emit extern functions as needed
  if (inputFunctionReferenced)
    emitter.emitInputFunction ();
  
  if (outputFunctionReferenced)
    emitter.emitOutputFunction ();
}
  
void
CodeGeneratorVisitor::visit (DeclarationNode* node) {}

void
CodeGeneratorVisitor::visit (FunctionDeclarationNode* node)
{
  int prevEBPOffset = ebpOffset;

  paramOffset = PARAMETER_BEGIN_OFFSET;
  for (ParameterNode* p : node->parameters)
    p->accept (this);

  // declare function
  emitter.emitSeparator ();
  emitter.emitFunctionDeclaration (node->identifier);
  emitter.emitLabel (node->identifier);

  emitter.emitEnter ();
  node->functionBody->accept (this);
  emitter.emitInstruction ("leave");
  emitter.emitInstruction ("ret");

  // reset offset
  ebpOffset = prevEBPOffset;
}

void
CodeGeneratorVisitor::visit (VariableDeclarationNode* node)
{
  if (node->nestLevel == 0)
  { // global variable
    emitter.emitInstruction (".globl", node->identifier);
    emitter.emitInstruction (".data");
    emitter.emitInstruction (".align", "4");
    emitter.emitInstruction (".type", node->identifier + ", @object");
    emitter.emitInstruction (".size", node->identifier + ", " + to_string (INT_SIZE));
    emitter.emitLabel (node->identifier);
    emitter.emitInstruction (".zero", to_string (INT_SIZE));
  }
  else
  {
    emitter.emitInstruction ("subl", "$4, %esp", "allocate local variable " + node->identifier);
    ebpOffset += INT_SIZE;
    node->offset = ebpOffset;
  }
}

void
CodeGeneratorVisitor::visit (ArrayDeclarationNode* node)
{
  if (node->nestLevel == 0)
  { // Global Declaration
    emitter.emitInstruction (".globl", node->identifier);
    emitter.emitInstruction (".data");
    emitter.emitInstruction (".align", "4");
    emitter.emitInstruction (".type", node->identifier + ", @object");
    emitter.emitInstruction (".size", node->identifier + ", " + to_string(INT_SIZE * node->size)); 
    emitter.emitLabel (node->identifier);
    emitter.emitInstruction (".zero", to_string(INT_SIZE * node->size), "initialize to zero");
  }
  else
  {
    emitter.emitInstruction ("subl", "$" + to_string (INT_SIZE*node->size) + ", %esp",
			     "allocate local array " + node->identifier);
    ebpOffset += INT_SIZE * node->size;
    node->offset = ebpOffset;
  }
}

void
CodeGeneratorVisitor::visit (ParameterNode* node)
{
  node->offset = paramOffset;
  paramOffset += INT_SIZE;
  node->isParameter = true;
}

void
CodeGeneratorVisitor::visit (StatementNode* node)
{
}

void
CodeGeneratorVisitor::visit (CompoundStatementNode* node)
{
  emitter.emitComment ("{-> Begin compound statement");

  int prevOffset = ebpOffset;
  
  for (auto l : node->localDeclarations)
    l->accept (this);
  for (auto s : node->statements)
    s->accept (this);

  emitter.emitInstruction ("addl", "$" + to_string (ebpOffset - prevOffset) + ", %esp",
			   "deallocate local variables");
  
  ebpOffset = prevOffset;
  
  emitter.emitComment ("}<- End compound statement");
}

void
CodeGeneratorVisitor::visit (IfStatementNode* node)
{
  string endThenLabel = emitter.createUniqueLabel ();
    
  node->conditionalExpression->accept (this);
  
  emitter.emitInstruction ("cmpl", "$0, %eax", "IF comparison");
  emitter.emitInstruction ("je", endThenLabel);
  emitter.emitComment ("{-> begin THEN");

  // process THEN body
  node->thenStatement->accept (this);

  // process ELSE body
  if (node->elseStatement != nullptr)
  {
    string endElseLabel = emitter.createUniqueLabel ();
    
    emitter.emitInstruction ("jmp", endElseLabel, "}<- end THEN");
    emitter.emitLabel (endThenLabel, "{-> begin ELSE");
    node->elseStatement->accept (this);
    emitter.emitLabel (endElseLabel,"}<- end ELSE");
  }
  else
  {
    emitter.emitLabel (endThenLabel, "}<- end THEN");
  }
}

void
CodeGeneratorVisitor::visit (WhileStatementNode* node)
{
  string beginWhileLabel = emitter.createUniqueLabel (); 
  string endWhileLabel = emitter.createUniqueLabel ();

  // WHILE label
  emitter.emitLabel (beginWhileLabel);
  
  node->conditionalExpression->accept (this);
  emitter.emitInstruction ("cmpl", "$0, %eax", "WHILE comparison");

  emitter.emitInstruction ("je", endWhileLabel);
  emitter.emitComment ("{-> begin WHILE body");

  node->body->accept (this);

  // jump back to WHILE label
  emitter.emitInstruction ("jmp", beginWhileLabel, "}<- end WHILE body");

  // END label
  emitter.emitLabel (endWhileLabel, "exit WHILE");
}

void
CodeGeneratorVisitor::visit (ForStatementNode* node)
{
  emitter.emitComment ("FOR initialization");
  node->initializer->accept (this);

  string beginForLabel = emitter.createUniqueLabel ();
  string endForLabel = emitter.createUniqueLabel ();
  
  // FOR label
  emitter.emitLabel (beginForLabel, "begin FOR loop");

  node->condition->accept (this);
  emitter.emitInstruction ("cmpl", "$0, %eax", "FOR condition");
  
  emitter.emitInstruction ("je", endForLabel);

  emitter.emitComment ("begin FOR body");
  
  node->body->accept (this);

  emitter.emitComment ("end FOR body");
  
  node->updater->accept (this);

  // jump back to FOR label
  emitter.emitInstruction ("jmp", beginForLabel, "return to FOR begin");

  // END label
  emitter.emitLabel (endForLabel, "exit FOR loop");    
}

void
CodeGeneratorVisitor::visit (ReturnStatementNode* node)
{
  if (node->expression != nullptr)
    node->expression->accept (this);
}

void
CodeGeneratorVisitor::visit (ExpressionStatementNode* node)
{
  if (node->expression != nullptr)
    node->expression->accept (this);
}

void
CodeGeneratorVisitor::visit (ExpressionNode* node) {}

void
CodeGeneratorVisitor::visit (AssignmentExpressionNode* node)
{
  emitter.emitComment ("Assignment: begin evaluating rhs");
  node->expression->accept (this);
  emitter.emitInstruction ("pushl", "%eax", "save evaluated value");

  
  node->variable->accept (this);
  
  emitter.emitInstruction ("popl", node->variable->asmReference,
			   "assign rhs value to variable");
  emitter.emitInstruction ("movl", node->variable->asmReference + ", %eax",
			   "place evaluated value in result");
}

void
CodeGeneratorVisitor::visit (AdditiveExpressionNode* node)
{
  emitter.emitComment ("Additive expression: begin evaluating rhs");
  node->right->accept (this);

  emitter.emitInstruction ("pushl", "%eax", "save rhs value while computing lhs");
  
  node->left->accept (this);

  emitter.emitInstruction ("popl", "%ebx", "restore rhs operand");
  emitter.emitInstruction (opString[node->addOperator], "%ebx, %eax",
			   "evaluate additive expression"); 
}

void
CodeGeneratorVisitor::visit (MultiplicativeExpressionNode* node)
{
  emitter.emitComment ("Multiplicative expression: begin evaluating rhs");
  node->right->accept (this);
  
  emitter.emitInstruction ("pushl", "%eax", "save rhs while computing lhs");

  node->left->accept (this);
  
  switch (node->multOperator)
  {
  case MultiplicativeOperatorType::TIMES:
    emitter.emitInstruction ("popl", "%ebx", "restore right operand");
    emitter.emitInstruction ("imul", "%ebx, %eax", "evaluate multiplication");
    break;

  case MultiplicativeOperatorType::DIVIDE:
    emitter.emitInstruction ("popl", "%ebx", "restore divisor");
    emitter.emitInstruction ("cdq", "", "change Double EAX to Quad EDX:EAX");
    emitter.emitComment ("see: http://stackoverflow.com/a/19853558");
    emitter.emitInstruction ("idivl", "%ebx", "divide EDX:EAX by EBX");
    break;
  }
}

void
CodeGeneratorVisitor::visit (RelationalExpressionNode* node)
{
  // evaluate operands
  emitter.emitComment ("relational expression: begin evaluating lhs");
  node->left->accept (this);
  emitter.emitInstruction ("pushl", "%eax", "save lhs while computing rhs");
  node->right->accept (this);
  emitter.emitInstruction ("popl", "%ebx", "restore lhs operand");

  // compare results
  emitter.emitInstruction ("cmpl", "%eax, %ebx", "comparision");
  emitter.emitInstruction (relInstruction[node->relationalOperator], "%al", "relation");

  emitter.emitInstruction ("movzbl", "%al,%eax", "place evaluated value in result");
}

void
CodeGeneratorVisitor::visit (UnaryExpressionNode* node)
{
  emitter.emitComment ("unary operation");
  node->variable->accept (this);
  emitter.emitInstruction (unaryInstruction[node->unaryOperator],
			   node->variable->asmReference,
			   "increment/decrement variable");
  emitter.emitInstruction ("movl", node->variable->asmReference + ", %eax", "pass result");
}

void
CodeGeneratorVisitor::visit (IntegerLiteralExpressionNode* node)
{
  emitter.emitInstruction ("movl", "$" + to_string (node->value) + ", %eax",
			   "integer literal");
}

void
CodeGeneratorVisitor::visit (ReferenceNode* node) {}

void
CodeGeneratorVisitor::visit (VariableExpressionNode* node)
{
  emitter.emitComment ("Loading variable \"" + node->identifier + "\"");
  if (node->declaration->isParameter)
  { // variable is a parameter
    node->asmReference = to_string (node->declaration->offset) + "(%ebp)";
    emitter.emitInstruction ("movl", node->asmReference + ", %eax", "load function parameter value");
  }
  else if (node->declaration->nestLevel == 0)
  { // variable is a global
    
    // if array, pass address
    if (node->evalType == ValueType::INT_ARRAY)
      node->asmReference = "$" + node->identifier;
    else
      node->asmReference = node->identifier;
    
    emitter.emitInstruction ("movl", node->asmReference + ", %eax", "load global value");
  }
  else
  { // local variable
    node->asmReference = "-" + to_string (node->declaration->offset) + "(%ebp)";
    if (node->evalType == ValueType::INT_ARRAY)
    {
      emitter.emitInstruction ("movl", "%ebp, %eax", "prepare to compute array address");
      emitter.emitInstruction ("subl", "$" + to_string (node->declaration->offset) + ", %eax", "load array address");
    }
    else 
      emitter.emitInstruction ("movl", node->asmReference + ", %eax", "load local variable value");
  }
  
}

void
CodeGeneratorVisitor::visit (SubscriptExpressionNode* node)
{
  emitter.emitComment ("Loading subscripted array \"" + node->identifier + "[_]\"");
  node->index->accept (this);
  emitter.emitInstruction ("movl", "%eax, %ebx", "store index value in EBX");

  if (node->declaration->isParameter)
  { // array was pass as a parameter
    emitter.emitInstruction ("movl", "%ebp, %eax");
    emitter.emitInstruction ("addl", "$" + to_string (node->declaration->offset) + ", %eax");
    emitter.emitInstruction ("movl", "(%eax), %eax"); 
    emitter.emitInstruction ("leal", "(%eax,%ebx,4), %ebx", "compute address");
    node->asmReference = "(%ebx)";
  }
  else if (node->declaration->nestLevel == 0)
  {
    // global array
    node->asmReference = node->identifier + "(,%ebx,4)";
  }
  else
  {
    emitter.emitInstruction ("movl", "%ebp, %eax");
    emitter.emitInstruction ("subl", "$" + to_string (node->declaration->offset) + ", %eax");
    emitter.emitInstruction ("leal", "(%eax,%ebx,4), %ebx", "compute address");
    node->asmReference = "(%ebx)";
  }

  emitter.emitInstruction ("movl", node->asmReference + ", %eax", "load value into EAX");
}

void
CodeGeneratorVisitor::visit (CallExpressionNode* node)
{
  // flag any uses of external methods
  inputFunctionReferenced = inputFunctionReferenced ||
    node->declaration->identifier == "input";

  outputFunctionReferenced = outputFunctionReferenced ||
    node->declaration->identifier == "output";

  // push arguments on stack in reverse order
  for (auto rit = node->arguments.rbegin (); rit != node->arguments.rend (); ++rit)
  {
    (*rit)->accept (this);
    emitter.emitInstruction ("pushl", "%eax", "push function argument onto stack");
  }

  emitter.emitInstruction ("call", node->declaration->identifier,
			   "invoke function");
  emitter.emitInstruction ("addl", "$" + to_string (4*node->arguments.size ()) +
			   ", %esp", "remove arguments from stack");
}
