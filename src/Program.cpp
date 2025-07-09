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


    StackOperation::StackOperation(StcParser::PushContext *ctx)
    {
        this->token = ctx->getText();
        this->stackOperation = getType(ctx);
        this->type = STACK_OPERATION;
    }

    StackOperationType StackOperation::getType(StcParser::PushContext* ctx)
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
}
