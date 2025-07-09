
// Generated from Stc.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "StcListener.h"


/**
 * This class provides an empty implementation of StcListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  StcBaseListener : public StcListener {
public:

  virtual void enterProg(StcParser::ProgContext * /*ctx*/) override { }
  virtual void exitProg(StcParser::ProgContext * /*ctx*/) override { }

  virtual void enterFunctionDef(StcParser::FunctionDefContext * /*ctx*/) override { }
  virtual void exitFunctionDef(StcParser::FunctionDefContext * /*ctx*/) override { }

  virtual void enterType(StcParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(StcParser::TypeContext * /*ctx*/) override { }

  virtual void enterStatement(StcParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(StcParser::StatementContext * /*ctx*/) override { }

  virtual void enterBlock(StcParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(StcParser::BlockContext * /*ctx*/) override { }

  virtual void enterNewStructAssign(StcParser::NewStructAssignContext * /*ctx*/) override { }
  virtual void exitNewStructAssign(StcParser::NewStructAssignContext * /*ctx*/) override { }

  virtual void enterNewOperator(StcParser::NewOperatorContext * /*ctx*/) override { }
  virtual void exitNewOperator(StcParser::NewOperatorContext * /*ctx*/) override { }

  virtual void enterStruct(StcParser::StructContext * /*ctx*/) override { }
  virtual void exitStruct(StcParser::StructContext * /*ctx*/) override { }

  virtual void enterStructElement(StcParser::StructElementContext * /*ctx*/) override { }
  virtual void exitStructElement(StcParser::StructElementContext * /*ctx*/) override { }

  virtual void enterStructBody(StcParser::StructBodyContext * /*ctx*/) override { }
  virtual void exitStructBody(StcParser::StructBodyContext * /*ctx*/) override { }

  virtual void enterIfBlock(StcParser::IfBlockContext * /*ctx*/) override { }
  virtual void exitIfBlock(StcParser::IfBlockContext * /*ctx*/) override { }

  virtual void enterElseBlock(StcParser::ElseBlockContext * /*ctx*/) override { }
  virtual void exitElseBlock(StcParser::ElseBlockContext * /*ctx*/) override { }

  virtual void enterRepeatBlock(StcParser::RepeatBlockContext * /*ctx*/) override { }
  virtual void exitRepeatBlock(StcParser::RepeatBlockContext * /*ctx*/) override { }

  virtual void enterArguments(StcParser::ArgumentsContext * /*ctx*/) override { }
  virtual void exitArguments(StcParser::ArgumentsContext * /*ctx*/) override { }

  virtual void enterOperation(StcParser::OperationContext * /*ctx*/) override { }
  virtual void exitOperation(StcParser::OperationContext * /*ctx*/) override { }

  virtual void enterOperaor(StcParser::OperaorContext * /*ctx*/) override { }
  virtual void exitOperaor(StcParser::OperaorContext * /*ctx*/) override { }

  virtual void enterStackOperation(StcParser::StackOperationContext * /*ctx*/) override { }
  virtual void exitStackOperation(StcParser::StackOperationContext * /*ctx*/) override { }

  virtual void enterPush(StcParser::PushContext * /*ctx*/) override { }
  virtual void exitPush(StcParser::PushContext * /*ctx*/) override { }

  virtual void enterArrayElement(StcParser::ArrayElementContext * /*ctx*/) override { }
  virtual void exitArrayElement(StcParser::ArrayElementContext * /*ctx*/) override { }

  virtual void enterArrayBase(StcParser::ArrayBaseContext * /*ctx*/) override { }
  virtual void exitArrayBase(StcParser::ArrayBaseContext * /*ctx*/) override { }

  virtual void enterArrayIndexShift(StcParser::ArrayIndexShiftContext * /*ctx*/) override { }
  virtual void exitArrayIndexShift(StcParser::ArrayIndexShiftContext * /*ctx*/) override { }

  virtual void enterArrayIndex(StcParser::ArrayIndexContext * /*ctx*/) override { }
  virtual void exitArrayIndex(StcParser::ArrayIndexContext * /*ctx*/) override { }

  virtual void enterCapacity(StcParser::CapacityContext * /*ctx*/) override { }
  virtual void exitCapacity(StcParser::CapacityContext * /*ctx*/) override { }

  virtual void enterArray(StcParser::ArrayContext * /*ctx*/) override { }
  virtual void exitArray(StcParser::ArrayContext * /*ctx*/) override { }

  virtual void enterArrayDescriber(StcParser::ArrayDescriberContext * /*ctx*/) override { }
  virtual void exitArrayDescriber(StcParser::ArrayDescriberContext * /*ctx*/) override { }

  virtual void enterArrayNew(StcParser::ArrayNewContext * /*ctx*/) override { }
  virtual void exitArrayNew(StcParser::ArrayNewContext * /*ctx*/) override { }

  virtual void enterArgument(StcParser::ArgumentContext * /*ctx*/) override { }
  virtual void exitArgument(StcParser::ArgumentContext * /*ctx*/) override { }

  virtual void enterVarAssign(StcParser::VarAssignContext * /*ctx*/) override { }
  virtual void exitVarAssign(StcParser::VarAssignContext * /*ctx*/) override { }

  virtual void enterVarAssignIdentifier(StcParser::VarAssignIdentifierContext * /*ctx*/) override { }
  virtual void exitVarAssignIdentifier(StcParser::VarAssignIdentifierContext * /*ctx*/) override { }

  virtual void enterVarType(StcParser::VarTypeContext * /*ctx*/) override { }
  virtual void exitVarType(StcParser::VarTypeContext * /*ctx*/) override { }

  virtual void enterVarReference(StcParser::VarReferenceContext * /*ctx*/) override { }
  virtual void exitVarReference(StcParser::VarReferenceContext * /*ctx*/) override { }

  virtual void enterVarIdentifier(StcParser::VarIdentifierContext * /*ctx*/) override { }
  virtual void exitVarIdentifier(StcParser::VarIdentifierContext * /*ctx*/) override { }

  virtual void enterIdentifier(StcParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(StcParser::IdentifierContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

