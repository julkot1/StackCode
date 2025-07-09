//
// Created by julian on 7/4/25.
//

#include "Program.h"

#include <llvm/IR/Intrinsics.h>

namespace stc
{
    std::string Function::getBlockIndex()
    {
        return BLOCK_NAME + std::to_string(this->blockIndex++) + "df";
    }


    PushOperation::PushOperation(StcParser::PushContext *ctx)
    {
        this->token = ctx->getText();
        this->stackOperation = getType(ctx);
        this->type = PUSH_OPERATION;
    }

    PushOperationType PushOperation::getType(StcParser::PushContext* ctx)
    {
        if (ctx->SIGNED_NUMBER())    return PUSH_SIGNED_I64;
        if (ctx->NUMBER())           return PUSH_I64;
        if (ctx->SIGNED_FLOAT())     return PUSH_SIGNED_F64;
        if (ctx->FLOAT())            return PUSH_F64;
        if (ctx->SIGNED_FLOAT_E())   return PUSH_SIGNED_F64_E;
        if (ctx->FLOAT_E())          return PUSH_F64_E;
        if (ctx->BIN_NUMBER())       return PUSH_BIN_I64;
        if (ctx->HEX_NUMBER())       return PUSH_HEX_I64;
        if (ctx->CHAR())             return PUSH_I8;
        if (ctx->STRING())           return PUSH_STR;
        if (ctx->BOOL())             return PUSH_BOOL;
        if (ctx->SIMPLE_TYPE())      return PUSH_SIMPLE_TYPE;

        return PUSH_IDENTIFIER;
    }

    StackOperation::StackOperation(StcParser::StackOperationContext *ctx)
    {
        this->token = ctx->getText();
        this->stackOperation = getType(ctx);
        this->type = STACK_OPERATION;
    }


    StackOperationType StackOperation::getType(StcParser::StackOperationContext* ctx)
    {

        const auto str = ctx->getText();
        if (auto it = stringToStackOp.find(str); it != stringToStackOp.end()) {
            return it->second;
        }
        throw std::invalid_argument("Unknown stack operation: " + str);
    }

    Operator::Operator(StcParser::OperaorContext *ctx) {
        type = STACK_OPERATION;
        token = ctx->getText();
        operatorType = getType(ctx);
    }
    OperatorType Operator::getType(StcParser::OperaorContext *ctx) {
        std::string str = ctx->getText(); // or ctx->op->getText() if labeled
        static const std::unordered_map<std::string, OperatorType> map = {
            // Logic
            {"<=", OPERATOR_LE},
            {">=", OPERATOR_GE},
            {"!=", OPERATOR_NE},
            {"==", OPERATOR_EQ},
            {"<",  OPERATOR_LT},
            {">",  OPERATOR_GT},
            {"and", OPERATOR_AND},
            {"or",  OPERATOR_OR},
            {"not", OPERATOR_NOT},

            // Arithmetic
            {"+", OPERATOR_ADD},
            {"-", OPERATOR_SUB},
            {"*", OPERATOR_MUL},
            {"/", OPERATOR_DIV},
            {"%", OPERATOR_MOD},

            // Assign
            {":=", OPERATOR_ASSIGN},

            // Built-in
            {"typeof", OPERATOR_TYPEOF},
            {"len",    OPERATOR_LEN},
            {"call",   OPERATOR_CALL},
            {"copy",   OPERATOR_COPY}
        };

        auto it = map.find(str);
        if (it != map.end()) {
            return it->second;
        }
    }



}
