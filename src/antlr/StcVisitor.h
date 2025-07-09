
// Generated from Stc.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "StcParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by StcParser.
 */
class  StcVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by StcParser.
   */
    virtual std::any visitProg(StcParser::ProgContext *context) = 0;

    virtual std::any visitFunctionDef(StcParser::FunctionDefContext *context) = 0;

    virtual std::any visitType(StcParser::TypeContext *context) = 0;

    virtual std::any visitStatement(StcParser::StatementContext *context) = 0;

    virtual std::any visitBlock(StcParser::BlockContext *context) = 0;

    virtual std::any visitNewStructAssign(StcParser::NewStructAssignContext *context) = 0;

    virtual std::any visitNewOperator(StcParser::NewOperatorContext *context) = 0;

    virtual std::any visitStruct(StcParser::StructContext *context) = 0;

    virtual std::any visitStructElement(StcParser::StructElementContext *context) = 0;

    virtual std::any visitStructBody(StcParser::StructBodyContext *context) = 0;

    virtual std::any visitIfBlock(StcParser::IfBlockContext *context) = 0;

    virtual std::any visitElseBlock(StcParser::ElseBlockContext *context) = 0;

    virtual std::any visitRepeatBlock(StcParser::RepeatBlockContext *context) = 0;

    virtual std::any visitArguments(StcParser::ArgumentsContext *context) = 0;

    virtual std::any visitOperation(StcParser::OperationContext *context) = 0;

    virtual std::any visitOperaor(StcParser::OperaorContext *context) = 0;

    virtual std::any visitStackOperation(StcParser::StackOperationContext *context) = 0;

    virtual std::any visitPush(StcParser::PushContext *context) = 0;

    virtual std::any visitArrayElement(StcParser::ArrayElementContext *context) = 0;

    virtual std::any visitArrayBase(StcParser::ArrayBaseContext *context) = 0;

    virtual std::any visitArrayIndexShift(StcParser::ArrayIndexShiftContext *context) = 0;

    virtual std::any visitArrayIndex(StcParser::ArrayIndexContext *context) = 0;

    virtual std::any visitCapacity(StcParser::CapacityContext *context) = 0;

    virtual std::any visitArray(StcParser::ArrayContext *context) = 0;

    virtual std::any visitArrayDescriber(StcParser::ArrayDescriberContext *context) = 0;

    virtual std::any visitArrayNew(StcParser::ArrayNewContext *context) = 0;

    virtual std::any visitArgument(StcParser::ArgumentContext *context) = 0;

    virtual std::any visitVarAssign(StcParser::VarAssignContext *context) = 0;

    virtual std::any visitVarAssignIdentifier(StcParser::VarAssignIdentifierContext *context) = 0;

    virtual std::any visitVarType(StcParser::VarTypeContext *context) = 0;

    virtual std::any visitVarReference(StcParser::VarReferenceContext *context) = 0;

    virtual std::any visitVarIdentifier(StcParser::VarIdentifierContext *context) = 0;

    virtual std::any visitIdentifier(StcParser::IdentifierContext *context) = 0;


};

