//
// Created by julian on 7/4/25.
//

#ifndef ASTBUILDER_H
#define ASTBUILDER_H
#include "Program.h"
#include "antlr/StcBaseListener.h"



class AstBuilder : public StcBaseListener {

    std::stack<std::unique_ptr<stc::Block>> blockStack;
    std::stack<stc::Block*> subBlockParents;


    std::stack<std::unique_ptr<stc::Function>> functionStack;
    std::unordered_set<std::string> seenIdentifier;
public:
    stc::Program program;

    void enterProg(StcParser::ProgContext *ctx) override;

    void exitBlock(StcParser::BlockContext *ctx) override;
    void enterBlock(StcParser::BlockContext *ctx) override;

    void enterFunctionDef(StcParser::FunctionDefContext *ctx) override;
    void exitFunctionDef(StcParser::FunctionDefContext *ctx) override;

    void exitStruct(StcParser::StructContext *ctx) override;

    void enterPush(StcParser::PushContext *ctx) override;

    void enterIfBlock(StcParser::IfBlockContext *ctx) override;

    void enterRepeatBlock(StcParser::RepeatBlockContext *ctx) override;

    void enterStackOperation(StcParser::StackOperationContext *ctx) override;

    void enterOperaor(StcParser::OperaorContext *ctx) override;

    void enterIdentifier(StcParser::IdentifierContext *ctx) override;

};



#endif //ASTBUILDER_H
