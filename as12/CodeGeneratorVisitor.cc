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

/********************************************************************/
// Local Includes

#include "CodeGeneratorVisitor.h"

/********************************************************************/
// Using declarations

using std::endl;
using std::to_string;

/********************************************************************/
// Class Methods

CodeGeneratorVisitor::CodeGeneratorVisitor (std::ofstream &strm) : emitter (strm) {}

CodeGeneratorVisitor::~CodeGeneratorVisitor () {}

void
CodeGeneratorVisitor::emitInputFunction ()
{
  emitter.emitSeparator ();

  emitter.emitComment ("Conversion string");
  emitter.emitInstruction (".section", ".rodata");
  emitter.emitConstDeclaration (".inStr", ".string", "\"%d\"");
  
  emitter.emitSeparator ();
  
  emitter.emitComment ("Input Routine");
  emitter.emitFunctionDeclaration ("input");
  emitter.emitLabel ("input");

  emitter.emitEnter ();

  emitter.emitInstruction ("subl", "$4, %esp", "create slot for result");
  emitter.emitInstruction ("pushl", "%esp", "push slot's address");
  emitter.emitInstruction ("pushl", "$.inStr", "push conversion spec");
  emitter.emitInstruction ("call", "scanf", "read an integer");
  emitter.emitInstruction ("movl", "8(%esp), %eax", "move int to %eax");

  emitter.emitInstruction ("leave", "", "reset stack & frame pointers");
  emitter.emitInstruction ("ret", "", "return to caller");
}

void
CodeGeneratorVisitor::emitOutputFunction ()
{
  emitter.emitSeparator ();

  emitter.emitComment ("Conversion string");
  emitter.emitInstruction (".section", ".rodata");
  emitter.emitConstDeclaration (".outStr", ".string", "\"%d\\n\"");
  
  emitter.emitSeparator ();

  emitter.emitComment ("Output Routine");
  emitter.emitFunctionDeclaration ("output");

  emitter.emitLabel ("output");

  emitter.emitEnter ();

  emitter.emitInstruction ("pushl", "8(%ebp)", "retrieve the integer to output");
  emitter.emitInstruction ("pushl", "$.outStr", "push conversion spec");
  emitter.emitInstruction ("call", "printf", "call printf");
  
  emitter.emitInstruction ("leave", "", "reset stack & frame pointers");
  emitter.emitInstruction ("ret", "", "return to caller");
}

void
CodeGeneratorVisitor::visit (ProgramNode* node)
{
  emitter.emitSeparator ();
  emitter.emitComment ({"C- Compiled to IA-32 Code", "", "Compiler v. 0.1.0"});
  emitter.emitSeparator ();

  
  for (DeclarationNode* d : node->children)
    d->accept (this);

  // emit extern functions as needed
  if (inputFunctionReferenced)
    emitInputFunction ();
  
  if (outputFunctionReferenced)
    emitOutputFunction ();
}
  
void
CodeGeneratorVisitor::visit (DeclarationNode* node)
{
  
}

void
CodeGeneratorVisitor::visit (FunctionDeclarationNode* node)
{  
  for (ParameterNode* p : node->parameters)
    p->accept (this);

  emitter.emitSeparator ();
  emitter.emitFunctionDeclaration (node->identifier);
  emitter.emitLabel (node->identifier);

  emitter.emitEnter ();
  
  node->functionBody->accept (this);

  emitter.emitInstruction ("leave");
  emitter.emitInstruction ("ret");
}

void
CodeGeneratorVisitor::visit (VariableDeclarationNode* node)
{
}

void
CodeGeneratorVisitor::visit (ArrayDeclarationNode* node)
{
}

void
CodeGeneratorVisitor::visit (ParameterNode* node)
{
  if (node->isArray)
    emitter.emitComment ("array");
}

void
CodeGeneratorVisitor::visit (StatementNode* node)
{
}

void
CodeGeneratorVisitor::visit (CompoundStatementNode* node)
{
  for (auto l : node->localDeclarations)
    l->accept (this);
  for (auto s : node->statements)
    s->accept (this);
}

void
CodeGeneratorVisitor::visit (IfStatementNode* node)
{
  node->conditionalExpression->accept (this);
  node->thenStatement->accept (this);
  if (node->elseStatement != nullptr)
    node->elseStatement->accept (this);
}

void
CodeGeneratorVisitor::visit (WhileStatementNode* node)
{
  node->conditionalExpression->accept (this);
  node->body->accept (this);
}

void
CodeGeneratorVisitor::visit (ForStatementNode* node)
{
  node->initializer->accept (this);
  node->condition->accept (this);
  node->updater->accept (this);
  node->body->accept (this);
}

void
CodeGeneratorVisitor::visit (ReturnStatementNode* node)
{
  if (node->expression != nullptr)
  {
    node->expression->accept (this);
  }
}

void
CodeGeneratorVisitor::visit (ExpressionStatementNode* node)
{
  if (node->expression != nullptr)
  {
    node->expression->accept (this);
  }
}

void
CodeGeneratorVisitor::visit (ExpressionNode* node)
{
}

void
CodeGeneratorVisitor::visit (AssignmentExpressionNode* node)
{
  node->variable->accept (this);
  node->expression->accept (this);
}

void
CodeGeneratorVisitor::visit (AdditiveExpressionNode* node)
{
  node->left->accept (this);

  emitter.emitInstruction ("pushl", "%eax", "push left operand to stack");
  
  node->right->accept (this);

  emitter.emitInstruction ("popl", "%ebx", "pop left operand to EBX");
  emitter.emitInstruction (opString[node->addOperator], "%ebx, %eax",
			   "evaluate additive expression"); 
}

void
CodeGeneratorVisitor::visit (MultiplicativeExpressionNode* node)
{
  node->right->accept (this);
  
  emitter.emitInstruction ("pushl", "%eax", "push right operand to stack");

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
  switch (node->relationalOperator)
  {
  case RelationalOperatorType::EQ:
    emitter.emitComment ("equals");
    break;
  case RelationalOperatorType::NEQ:
    emitter.emitComment ("not equals");
    break;
  case RelationalOperatorType::LT:
    emitter.emitComment ("less than");
    break;
  case RelationalOperatorType::LTE:
    emitter.emitComment ("less than or equal to");
    break;
  case RelationalOperatorType::GT:
    emitter.emitComment ("greater than");
    break;
  case RelationalOperatorType::GTE:
    emitter.emitComment ("greater than or equal to");
    break;
  }

  node->left->accept (this);
  node->right->accept (this);
}

void
CodeGeneratorVisitor::visit (UnaryExpressionNode* node)
{

  switch (node->unaryOperator)
  {
  case UnaryOperatorType::INCREMENT:
    emitter.emitComment ("++");
    break;
  case UnaryOperatorType::DECREMENT:
    emitter.emitComment ("--");
    break;
  }
  
  node->variable->accept (this);
}

void
CodeGeneratorVisitor::visit (IntegerLiteralExpressionNode* node)
{
  emitter.emitInstruction ("movl", "$" + to_string (node->value) + ", %eax",
			   "integer literal");
}

void
CodeGeneratorVisitor::visit (ReferenceNode* node)
{
}

void
CodeGeneratorVisitor::visit (VariableExpressionNode* node)
{
}

void
CodeGeneratorVisitor::visit (SubscriptExpressionNode* node)
{
  node->index->accept (this);
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
}
