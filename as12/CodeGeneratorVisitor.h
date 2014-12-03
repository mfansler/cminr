/*
  Filename   : CodeGeneratorVisitor.h
  Author     : Merv Fansler
  Course     : CSCI 435
  Assignment : Assignment 12, Code Generator
  Description: Traverses annotated C- ASTs and generates inefficient but
                 semantically valid assembly code. Hopefully.
*/

/********************************************************************/
// System Includes

#include <string>
#include <fstream>
#include <map>

/********************************************************************/
// Local Includes

#include "CMinusAst.h"
#include "AssemblyEmitter.h"

/********************************************************************/
// Class Definition

class CodeGeneratorVisitor : public IVisitor
{
  AssemblyEmitter emitter;
  std::map<ValueType, std::string> vtString =
    {
      {	ValueType::INT          , "Int type"           },
      {	ValueType::VOID         , "Void type"          },
      { ValueType::INT_ARRAY    , "Int Array type"     },
      { ValueType::VOID_ARRAY   , "Void Array type"    },
      { ValueType::INT_FUNCTION , "Int Function type"  },
      { ValueType::VOID_FUNCTION, "Void Function type" }
    };

public:
  CodeGeneratorVisitor (std::ofstream &strm);
  ~CodeGeneratorVisitor ();
  
  void visit (ProgramNode* node);

  void visit (DeclarationNode* node);
  void visit (FunctionDeclarationNode* node);
  void visit (VariableDeclarationNode* node);
  void visit (ArrayDeclarationNode* node);
  void visit (ParameterNode* node);

  void visit (StatementNode* node);
  void visit (CompoundStatementNode* node);
  void visit (IfStatementNode* node);
  void visit (WhileStatementNode* node);
  void visit (ForStatementNode* node);
  void visit (ReturnStatementNode* node);
  void visit (ExpressionStatementNode* node);

  void visit (ExpressionNode* node);
  void visit (AssignmentExpressionNode* node);
  void visit (AdditiveExpressionNode* node);
  void visit (MultiplicativeExpressionNode* node);
  void visit (RelationalExpressionNode* node);
  void visit (UnaryExpressionNode* node);
  void visit (IntegerLiteralExpressionNode* node);

  void visit (ReferenceNode* node);
  void visit (VariableExpressionNode* node);
  void visit (SubscriptExpressionNode* node);
  void visit (CallExpressionNode* node);
};
