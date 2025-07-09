
// Generated from Stc.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "StcParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by StcParser.
 */
class  StcListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(StcParser::ProgContext *ctx) = 0;
  virtual void exitProg(StcParser::ProgContext *ctx) = 0;

  virtual void enterFunctionDef(StcParser::FunctionDefContext *ctx) = 0;
  virtual void exitFunctionDef(StcParser::FunctionDefContext *ctx) = 0;

  virtual void enterType(StcParser::TypeContext *ctx) = 0;
  virtual void exitType(StcParser::TypeContext *ctx) = 0;

  virtual void enterStatement(StcParser::StatementContext *ctx) = 0;
  virtual void exitStatement(StcParser::StatementContext *ctx) = 0;

  virtual void enterBlock(StcParser::BlockContext *ctx) = 0;
  virtual void exitBlock(StcParser::BlockContext *ctx) = 0;

  virtual void enterNewStructAssign(StcParser::NewStructAssignContext *ctx) = 0;
  virtual void exitNewStructAssign(StcParser::NewStructAssignContext *ctx) = 0;

  virtual void enterNewOperator(StcParser::NewOperatorContext *ctx) = 0;
  virtual void exitNewOperator(StcParser::NewOperatorContext *ctx) = 0;

  virtual void enterStruct(StcParser::StructContext *ctx) = 0;
  virtual void exitStruct(StcParser::StructContext *ctx) = 0;

  virtual void enterStructElement(StcParser::StructElementContext *ctx) = 0;
  virtual void exitStructElement(StcParser::StructElementContext *ctx) = 0;

  virtual void enterStructBody(StcParser::StructBodyContext *ctx) = 0;
  virtual void exitStructBody(StcParser::StructBodyContext *ctx) = 0;

  virtual void enterIfBlock(StcParser::IfBlockContext *ctx) = 0;
  virtual void exitIfBlock(StcParser::IfBlockContext *ctx) = 0;

  virtual void enterElseBlock(StcParser::ElseBlockContext *ctx) = 0;
  virtual void exitElseBlock(StcParser::ElseBlockContext *ctx) = 0;

  virtual void enterRepeatBlock(StcParser::RepeatBlockContext *ctx) = 0;
  virtual void exitRepeatBlock(StcParser::RepeatBlockContext *ctx) = 0;

  virtual void enterArguments(StcParser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(StcParser::ArgumentsContext *ctx) = 0;

  virtual void enterOperation(StcParser::OperationContext *ctx) = 0;
  virtual void exitOperation(StcParser::OperationContext *ctx) = 0;

  virtual void enterOperaor(StcParser::OperaorContext *ctx) = 0;
  virtual void exitOperaor(StcParser::OperaorContext *ctx) = 0;

  virtual void enterStackOperation(StcParser::StackOperationContext *ctx) = 0;
  virtual void exitStackOperation(StcParser::StackOperationContext *ctx) = 0;

  virtual void enterPush(StcParser::PushContext *ctx) = 0;
  virtual void exitPush(StcParser::PushContext *ctx) = 0;

  virtual void enterArrayElement(StcParser::ArrayElementContext *ctx) = 0;
  virtual void exitArrayElement(StcParser::ArrayElementContext *ctx) = 0;

  virtual void enterArrayBase(StcParser::ArrayBaseContext *ctx) = 0;
  virtual void exitArrayBase(StcParser::ArrayBaseContext *ctx) = 0;

  virtual void enterArrayIndexShift(StcParser::ArrayIndexShiftContext *ctx) = 0;
  virtual void exitArrayIndexShift(StcParser::ArrayIndexShiftContext *ctx) = 0;

  virtual void enterArrayIndex(StcParser::ArrayIndexContext *ctx) = 0;
  virtual void exitArrayIndex(StcParser::ArrayIndexContext *ctx) = 0;

  virtual void enterCapacity(StcParser::CapacityContext *ctx) = 0;
  virtual void exitCapacity(StcParser::CapacityContext *ctx) = 0;

  virtual void enterArray(StcParser::ArrayContext *ctx) = 0;
  virtual void exitArray(StcParser::ArrayContext *ctx) = 0;

  virtual void enterArrayDescriber(StcParser::ArrayDescriberContext *ctx) = 0;
  virtual void exitArrayDescriber(StcParser::ArrayDescriberContext *ctx) = 0;

  virtual void enterArrayNew(StcParser::ArrayNewContext *ctx) = 0;
  virtual void exitArrayNew(StcParser::ArrayNewContext *ctx) = 0;

  virtual void enterArgument(StcParser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(StcParser::ArgumentContext *ctx) = 0;

  virtual void enterVarAssign(StcParser::VarAssignContext *ctx) = 0;
  virtual void exitVarAssign(StcParser::VarAssignContext *ctx) = 0;

  virtual void enterVarAssignIdentifier(StcParser::VarAssignIdentifierContext *ctx) = 0;
  virtual void exitVarAssignIdentifier(StcParser::VarAssignIdentifierContext *ctx) = 0;

  virtual void enterVarType(StcParser::VarTypeContext *ctx) = 0;
  virtual void exitVarType(StcParser::VarTypeContext *ctx) = 0;

  virtual void enterVarReference(StcParser::VarReferenceContext *ctx) = 0;
  virtual void exitVarReference(StcParser::VarReferenceContext *ctx) = 0;

  virtual void enterVarIdentifier(StcParser::VarIdentifierContext *ctx) = 0;
  virtual void exitVarIdentifier(StcParser::VarIdentifierContext *ctx) = 0;

  virtual void enterIdentifier(StcParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(StcParser::IdentifierContext *ctx) = 0;


};

