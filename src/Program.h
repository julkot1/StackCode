//
// Created by julian on 7/4/25.
//

#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>
#include <string>
#include <vector>
#include <map>

#include <llvm/IR/Value.h>
#include "Type.h"
#include "antlr/StcParser.h"

namespace stc
{


    const std::string BLOCK_NAME     = "block";



    enum NodeType
    {
        STACK_OPERATION,
        PUSH_OPERATION,
        IF_STATEMENT,
        REPEAT_STATEMENT,
        VAR_ASSIGNMENT,
        FUNCTION_CALL,
        OPERATION,
    };

    class ASTNode {
    public:
        virtual ~ASTNode() = default;
        NodeType type;
        //virtual llvm::Value* codegen() = 0;
    };

    enum PushOperationType
    {
         PUSH_SIGNED_I64,
         PUSH_I64,
         PUSH_SIGNED_F64,
         PUSH_F64,
         PUSH_SIGNED_F64_E,
         PUSH_F64_E,
         PUSH_BIN_I64,
         PUSH_HEX_I64,
         PUSH_I8,
         PUSH_STR,
         PUSH_BOOL,
         PUSH_SIMPLE_TYPE,
         PUSH_IDENTIFIER
    };
    enum StackOperationType
    {
        STACK_DUP,
        STACK_ROT,
        STACK_SWAP,
        STACK_OVER,
        STACK_POP
   };
    const std::unordered_map<std::string, StackOperationType> stringToStackOp = {
        {"dup",  STACK_DUP},
        {"rot",  STACK_ROT},
        {"swap", STACK_SWAP},
        {"over", STACK_OVER},
        {"pop",  STACK_POP}
    };



    class PushOperation: public ASTNode
    {
        static PushOperationType getType(StcParser::PushContext *ctx);
        public:

        PushOperationType stackOperation;
        std::string token;

        PushOperation(StcParser::PushContext *ctx);
    };



    class StackOperation: public ASTNode
    {
        static StackOperationType getType(StcParser::StackOperationContext *ctx);
    public:

        StackOperationType stackOperation;
        std::string token;

        StackOperation(StcParser::StackOperationContext *ctx);
    };



    enum OperatorType {
        // Logic
        OPERATOR_LE,
        OPERATOR_GE,
        OPERATOR_NE,
        OPERATOR_EQ,
        OPERATOR_LT,
        OPERATOR_GT,
        OPERATOR_AND,
        OPERATOR_OR,
        OPERATOR_NOT,

        // Arithmetic
        OPERATOR_ADD,
        OPERATOR_SUB,
        OPERATOR_MUL,
        OPERATOR_DIV,
        OPERATOR_MOD,

        // Assign
        OPERATOR_ASSIGN,

        // Built-in
        OPERATOR_TYPEOF,
        OPERATOR_LEN,
        OPERATOR_CALL,
        OPERATOR_COPY
    };
    class Operator : public ASTNode{
        static OperatorType getType(StcParser::OperaorContext *ctx);
    public:

        OperatorType operatorType;
        std::string token;

        Operator(StcParser::OperaorContext *ctx);
    };
    class Var
    {
    public:
        std::string name;
        type::SimpleType type;
    };
    class Block
    {
    public:
        std::string name;
        std::vector<std::unique_ptr<Var>> variables;
        std::vector<std::unique_ptr<ASTNode>> operations;
        std::vector<std::unique_ptr<Block>> blocks;
    };

    class IfStatement: public ASTNode
    {
    public:
        bool isElse = false;
        std::unique_ptr<Block> trueBlock;
        std::unique_ptr<Block> falseBlock;
        IfStatement()
        {
            this->type = IF_STATEMENT;
        }
    };

    class RepeatStatement: public ASTNode
    {
    public:
        std::unique_ptr<Block> LoopBlock;
        RepeatStatement()
        {
            this->type = REPEAT_STATEMENT;
        }
    };

    class Function
    {
        int blockIndex = 0;
    public:
        std::string name;
        std::vector<std::unique_ptr<Var>> arguments;
        type::Type returnType{};
        std::vector<std::unique_ptr<Block>> blocks;
        std::string getBlockIndex();
    };
    class Struct
    {
    public:
        std::string name;
        std::vector<std::unique_ptr<Var>> fields;
    };
    class Program
    {
    public:
        std::map<std::string, std::unique_ptr<Function>> functions;
        std::map<std::string, std::unique_ptr<Struct>>structs;

    };
}




#endif //PROGRAM_H
