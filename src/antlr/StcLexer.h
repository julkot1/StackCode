
// Generated from Stc.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  StcLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, NEW = 18, STRUCT_DEFINITION = 19, 
    STACK_PREVENTION = 20, NUMBER = 21, SIGNED_NUMBER = 22, FLOAT = 23, 
    SIGNED_FLOAT = 24, FLOAT_E = 25, SIGNED_FLOAT_E = 26, BIN_NUMBER = 27, 
    HEX_NUMBER = 28, STRING = 29, CHAR = 30, BOOL = 31, SIMPLE_TYPE = 32, 
    LOGIC_OPERATOR = 33, ARITHMETIC_OPERATOR = 34, ASSIGN_OPERATOR = 35, 
    REFERENCE_OPERATOR = 36, BUILD_IN_OPERATOR = 37, ARRAY_OPEN = 38, ARRAY_CLOSE = 39, 
    ARRAY_OPERATOR = 40, AT = 41, ID = 42, WS = 43
  };

  explicit StcLexer(antlr4::CharStream *input);

  ~StcLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

