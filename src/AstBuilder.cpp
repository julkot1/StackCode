//
// Created by julian on 7/4/25.
//

#include "AstBuilder.h"

#include <functional>

#include "error.h"

void AstBuilder::enterFunctionDef(StcParser::FunctionDefContext *ctx)
{
    auto function = std::make_unique<stc::Function>();
    function->name =  ctx->ID()->getText();
    std::unordered_set<std::string> seen;
    if (ctx->arguments() != nullptr)
    {
        for (auto argAntlr : ctx->arguments()->argument())
        {
            auto arg = std::make_unique<stc::Var>();
            arg->name = argAntlr->ID()->getText();
            auto [_, inserted] = seen.insert(arg->name);
            if (!inserted)
            {
                auto line = getWholeLine(argAntlr->start);
                auto num = argAntlr->start->getLine();
                auto msg ="argument "+argAntlr->ID()->getText()+" already exists!";
                auto name = "app.rpn";
                 throw ParserError(name, line, num, msg);
            }
        }
    }

    functionStack.push(std::move(function));
}

void AstBuilder::exitFunctionDef(StcParser::FunctionDefContext *ctx)
{
    auto function = std::move(functionStack.top());
    functionStack.pop();

    while (!blockStack.empty())
    {
        function->blocks.push_back(std::move(blockStack.top()));
        blockStack.pop();
    }
    std::reverse(function->blocks.begin(), function->blocks.end());
    program.functions[function->name] = std::move(function);
}



void AstBuilder::exitStruct(StcParser::StructContext *ctx)
{
    auto structure = std::make_unique<stc::Struct>();
    structure->name =  ctx->ID()->getText();
    std::unordered_set<std::string> seen;

    for (auto field : ctx->structBody()->structElement())
    {
        auto fieldVar = std::make_unique<stc::Var>();
        fieldVar->name =  field->ID()->getText();
        structure->fields.push_back(std::move(fieldVar));

        auto [_, inserted] = seen.insert(field->ID()->getText());
        if (!inserted)
        {
            auto line = getWholeLine(field->start);
            auto num = field->start->getLine();
            auto msg ="field "+field->ID()->getText()+" already exists!";
            auto name = "app.rpn";
            throw ParserError(name, line, num, msg);
        }
    }
    program.structs[structure->name] = std::move(structure);
}

void AstBuilder::exitBlock(StcParser::BlockContext *ctx)
{
    auto currentBlock = std::move(blockStack.top());
    blockStack.pop();

    if (!blockStack.empty())
    {
        auto& parentBlock = blockStack.top();

        if (!parentBlock->operations.empty())
        {
            auto& lastOp = parentBlock->operations.back();

            // Check if it's an IfStatement
            if (auto* rawIf = dynamic_cast<stc::IfStatement*>(lastOp.get()))
            {
                if (!rawIf->trueBlock)
                {
                    rawIf->trueBlock = std::move(currentBlock);
                    return;
                }
                if (!rawIf->falseBlock)
                {
                    rawIf->isElse = true;
                    rawIf->falseBlock = std::move(currentBlock);
                    return;
                }
            }
            //Check if it's a RepeatStatement
            else if (auto* rawRepeat = dynamic_cast<stc::RepeatStatement*>(lastOp.get()))
            {
                rawRepeat->LoopBlock = std::move(currentBlock);
            }
        }

        // Otherwise, just a normal nested block
        parentBlock->blocks.push_back(std::move(currentBlock));
    }
    else
    {
        // Top-level block (should not usually happen here)
        blockStack.push(std::move(currentBlock));
    }
}
void AstBuilder::enterBlock(StcParser::BlockContext *ctx)
{
    auto block = std::make_unique<stc::Block>();
    block->name = functionStack.top()->getBlockIndex();
    blockStack.push(std::move(block));
}

void AstBuilder::enterPush(StcParser::PushContext *ctx)
{
    auto stackOperation = std::make_unique<stc::PushOperation>(ctx);
    blockStack.top()->operations.push_back(std::move(stackOperation));
}


void AstBuilder::enterIfBlock(StcParser::IfBlockContext *ctx)
{
    auto IfStatement = std::make_unique<stc::IfStatement>();
    blockStack.top()->operations.push_back(std::move(IfStatement));
}

void AstBuilder::enterRepeatBlock(StcParser::RepeatBlockContext *ctx)
{
    auto RepeatStatement = std::make_unique<stc::RepeatStatement>();
    blockStack.top()->operations.push_back(std::move(RepeatStatement));
}

void AstBuilder::enterStackOperation(StcParser::StackOperationContext *ctx)
{
    auto stackOperation = std::make_unique<stc::StackOperation>(ctx);
    blockStack.top()->operations.push_back(std::move(stackOperation));
}
void AstBuilder::enterOperaor(StcParser::OperaorContext *ctx)
{
    auto operation = std::make_unique<stc::Operator>(ctx);
    blockStack.top()->operations.push_back(std::move(operation));
}

void AstBuilder::enterIdentifier(StcParser::IdentifierContext *ctx)
{
    auto id = std::make_unique<stc::Identifier>(ctx);
    blockStack.top()->operations.push_back(std::move(id));

}

void AstBuilder::enterProg(StcParser::ProgContext *ctx)
{
}
