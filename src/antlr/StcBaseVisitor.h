
// Generated from Stc.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "StcVisitor.h"


/**
 * This class provides an empty implementation of StcVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  StcBaseVisitor : public StcVisitor {
public:

  virtual std::any visitProg(StcParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDef(StcParser::FunctionDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(StcParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(StcParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(StcParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewStructAssign(StcParser::NewStructAssignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewOperator(StcParser::NewOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStruct(StcParser::StructContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructElement(StcParser::StructElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructBody(StcParser::StructBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfBlock(StcParser::IfBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElseBlock(StcParser::ElseBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRepeatBlock(StcParser::RepeatBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(StcParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperation(StcParser::OperationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperaor(StcParser::OperaorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStackOperation(StcParser::StackOperationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPush(StcParser::PushContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayElement(StcParser::ArrayElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayBase(StcParser::ArrayBaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayIndexShift(StcParser::ArrayIndexShiftContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayIndex(StcParser::ArrayIndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCapacity(StcParser::CapacityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray(StcParser::ArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayDescriber(StcParser::ArrayDescriberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayNew(StcParser::ArrayNewContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument(StcParser::ArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarAssign(StcParser::VarAssignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarAssignIdentifier(StcParser::VarAssignIdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarType(StcParser::VarTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarReference(StcParser::VarReferenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarIdentifier(StcParser::VarIdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(StcParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }


};

