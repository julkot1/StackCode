
// Generated from Stc.g4 by ANTLR 4.13.1


#include "StcListener.h"
#include "StcVisitor.h"

#include "StcParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct StcParserStaticData final {
  StcParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  StcParserStaticData(const StcParserStaticData&) = delete;
  StcParserStaticData(StcParserStaticData&&) = delete;
  StcParserStaticData& operator=(const StcParserStaticData&) = delete;
  StcParserStaticData& operator=(StcParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag stcParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
StcParserStaticData *stcParserStaticData = nullptr;

void stcParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (stcParserStaticData != nullptr) {
    return;
  }
#else
  assert(stcParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<StcParserStaticData>(
    std::vector<std::string>{
      "prog", "functionDef", "type", "statement", "block", "newStructAssign", 
      "newOperator", "struct", "structElement", "structBody", "ifBlock", 
      "elseBlock", "repeatBlock", "arguments", "operation", "operaor", "stackOperation", 
      "push", "arrayElement", "arrayBase", "arrayIndexShift", "arrayIndex", 
      "capacity", "array", "arrayDescriber", "arrayNew", "argument", "varAssign", 
      "varAssignIdentifier", "varType", "varReference", "varIdentifier", 
      "identifier"
    },
    std::vector<std::string>{
      "", "'fun'", "'<'", "'>'", "'{'", "'}'", "':'", "'if'", "'else'", 
      "'repeat'", "'('", "')'", "'dup'", "'rot'", "'swap'", "'pop'", "'over'", 
      "'c:'", "'new'", "'struct'", "'!'", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "':='", "'&'", "", "'['", "']'", "'arr'", 
      "'@'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "NEW", "STRUCT_DEFINITION", "STACK_PREVENTION", "NUMBER", "SIGNED_NUMBER", 
      "FLOAT", "SIGNED_FLOAT", "FLOAT_E", "SIGNED_FLOAT_E", "BIN_NUMBER", 
      "HEX_NUMBER", "STRING", "CHAR", "BOOL", "SIMPLE_TYPE", "LOGIC_OPERATOR", 
      "ARITHMETIC_OPERATOR", "ASSIGN_OPERATOR", "REFERENCE_OPERATOR", "BUILD_IN_OPERATOR", 
      "ARRAY_OPEN", "ARRAY_CLOSE", "ARRAY_OPERATOR", "AT", "ID", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,43,266,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,1,0,1,0,4,0,69,8,0,11,0,12,
  	0,70,1,0,1,0,1,1,1,1,1,1,3,1,78,8,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,3,
  	2,88,8,2,1,2,3,2,91,8,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,3,3,107,8,3,1,4,1,4,4,4,111,8,4,11,4,12,4,112,1,4,1,4,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,9,1,9,
  	4,9,136,8,9,11,9,12,9,137,1,9,1,9,1,10,1,10,1,10,3,10,145,8,10,1,11,1,
  	11,1,11,1,12,1,12,3,12,152,8,12,1,12,1,12,1,13,1,13,4,13,158,8,13,11,
  	13,12,13,159,1,13,1,13,1,14,3,14,165,8,14,1,14,1,14,1,15,1,15,1,16,1,
  	16,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,
  	18,1,18,1,18,1,18,3,18,190,8,18,1,19,1,19,1,20,1,20,3,20,196,8,20,1,21,
  	1,21,1,21,1,21,1,22,1,22,1,22,1,23,1,23,4,23,207,8,23,11,23,12,23,208,
  	1,23,1,23,3,23,213,8,23,1,24,1,24,1,24,1,24,1,25,1,25,1,25,3,25,222,8,
  	25,1,26,1,26,3,26,226,8,26,1,27,1,27,1,27,3,27,231,8,27,1,27,1,27,1,28,
  	1,28,1,28,1,29,1,29,1,29,1,29,1,30,1,30,1,30,1,31,1,31,1,31,4,31,248,
  	8,31,11,31,12,31,249,3,31,252,8,31,1,32,3,32,255,8,32,1,32,1,32,1,32,
  	4,32,260,8,32,11,32,12,32,261,3,32,264,8,32,1,32,0,0,33,0,2,4,6,8,10,
  	12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,
  	58,60,62,64,0,3,2,0,33,35,37,37,1,0,12,16,1,0,21,32,283,0,68,1,0,0,0,
  	2,74,1,0,0,0,4,90,1,0,0,0,6,106,1,0,0,0,8,108,1,0,0,0,10,116,1,0,0,0,
  	12,122,1,0,0,0,14,126,1,0,0,0,16,130,1,0,0,0,18,133,1,0,0,0,20,141,1,
  	0,0,0,22,146,1,0,0,0,24,149,1,0,0,0,26,155,1,0,0,0,28,164,1,0,0,0,30,
  	168,1,0,0,0,32,170,1,0,0,0,34,172,1,0,0,0,36,189,1,0,0,0,38,191,1,0,0,
  	0,40,195,1,0,0,0,42,197,1,0,0,0,44,201,1,0,0,0,46,204,1,0,0,0,48,214,
  	1,0,0,0,50,218,1,0,0,0,52,223,1,0,0,0,54,230,1,0,0,0,56,234,1,0,0,0,58,
  	237,1,0,0,0,60,241,1,0,0,0,62,244,1,0,0,0,64,254,1,0,0,0,66,69,3,2,1,
  	0,67,69,3,14,7,0,68,66,1,0,0,0,68,67,1,0,0,0,69,70,1,0,0,0,70,68,1,0,
  	0,0,70,71,1,0,0,0,71,72,1,0,0,0,72,73,5,0,0,1,73,1,1,0,0,0,74,75,5,1,
  	0,0,75,77,5,42,0,0,76,78,3,26,13,0,77,76,1,0,0,0,77,78,1,0,0,0,78,79,
  	1,0,0,0,79,80,3,8,4,0,80,3,1,0,0,0,81,91,5,32,0,0,82,91,5,42,0,0,83,84,
  	5,32,0,0,84,87,5,2,0,0,85,88,3,4,2,0,86,88,5,42,0,0,87,85,1,0,0,0,87,
  	86,1,0,0,0,88,89,1,0,0,0,89,91,5,3,0,0,90,81,1,0,0,0,90,82,1,0,0,0,90,
  	83,1,0,0,0,91,5,1,0,0,0,92,107,3,10,5,0,93,107,3,12,6,0,94,107,3,60,30,
  	0,95,107,3,54,27,0,96,107,3,42,21,0,97,107,3,50,25,0,98,107,3,46,23,0,
  	99,107,3,28,14,0,100,107,3,32,16,0,101,107,3,34,17,0,102,107,3,64,32,
  	0,103,107,3,2,1,0,104,107,3,20,10,0,105,107,3,24,12,0,106,92,1,0,0,0,
  	106,93,1,0,0,0,106,94,1,0,0,0,106,95,1,0,0,0,106,96,1,0,0,0,106,97,1,
  	0,0,0,106,98,1,0,0,0,106,99,1,0,0,0,106,100,1,0,0,0,106,101,1,0,0,0,106,
  	102,1,0,0,0,106,103,1,0,0,0,106,104,1,0,0,0,106,105,1,0,0,0,107,7,1,0,
  	0,0,108,110,5,4,0,0,109,111,3,6,3,0,110,109,1,0,0,0,111,112,1,0,0,0,112,
  	110,1,0,0,0,112,113,1,0,0,0,113,114,1,0,0,0,114,115,5,5,0,0,115,9,1,0,
  	0,0,116,117,5,18,0,0,117,118,5,6,0,0,118,119,5,42,0,0,119,120,5,42,0,
  	0,120,121,5,35,0,0,121,11,1,0,0,0,122,123,5,18,0,0,123,124,5,6,0,0,124,
  	125,5,42,0,0,125,13,1,0,0,0,126,127,5,19,0,0,127,128,5,42,0,0,128,129,
  	3,18,9,0,129,15,1,0,0,0,130,131,5,42,0,0,131,132,3,58,29,0,132,17,1,0,
  	0,0,133,135,5,4,0,0,134,136,3,16,8,0,135,134,1,0,0,0,136,137,1,0,0,0,
  	137,135,1,0,0,0,137,138,1,0,0,0,138,139,1,0,0,0,139,140,5,5,0,0,140,19,
  	1,0,0,0,141,142,5,7,0,0,142,144,3,8,4,0,143,145,3,22,11,0,144,143,1,0,
  	0,0,144,145,1,0,0,0,145,21,1,0,0,0,146,147,5,8,0,0,147,148,3,8,4,0,148,
  	23,1,0,0,0,149,151,5,9,0,0,150,152,3,26,13,0,151,150,1,0,0,0,151,152,
  	1,0,0,0,152,153,1,0,0,0,153,154,3,8,4,0,154,25,1,0,0,0,155,157,5,10,0,
  	0,156,158,3,52,26,0,157,156,1,0,0,0,158,159,1,0,0,0,159,157,1,0,0,0,159,
  	160,1,0,0,0,160,161,1,0,0,0,161,162,5,11,0,0,162,27,1,0,0,0,163,165,5,
  	20,0,0,164,163,1,0,0,0,164,165,1,0,0,0,165,166,1,0,0,0,166,167,3,30,15,
  	0,167,29,1,0,0,0,168,169,7,0,0,0,169,31,1,0,0,0,170,171,7,1,0,0,171,33,
  	1,0,0,0,172,173,7,2,0,0,173,35,1,0,0,0,174,190,5,22,0,0,175,190,5,21,
  	0,0,176,190,5,24,0,0,177,190,5,23,0,0,178,190,5,26,0,0,179,190,5,25,0,
  	0,180,190,5,27,0,0,181,190,5,28,0,0,182,190,5,30,0,0,183,190,5,29,0,0,
  	184,190,5,31,0,0,185,190,5,32,0,0,186,190,3,42,21,0,187,190,3,62,31,0,
  	188,190,3,46,23,0,189,174,1,0,0,0,189,175,1,0,0,0,189,176,1,0,0,0,189,
  	177,1,0,0,0,189,178,1,0,0,0,189,179,1,0,0,0,189,180,1,0,0,0,189,181,1,
  	0,0,0,189,182,1,0,0,0,189,183,1,0,0,0,189,184,1,0,0,0,189,185,1,0,0,0,
  	189,186,1,0,0,0,189,187,1,0,0,0,189,188,1,0,0,0,190,37,1,0,0,0,191,192,
  	3,62,31,0,192,39,1,0,0,0,193,196,5,21,0,0,194,196,3,62,31,0,195,193,1,
  	0,0,0,195,194,1,0,0,0,196,41,1,0,0,0,197,198,3,38,19,0,198,199,5,41,0,
  	0,199,200,3,40,20,0,200,43,1,0,0,0,201,202,5,17,0,0,202,203,5,21,0,0,
  	203,45,1,0,0,0,204,206,5,38,0,0,205,207,3,36,18,0,206,205,1,0,0,0,207,
  	208,1,0,0,0,208,206,1,0,0,0,208,209,1,0,0,0,209,210,1,0,0,0,210,212,5,
  	39,0,0,211,213,3,44,22,0,212,211,1,0,0,0,212,213,1,0,0,0,213,47,1,0,0,
  	0,214,215,5,38,0,0,215,216,5,21,0,0,216,217,5,39,0,0,217,49,1,0,0,0,218,
  	219,5,40,0,0,219,221,3,48,24,0,220,222,3,48,24,0,221,220,1,0,0,0,221,
  	222,1,0,0,0,222,51,1,0,0,0,223,225,5,42,0,0,224,226,3,58,29,0,225,224,
  	1,0,0,0,225,226,1,0,0,0,226,53,1,0,0,0,227,231,3,56,28,0,228,231,3,42,
  	21,0,229,231,3,64,32,0,230,227,1,0,0,0,230,228,1,0,0,0,230,229,1,0,0,
  	0,231,232,1,0,0,0,232,233,5,35,0,0,233,55,1,0,0,0,234,235,3,62,31,0,235,
  	236,3,58,29,0,236,57,1,0,0,0,237,238,5,2,0,0,238,239,3,4,2,0,239,240,
  	5,3,0,0,240,59,1,0,0,0,241,242,5,36,0,0,242,243,3,62,31,0,243,61,1,0,
  	0,0,244,251,5,42,0,0,245,246,5,6,0,0,246,248,5,42,0,0,247,245,1,0,0,0,
  	248,249,1,0,0,0,249,247,1,0,0,0,249,250,1,0,0,0,250,252,1,0,0,0,251,247,
  	1,0,0,0,251,252,1,0,0,0,252,63,1,0,0,0,253,255,5,20,0,0,254,253,1,0,0,
  	0,254,255,1,0,0,0,255,256,1,0,0,0,256,263,5,42,0,0,257,258,5,6,0,0,258,
  	260,5,42,0,0,259,257,1,0,0,0,260,261,1,0,0,0,261,259,1,0,0,0,261,262,
  	1,0,0,0,262,264,1,0,0,0,263,259,1,0,0,0,263,264,1,0,0,0,264,65,1,0,0,
  	0,24,68,70,77,87,90,106,112,137,144,151,159,164,189,195,208,212,221,225,
  	230,249,251,254,261,263
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  stcParserStaticData = staticData.release();
}

}

StcParser::StcParser(TokenStream *input) : StcParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

StcParser::StcParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  StcParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *stcParserStaticData->atn, stcParserStaticData->decisionToDFA, stcParserStaticData->sharedContextCache, options);
}

StcParser::~StcParser() {
  delete _interpreter;
}

const atn::ATN& StcParser::getATN() const {
  return *stcParserStaticData->atn;
}

std::string StcParser::getGrammarFileName() const {
  return "Stc.g4";
}

const std::vector<std::string>& StcParser::getRuleNames() const {
  return stcParserStaticData->ruleNames;
}

const dfa::Vocabulary& StcParser::getVocabulary() const {
  return stcParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView StcParser::getSerializedATN() const {
  return stcParserStaticData->serializedATN;
}


//----------------- ProgContext ------------------------------------------------------------------

StcParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::ProgContext::EOF() {
  return getToken(StcParser::EOF, 0);
}

std::vector<StcParser::FunctionDefContext *> StcParser::ProgContext::functionDef() {
  return getRuleContexts<StcParser::FunctionDefContext>();
}

StcParser::FunctionDefContext* StcParser::ProgContext::functionDef(size_t i) {
  return getRuleContext<StcParser::FunctionDefContext>(i);
}

std::vector<StcParser::StructContext *> StcParser::ProgContext::struct_() {
  return getRuleContexts<StcParser::StructContext>();
}

StcParser::StructContext* StcParser::ProgContext::struct_(size_t i) {
  return getRuleContext<StcParser::StructContext>(i);
}


size_t StcParser::ProgContext::getRuleIndex() const {
  return StcParser::RuleProg;
}

void StcParser::ProgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg(this);
}

void StcParser::ProgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg(this);
}


std::any StcParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

StcParser::ProgContext* StcParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, StcParser::RuleProg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(68);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case StcParser::T__0: {
          setState(66);
          functionDef();
          break;
        }

        case StcParser::STRUCT_DEFINITION: {
          setState(67);
          struct_();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(70); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == StcParser::T__0

    || _la == StcParser::STRUCT_DEFINITION);
    setState(72);
    match(StcParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefContext ------------------------------------------------------------------

StcParser::FunctionDefContext::FunctionDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::FunctionDefContext::ID() {
  return getToken(StcParser::ID, 0);
}

StcParser::BlockContext* StcParser::FunctionDefContext::block() {
  return getRuleContext<StcParser::BlockContext>(0);
}

StcParser::ArgumentsContext* StcParser::FunctionDefContext::arguments() {
  return getRuleContext<StcParser::ArgumentsContext>(0);
}


size_t StcParser::FunctionDefContext::getRuleIndex() const {
  return StcParser::RuleFunctionDef;
}

void StcParser::FunctionDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDef(this);
}

void StcParser::FunctionDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDef(this);
}


std::any StcParser::FunctionDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitFunctionDef(this);
  else
    return visitor->visitChildren(this);
}

StcParser::FunctionDefContext* StcParser::functionDef() {
  FunctionDefContext *_localctx = _tracker.createInstance<FunctionDefContext>(_ctx, getState());
  enterRule(_localctx, 2, StcParser::RuleFunctionDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    match(StcParser::T__0);
    setState(75);
    match(StcParser::ID);
    setState(77);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StcParser::T__9) {
      setState(76);
      arguments();
    }
    setState(79);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

StcParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::TypeContext::SIMPLE_TYPE() {
  return getToken(StcParser::SIMPLE_TYPE, 0);
}

tree::TerminalNode* StcParser::TypeContext::ID() {
  return getToken(StcParser::ID, 0);
}

StcParser::TypeContext* StcParser::TypeContext::type() {
  return getRuleContext<StcParser::TypeContext>(0);
}


size_t StcParser::TypeContext::getRuleIndex() const {
  return StcParser::RuleType;
}

void StcParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void StcParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}


std::any StcParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

StcParser::TypeContext* StcParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 4, StcParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(90);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(81);
      match(StcParser::SIMPLE_TYPE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(82);
      match(StcParser::ID);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(83);
      match(StcParser::SIMPLE_TYPE);
      setState(84);
      match(StcParser::T__1);
      setState(87);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
      case 1: {
        setState(85);
        type();
        break;
      }

      case 2: {
        setState(86);
        match(StcParser::ID);
        break;
      }

      default:
        break;
      }
      setState(89);
      match(StcParser::T__2);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

StcParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StcParser::NewStructAssignContext* StcParser::StatementContext::newStructAssign() {
  return getRuleContext<StcParser::NewStructAssignContext>(0);
}

StcParser::NewOperatorContext* StcParser::StatementContext::newOperator() {
  return getRuleContext<StcParser::NewOperatorContext>(0);
}

StcParser::VarReferenceContext* StcParser::StatementContext::varReference() {
  return getRuleContext<StcParser::VarReferenceContext>(0);
}

StcParser::VarAssignContext* StcParser::StatementContext::varAssign() {
  return getRuleContext<StcParser::VarAssignContext>(0);
}

StcParser::ArrayIndexContext* StcParser::StatementContext::arrayIndex() {
  return getRuleContext<StcParser::ArrayIndexContext>(0);
}

StcParser::ArrayNewContext* StcParser::StatementContext::arrayNew() {
  return getRuleContext<StcParser::ArrayNewContext>(0);
}

StcParser::ArrayContext* StcParser::StatementContext::array() {
  return getRuleContext<StcParser::ArrayContext>(0);
}

StcParser::OperationContext* StcParser::StatementContext::operation() {
  return getRuleContext<StcParser::OperationContext>(0);
}

StcParser::StackOperationContext* StcParser::StatementContext::stackOperation() {
  return getRuleContext<StcParser::StackOperationContext>(0);
}

StcParser::PushContext* StcParser::StatementContext::push() {
  return getRuleContext<StcParser::PushContext>(0);
}

StcParser::IdentifierContext* StcParser::StatementContext::identifier() {
  return getRuleContext<StcParser::IdentifierContext>(0);
}

StcParser::FunctionDefContext* StcParser::StatementContext::functionDef() {
  return getRuleContext<StcParser::FunctionDefContext>(0);
}

StcParser::IfBlockContext* StcParser::StatementContext::ifBlock() {
  return getRuleContext<StcParser::IfBlockContext>(0);
}

StcParser::RepeatBlockContext* StcParser::StatementContext::repeatBlock() {
  return getRuleContext<StcParser::RepeatBlockContext>(0);
}


size_t StcParser::StatementContext::getRuleIndex() const {
  return StcParser::RuleStatement;
}

void StcParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void StcParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any StcParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

StcParser::StatementContext* StcParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 6, StcParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(106);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(92);
      newStructAssign();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(93);
      newOperator();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(94);
      varReference();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(95);
      varAssign();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(96);
      arrayIndex();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(97);
      arrayNew();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(98);
      array();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(99);
      operation();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(100);
      stackOperation();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(101);
      push();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(102);
      identifier();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(103);
      functionDef();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(104);
      ifBlock();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(105);
      repeatBlock();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

StcParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<StcParser::StatementContext *> StcParser::BlockContext::statement() {
  return getRuleContexts<StcParser::StatementContext>();
}

StcParser::StatementContext* StcParser::BlockContext::statement(size_t i) {
  return getRuleContext<StcParser::StatementContext>(i);
}


size_t StcParser::BlockContext::getRuleIndex() const {
  return StcParser::RuleBlock;
}

void StcParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void StcParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any StcParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

StcParser::BlockContext* StcParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 8, StcParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(108);
    match(StcParser::T__3);
    setState(110); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(109);
      statement();
      setState(112); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 6047313293954) != 0));
    setState(114);
    match(StcParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NewStructAssignContext ------------------------------------------------------------------

StcParser::NewStructAssignContext::NewStructAssignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::NewStructAssignContext::NEW() {
  return getToken(StcParser::NEW, 0);
}

std::vector<tree::TerminalNode *> StcParser::NewStructAssignContext::ID() {
  return getTokens(StcParser::ID);
}

tree::TerminalNode* StcParser::NewStructAssignContext::ID(size_t i) {
  return getToken(StcParser::ID, i);
}

tree::TerminalNode* StcParser::NewStructAssignContext::ASSIGN_OPERATOR() {
  return getToken(StcParser::ASSIGN_OPERATOR, 0);
}


size_t StcParser::NewStructAssignContext::getRuleIndex() const {
  return StcParser::RuleNewStructAssign;
}

void StcParser::NewStructAssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNewStructAssign(this);
}

void StcParser::NewStructAssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNewStructAssign(this);
}


std::any StcParser::NewStructAssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitNewStructAssign(this);
  else
    return visitor->visitChildren(this);
}

StcParser::NewStructAssignContext* StcParser::newStructAssign() {
  NewStructAssignContext *_localctx = _tracker.createInstance<NewStructAssignContext>(_ctx, getState());
  enterRule(_localctx, 10, StcParser::RuleNewStructAssign);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    match(StcParser::NEW);
    setState(117);
    match(StcParser::T__5);
    setState(118);
    match(StcParser::ID);
    setState(119);
    match(StcParser::ID);
    setState(120);
    match(StcParser::ASSIGN_OPERATOR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NewOperatorContext ------------------------------------------------------------------

StcParser::NewOperatorContext::NewOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::NewOperatorContext::NEW() {
  return getToken(StcParser::NEW, 0);
}

tree::TerminalNode* StcParser::NewOperatorContext::ID() {
  return getToken(StcParser::ID, 0);
}


size_t StcParser::NewOperatorContext::getRuleIndex() const {
  return StcParser::RuleNewOperator;
}

void StcParser::NewOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNewOperator(this);
}

void StcParser::NewOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNewOperator(this);
}


std::any StcParser::NewOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitNewOperator(this);
  else
    return visitor->visitChildren(this);
}

StcParser::NewOperatorContext* StcParser::newOperator() {
  NewOperatorContext *_localctx = _tracker.createInstance<NewOperatorContext>(_ctx, getState());
  enterRule(_localctx, 12, StcParser::RuleNewOperator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(StcParser::NEW);
    setState(123);
    match(StcParser::T__5);
    setState(124);
    match(StcParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructContext ------------------------------------------------------------------

StcParser::StructContext::StructContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::StructContext::STRUCT_DEFINITION() {
  return getToken(StcParser::STRUCT_DEFINITION, 0);
}

tree::TerminalNode* StcParser::StructContext::ID() {
  return getToken(StcParser::ID, 0);
}

StcParser::StructBodyContext* StcParser::StructContext::structBody() {
  return getRuleContext<StcParser::StructBodyContext>(0);
}


size_t StcParser::StructContext::getRuleIndex() const {
  return StcParser::RuleStruct;
}

void StcParser::StructContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct(this);
}

void StcParser::StructContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct(this);
}


std::any StcParser::StructContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitStruct(this);
  else
    return visitor->visitChildren(this);
}

StcParser::StructContext* StcParser::struct_() {
  StructContext *_localctx = _tracker.createInstance<StructContext>(_ctx, getState());
  enterRule(_localctx, 14, StcParser::RuleStruct);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(126);
    match(StcParser::STRUCT_DEFINITION);
    setState(127);
    match(StcParser::ID);
    setState(128);
    structBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructElementContext ------------------------------------------------------------------

StcParser::StructElementContext::StructElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::StructElementContext::ID() {
  return getToken(StcParser::ID, 0);
}

StcParser::VarTypeContext* StcParser::StructElementContext::varType() {
  return getRuleContext<StcParser::VarTypeContext>(0);
}


size_t StcParser::StructElementContext::getRuleIndex() const {
  return StcParser::RuleStructElement;
}

void StcParser::StructElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructElement(this);
}

void StcParser::StructElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructElement(this);
}


std::any StcParser::StructElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitStructElement(this);
  else
    return visitor->visitChildren(this);
}

StcParser::StructElementContext* StcParser::structElement() {
  StructElementContext *_localctx = _tracker.createInstance<StructElementContext>(_ctx, getState());
  enterRule(_localctx, 16, StcParser::RuleStructElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    match(StcParser::ID);
    setState(131);
    varType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructBodyContext ------------------------------------------------------------------

StcParser::StructBodyContext::StructBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<StcParser::StructElementContext *> StcParser::StructBodyContext::structElement() {
  return getRuleContexts<StcParser::StructElementContext>();
}

StcParser::StructElementContext* StcParser::StructBodyContext::structElement(size_t i) {
  return getRuleContext<StcParser::StructElementContext>(i);
}


size_t StcParser::StructBodyContext::getRuleIndex() const {
  return StcParser::RuleStructBody;
}

void StcParser::StructBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructBody(this);
}

void StcParser::StructBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructBody(this);
}


std::any StcParser::StructBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitStructBody(this);
  else
    return visitor->visitChildren(this);
}

StcParser::StructBodyContext* StcParser::structBody() {
  StructBodyContext *_localctx = _tracker.createInstance<StructBodyContext>(_ctx, getState());
  enterRule(_localctx, 18, StcParser::RuleStructBody);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    match(StcParser::T__3);
    setState(135); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(134);
      structElement();
      setState(137); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == StcParser::ID);
    setState(139);
    match(StcParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfBlockContext ------------------------------------------------------------------

StcParser::IfBlockContext::IfBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StcParser::BlockContext* StcParser::IfBlockContext::block() {
  return getRuleContext<StcParser::BlockContext>(0);
}

StcParser::ElseBlockContext* StcParser::IfBlockContext::elseBlock() {
  return getRuleContext<StcParser::ElseBlockContext>(0);
}


size_t StcParser::IfBlockContext::getRuleIndex() const {
  return StcParser::RuleIfBlock;
}

void StcParser::IfBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfBlock(this);
}

void StcParser::IfBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfBlock(this);
}


std::any StcParser::IfBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitIfBlock(this);
  else
    return visitor->visitChildren(this);
}

StcParser::IfBlockContext* StcParser::ifBlock() {
  IfBlockContext *_localctx = _tracker.createInstance<IfBlockContext>(_ctx, getState());
  enterRule(_localctx, 20, StcParser::RuleIfBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(141);
    match(StcParser::T__6);
    setState(142);
    block();
    setState(144);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StcParser::T__7) {
      setState(143);
      elseBlock();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseBlockContext ------------------------------------------------------------------

StcParser::ElseBlockContext::ElseBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StcParser::BlockContext* StcParser::ElseBlockContext::block() {
  return getRuleContext<StcParser::BlockContext>(0);
}


size_t StcParser::ElseBlockContext::getRuleIndex() const {
  return StcParser::RuleElseBlock;
}

void StcParser::ElseBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseBlock(this);
}

void StcParser::ElseBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseBlock(this);
}


std::any StcParser::ElseBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitElseBlock(this);
  else
    return visitor->visitChildren(this);
}

StcParser::ElseBlockContext* StcParser::elseBlock() {
  ElseBlockContext *_localctx = _tracker.createInstance<ElseBlockContext>(_ctx, getState());
  enterRule(_localctx, 22, StcParser::RuleElseBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    match(StcParser::T__7);
    setState(147);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RepeatBlockContext ------------------------------------------------------------------

StcParser::RepeatBlockContext::RepeatBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StcParser::BlockContext* StcParser::RepeatBlockContext::block() {
  return getRuleContext<StcParser::BlockContext>(0);
}

StcParser::ArgumentsContext* StcParser::RepeatBlockContext::arguments() {
  return getRuleContext<StcParser::ArgumentsContext>(0);
}


size_t StcParser::RepeatBlockContext::getRuleIndex() const {
  return StcParser::RuleRepeatBlock;
}

void StcParser::RepeatBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRepeatBlock(this);
}

void StcParser::RepeatBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRepeatBlock(this);
}


std::any StcParser::RepeatBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitRepeatBlock(this);
  else
    return visitor->visitChildren(this);
}

StcParser::RepeatBlockContext* StcParser::repeatBlock() {
  RepeatBlockContext *_localctx = _tracker.createInstance<RepeatBlockContext>(_ctx, getState());
  enterRule(_localctx, 24, StcParser::RuleRepeatBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149);
    match(StcParser::T__8);
    setState(151);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StcParser::T__9) {
      setState(150);
      arguments();
    }
    setState(153);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

StcParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<StcParser::ArgumentContext *> StcParser::ArgumentsContext::argument() {
  return getRuleContexts<StcParser::ArgumentContext>();
}

StcParser::ArgumentContext* StcParser::ArgumentsContext::argument(size_t i) {
  return getRuleContext<StcParser::ArgumentContext>(i);
}


size_t StcParser::ArgumentsContext::getRuleIndex() const {
  return StcParser::RuleArguments;
}

void StcParser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void StcParser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}


std::any StcParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

StcParser::ArgumentsContext* StcParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 26, StcParser::RuleArguments);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    match(StcParser::T__9);
    setState(157); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(156);
      argument();
      setState(159); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == StcParser::ID);
    setState(161);
    match(StcParser::T__10);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperationContext ------------------------------------------------------------------

StcParser::OperationContext::OperationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StcParser::OperaorContext* StcParser::OperationContext::operaor() {
  return getRuleContext<StcParser::OperaorContext>(0);
}

tree::TerminalNode* StcParser::OperationContext::STACK_PREVENTION() {
  return getToken(StcParser::STACK_PREVENTION, 0);
}


size_t StcParser::OperationContext::getRuleIndex() const {
  return StcParser::RuleOperation;
}

void StcParser::OperationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperation(this);
}

void StcParser::OperationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperation(this);
}


std::any StcParser::OperationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitOperation(this);
  else
    return visitor->visitChildren(this);
}

StcParser::OperationContext* StcParser::operation() {
  OperationContext *_localctx = _tracker.createInstance<OperationContext>(_ctx, getState());
  enterRule(_localctx, 28, StcParser::RuleOperation);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StcParser::STACK_PREVENTION) {
      setState(163);
      match(StcParser::STACK_PREVENTION);
    }
    setState(166);
    operaor();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperaorContext ------------------------------------------------------------------

StcParser::OperaorContext::OperaorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::OperaorContext::LOGIC_OPERATOR() {
  return getToken(StcParser::LOGIC_OPERATOR, 0);
}

tree::TerminalNode* StcParser::OperaorContext::ARITHMETIC_OPERATOR() {
  return getToken(StcParser::ARITHMETIC_OPERATOR, 0);
}

tree::TerminalNode* StcParser::OperaorContext::BUILD_IN_OPERATOR() {
  return getToken(StcParser::BUILD_IN_OPERATOR, 0);
}

tree::TerminalNode* StcParser::OperaorContext::ASSIGN_OPERATOR() {
  return getToken(StcParser::ASSIGN_OPERATOR, 0);
}


size_t StcParser::OperaorContext::getRuleIndex() const {
  return StcParser::RuleOperaor;
}

void StcParser::OperaorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperaor(this);
}

void StcParser::OperaorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperaor(this);
}


std::any StcParser::OperaorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitOperaor(this);
  else
    return visitor->visitChildren(this);
}

StcParser::OperaorContext* StcParser::operaor() {
  OperaorContext *_localctx = _tracker.createInstance<OperaorContext>(_ctx, getState());
  enterRule(_localctx, 30, StcParser::RuleOperaor);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(168);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 197568495616) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StackOperationContext ------------------------------------------------------------------

StcParser::StackOperationContext::StackOperationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t StcParser::StackOperationContext::getRuleIndex() const {
  return StcParser::RuleStackOperation;
}

void StcParser::StackOperationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStackOperation(this);
}

void StcParser::StackOperationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStackOperation(this);
}


std::any StcParser::StackOperationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitStackOperation(this);
  else
    return visitor->visitChildren(this);
}

StcParser::StackOperationContext* StcParser::stackOperation() {
  StackOperationContext *_localctx = _tracker.createInstance<StackOperationContext>(_ctx, getState());
  enterRule(_localctx, 32, StcParser::RuleStackOperation);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 126976) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PushContext ------------------------------------------------------------------

StcParser::PushContext::PushContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::PushContext::SIGNED_NUMBER() {
  return getToken(StcParser::SIGNED_NUMBER, 0);
}

tree::TerminalNode* StcParser::PushContext::NUMBER() {
  return getToken(StcParser::NUMBER, 0);
}

tree::TerminalNode* StcParser::PushContext::SIGNED_FLOAT() {
  return getToken(StcParser::SIGNED_FLOAT, 0);
}

tree::TerminalNode* StcParser::PushContext::FLOAT() {
  return getToken(StcParser::FLOAT, 0);
}

tree::TerminalNode* StcParser::PushContext::SIGNED_FLOAT_E() {
  return getToken(StcParser::SIGNED_FLOAT_E, 0);
}

tree::TerminalNode* StcParser::PushContext::FLOAT_E() {
  return getToken(StcParser::FLOAT_E, 0);
}

tree::TerminalNode* StcParser::PushContext::BIN_NUMBER() {
  return getToken(StcParser::BIN_NUMBER, 0);
}

tree::TerminalNode* StcParser::PushContext::HEX_NUMBER() {
  return getToken(StcParser::HEX_NUMBER, 0);
}

tree::TerminalNode* StcParser::PushContext::CHAR() {
  return getToken(StcParser::CHAR, 0);
}

tree::TerminalNode* StcParser::PushContext::STRING() {
  return getToken(StcParser::STRING, 0);
}

tree::TerminalNode* StcParser::PushContext::BOOL() {
  return getToken(StcParser::BOOL, 0);
}

tree::TerminalNode* StcParser::PushContext::SIMPLE_TYPE() {
  return getToken(StcParser::SIMPLE_TYPE, 0);
}


size_t StcParser::PushContext::getRuleIndex() const {
  return StcParser::RulePush;
}

void StcParser::PushContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPush(this);
}

void StcParser::PushContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPush(this);
}


std::any StcParser::PushContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitPush(this);
  else
    return visitor->visitChildren(this);
}

StcParser::PushContext* StcParser::push() {
  PushContext *_localctx = _tracker.createInstance<PushContext>(_ctx, getState());
  enterRule(_localctx, 34, StcParser::RulePush);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(172);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8587837440) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayElementContext ------------------------------------------------------------------

StcParser::ArrayElementContext::ArrayElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::ArrayElementContext::SIGNED_NUMBER() {
  return getToken(StcParser::SIGNED_NUMBER, 0);
}

tree::TerminalNode* StcParser::ArrayElementContext::NUMBER() {
  return getToken(StcParser::NUMBER, 0);
}

tree::TerminalNode* StcParser::ArrayElementContext::SIGNED_FLOAT() {
  return getToken(StcParser::SIGNED_FLOAT, 0);
}

tree::TerminalNode* StcParser::ArrayElementContext::FLOAT() {
  return getToken(StcParser::FLOAT, 0);
}

tree::TerminalNode* StcParser::ArrayElementContext::SIGNED_FLOAT_E() {
  return getToken(StcParser::SIGNED_FLOAT_E, 0);
}

tree::TerminalNode* StcParser::ArrayElementContext::FLOAT_E() {
  return getToken(StcParser::FLOAT_E, 0);
}

tree::TerminalNode* StcParser::ArrayElementContext::BIN_NUMBER() {
  return getToken(StcParser::BIN_NUMBER, 0);
}

tree::TerminalNode* StcParser::ArrayElementContext::HEX_NUMBER() {
  return getToken(StcParser::HEX_NUMBER, 0);
}

tree::TerminalNode* StcParser::ArrayElementContext::CHAR() {
  return getToken(StcParser::CHAR, 0);
}

tree::TerminalNode* StcParser::ArrayElementContext::STRING() {
  return getToken(StcParser::STRING, 0);
}

tree::TerminalNode* StcParser::ArrayElementContext::BOOL() {
  return getToken(StcParser::BOOL, 0);
}

tree::TerminalNode* StcParser::ArrayElementContext::SIMPLE_TYPE() {
  return getToken(StcParser::SIMPLE_TYPE, 0);
}

StcParser::ArrayIndexContext* StcParser::ArrayElementContext::arrayIndex() {
  return getRuleContext<StcParser::ArrayIndexContext>(0);
}

StcParser::VarIdentifierContext* StcParser::ArrayElementContext::varIdentifier() {
  return getRuleContext<StcParser::VarIdentifierContext>(0);
}

StcParser::ArrayContext* StcParser::ArrayElementContext::array() {
  return getRuleContext<StcParser::ArrayContext>(0);
}


size_t StcParser::ArrayElementContext::getRuleIndex() const {
  return StcParser::RuleArrayElement;
}

void StcParser::ArrayElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayElement(this);
}

void StcParser::ArrayElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayElement(this);
}


std::any StcParser::ArrayElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitArrayElement(this);
  else
    return visitor->visitChildren(this);
}

StcParser::ArrayElementContext* StcParser::arrayElement() {
  ArrayElementContext *_localctx = _tracker.createInstance<ArrayElementContext>(_ctx, getState());
  enterRule(_localctx, 36, StcParser::RuleArrayElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(189);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(174);
      match(StcParser::SIGNED_NUMBER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(175);
      match(StcParser::NUMBER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(176);
      match(StcParser::SIGNED_FLOAT);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(177);
      match(StcParser::FLOAT);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(178);
      match(StcParser::SIGNED_FLOAT_E);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(179);
      match(StcParser::FLOAT_E);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(180);
      match(StcParser::BIN_NUMBER);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(181);
      match(StcParser::HEX_NUMBER);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(182);
      match(StcParser::CHAR);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(183);
      match(StcParser::STRING);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(184);
      match(StcParser::BOOL);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(185);
      match(StcParser::SIMPLE_TYPE);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(186);
      arrayIndex();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(187);
      varIdentifier();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(188);
      array();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayBaseContext ------------------------------------------------------------------

StcParser::ArrayBaseContext::ArrayBaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StcParser::VarIdentifierContext* StcParser::ArrayBaseContext::varIdentifier() {
  return getRuleContext<StcParser::VarIdentifierContext>(0);
}


size_t StcParser::ArrayBaseContext::getRuleIndex() const {
  return StcParser::RuleArrayBase;
}

void StcParser::ArrayBaseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayBase(this);
}

void StcParser::ArrayBaseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayBase(this);
}


std::any StcParser::ArrayBaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitArrayBase(this);
  else
    return visitor->visitChildren(this);
}

StcParser::ArrayBaseContext* StcParser::arrayBase() {
  ArrayBaseContext *_localctx = _tracker.createInstance<ArrayBaseContext>(_ctx, getState());
  enterRule(_localctx, 38, StcParser::RuleArrayBase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(191);
    varIdentifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayIndexShiftContext ------------------------------------------------------------------

StcParser::ArrayIndexShiftContext::ArrayIndexShiftContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::ArrayIndexShiftContext::NUMBER() {
  return getToken(StcParser::NUMBER, 0);
}

StcParser::VarIdentifierContext* StcParser::ArrayIndexShiftContext::varIdentifier() {
  return getRuleContext<StcParser::VarIdentifierContext>(0);
}


size_t StcParser::ArrayIndexShiftContext::getRuleIndex() const {
  return StcParser::RuleArrayIndexShift;
}

void StcParser::ArrayIndexShiftContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayIndexShift(this);
}

void StcParser::ArrayIndexShiftContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayIndexShift(this);
}


std::any StcParser::ArrayIndexShiftContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitArrayIndexShift(this);
  else
    return visitor->visitChildren(this);
}

StcParser::ArrayIndexShiftContext* StcParser::arrayIndexShift() {
  ArrayIndexShiftContext *_localctx = _tracker.createInstance<ArrayIndexShiftContext>(_ctx, getState());
  enterRule(_localctx, 40, StcParser::RuleArrayIndexShift);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(195);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StcParser::NUMBER: {
        setState(193);
        match(StcParser::NUMBER);
        break;
      }

      case StcParser::ID: {
        setState(194);
        varIdentifier();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayIndexContext ------------------------------------------------------------------

StcParser::ArrayIndexContext::ArrayIndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StcParser::ArrayBaseContext* StcParser::ArrayIndexContext::arrayBase() {
  return getRuleContext<StcParser::ArrayBaseContext>(0);
}

tree::TerminalNode* StcParser::ArrayIndexContext::AT() {
  return getToken(StcParser::AT, 0);
}

StcParser::ArrayIndexShiftContext* StcParser::ArrayIndexContext::arrayIndexShift() {
  return getRuleContext<StcParser::ArrayIndexShiftContext>(0);
}


size_t StcParser::ArrayIndexContext::getRuleIndex() const {
  return StcParser::RuleArrayIndex;
}

void StcParser::ArrayIndexContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayIndex(this);
}

void StcParser::ArrayIndexContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayIndex(this);
}


std::any StcParser::ArrayIndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitArrayIndex(this);
  else
    return visitor->visitChildren(this);
}

StcParser::ArrayIndexContext* StcParser::arrayIndex() {
  ArrayIndexContext *_localctx = _tracker.createInstance<ArrayIndexContext>(_ctx, getState());
  enterRule(_localctx, 42, StcParser::RuleArrayIndex);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(197);
    arrayBase();
    setState(198);
    match(StcParser::AT);
    setState(199);
    arrayIndexShift();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CapacityContext ------------------------------------------------------------------

StcParser::CapacityContext::CapacityContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::CapacityContext::NUMBER() {
  return getToken(StcParser::NUMBER, 0);
}


size_t StcParser::CapacityContext::getRuleIndex() const {
  return StcParser::RuleCapacity;
}

void StcParser::CapacityContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCapacity(this);
}

void StcParser::CapacityContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCapacity(this);
}


std::any StcParser::CapacityContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitCapacity(this);
  else
    return visitor->visitChildren(this);
}

StcParser::CapacityContext* StcParser::capacity() {
  CapacityContext *_localctx = _tracker.createInstance<CapacityContext>(_ctx, getState());
  enterRule(_localctx, 44, StcParser::RuleCapacity);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    match(StcParser::T__16);
    setState(202);
    match(StcParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayContext ------------------------------------------------------------------

StcParser::ArrayContext::ArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::ArrayContext::ARRAY_OPEN() {
  return getToken(StcParser::ARRAY_OPEN, 0);
}

tree::TerminalNode* StcParser::ArrayContext::ARRAY_CLOSE() {
  return getToken(StcParser::ARRAY_CLOSE, 0);
}

std::vector<StcParser::ArrayElementContext *> StcParser::ArrayContext::arrayElement() {
  return getRuleContexts<StcParser::ArrayElementContext>();
}

StcParser::ArrayElementContext* StcParser::ArrayContext::arrayElement(size_t i) {
  return getRuleContext<StcParser::ArrayElementContext>(i);
}

StcParser::CapacityContext* StcParser::ArrayContext::capacity() {
  return getRuleContext<StcParser::CapacityContext>(0);
}


size_t StcParser::ArrayContext::getRuleIndex() const {
  return StcParser::RuleArray;
}

void StcParser::ArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArray(this);
}

void StcParser::ArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArray(this);
}


std::any StcParser::ArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitArray(this);
  else
    return visitor->visitChildren(this);
}

StcParser::ArrayContext* StcParser::array() {
  ArrayContext *_localctx = _tracker.createInstance<ArrayContext>(_ctx, getState());
  enterRule(_localctx, 46, StcParser::RuleArray);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(204);
    match(StcParser::ARRAY_OPEN);
    setState(206); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(205);
      arrayElement();
      setState(208); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4681512255488) != 0));
    setState(210);
    match(StcParser::ARRAY_CLOSE);
    setState(212);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StcParser::T__16) {
      setState(211);
      capacity();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayDescriberContext ------------------------------------------------------------------

StcParser::ArrayDescriberContext::ArrayDescriberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::ArrayDescriberContext::ARRAY_OPEN() {
  return getToken(StcParser::ARRAY_OPEN, 0);
}

tree::TerminalNode* StcParser::ArrayDescriberContext::NUMBER() {
  return getToken(StcParser::NUMBER, 0);
}

tree::TerminalNode* StcParser::ArrayDescriberContext::ARRAY_CLOSE() {
  return getToken(StcParser::ARRAY_CLOSE, 0);
}


size_t StcParser::ArrayDescriberContext::getRuleIndex() const {
  return StcParser::RuleArrayDescriber;
}

void StcParser::ArrayDescriberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayDescriber(this);
}

void StcParser::ArrayDescriberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayDescriber(this);
}


std::any StcParser::ArrayDescriberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitArrayDescriber(this);
  else
    return visitor->visitChildren(this);
}

StcParser::ArrayDescriberContext* StcParser::arrayDescriber() {
  ArrayDescriberContext *_localctx = _tracker.createInstance<ArrayDescriberContext>(_ctx, getState());
  enterRule(_localctx, 48, StcParser::RuleArrayDescriber);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(214);
    match(StcParser::ARRAY_OPEN);
    setState(215);
    match(StcParser::NUMBER);
    setState(216);
    match(StcParser::ARRAY_CLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayNewContext ------------------------------------------------------------------

StcParser::ArrayNewContext::ArrayNewContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::ArrayNewContext::ARRAY_OPERATOR() {
  return getToken(StcParser::ARRAY_OPERATOR, 0);
}

std::vector<StcParser::ArrayDescriberContext *> StcParser::ArrayNewContext::arrayDescriber() {
  return getRuleContexts<StcParser::ArrayDescriberContext>();
}

StcParser::ArrayDescriberContext* StcParser::ArrayNewContext::arrayDescriber(size_t i) {
  return getRuleContext<StcParser::ArrayDescriberContext>(i);
}


size_t StcParser::ArrayNewContext::getRuleIndex() const {
  return StcParser::RuleArrayNew;
}

void StcParser::ArrayNewContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayNew(this);
}

void StcParser::ArrayNewContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayNew(this);
}


std::any StcParser::ArrayNewContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitArrayNew(this);
  else
    return visitor->visitChildren(this);
}

StcParser::ArrayNewContext* StcParser::arrayNew() {
  ArrayNewContext *_localctx = _tracker.createInstance<ArrayNewContext>(_ctx, getState());
  enterRule(_localctx, 50, StcParser::RuleArrayNew);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
    match(StcParser::ARRAY_OPERATOR);
    setState(219);
    arrayDescriber();
    setState(221);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      setState(220);
      arrayDescriber();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentContext ------------------------------------------------------------------

StcParser::ArgumentContext::ArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::ArgumentContext::ID() {
  return getToken(StcParser::ID, 0);
}

StcParser::VarTypeContext* StcParser::ArgumentContext::varType() {
  return getRuleContext<StcParser::VarTypeContext>(0);
}


size_t StcParser::ArgumentContext::getRuleIndex() const {
  return StcParser::RuleArgument;
}

void StcParser::ArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgument(this);
}

void StcParser::ArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgument(this);
}


std::any StcParser::ArgumentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitArgument(this);
  else
    return visitor->visitChildren(this);
}

StcParser::ArgumentContext* StcParser::argument() {
  ArgumentContext *_localctx = _tracker.createInstance<ArgumentContext>(_ctx, getState());
  enterRule(_localctx, 52, StcParser::RuleArgument);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    match(StcParser::ID);
    setState(225);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StcParser::T__1) {
      setState(224);
      varType();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarAssignContext ------------------------------------------------------------------

StcParser::VarAssignContext::VarAssignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::VarAssignContext::ASSIGN_OPERATOR() {
  return getToken(StcParser::ASSIGN_OPERATOR, 0);
}

StcParser::VarAssignIdentifierContext* StcParser::VarAssignContext::varAssignIdentifier() {
  return getRuleContext<StcParser::VarAssignIdentifierContext>(0);
}

StcParser::ArrayIndexContext* StcParser::VarAssignContext::arrayIndex() {
  return getRuleContext<StcParser::ArrayIndexContext>(0);
}

StcParser::IdentifierContext* StcParser::VarAssignContext::identifier() {
  return getRuleContext<StcParser::IdentifierContext>(0);
}


size_t StcParser::VarAssignContext::getRuleIndex() const {
  return StcParser::RuleVarAssign;
}

void StcParser::VarAssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarAssign(this);
}

void StcParser::VarAssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarAssign(this);
}


std::any StcParser::VarAssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitVarAssign(this);
  else
    return visitor->visitChildren(this);
}

StcParser::VarAssignContext* StcParser::varAssign() {
  VarAssignContext *_localctx = _tracker.createInstance<VarAssignContext>(_ctx, getState());
  enterRule(_localctx, 54, StcParser::RuleVarAssign);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(230);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      setState(227);
      varAssignIdentifier();
      break;
    }

    case 2: {
      setState(228);
      arrayIndex();
      break;
    }

    case 3: {
      setState(229);
      identifier();
      break;
    }

    default:
      break;
    }
    setState(232);
    match(StcParser::ASSIGN_OPERATOR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarAssignIdentifierContext ------------------------------------------------------------------

StcParser::VarAssignIdentifierContext::VarAssignIdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StcParser::VarIdentifierContext* StcParser::VarAssignIdentifierContext::varIdentifier() {
  return getRuleContext<StcParser::VarIdentifierContext>(0);
}

StcParser::VarTypeContext* StcParser::VarAssignIdentifierContext::varType() {
  return getRuleContext<StcParser::VarTypeContext>(0);
}


size_t StcParser::VarAssignIdentifierContext::getRuleIndex() const {
  return StcParser::RuleVarAssignIdentifier;
}

void StcParser::VarAssignIdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarAssignIdentifier(this);
}

void StcParser::VarAssignIdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarAssignIdentifier(this);
}


std::any StcParser::VarAssignIdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitVarAssignIdentifier(this);
  else
    return visitor->visitChildren(this);
}

StcParser::VarAssignIdentifierContext* StcParser::varAssignIdentifier() {
  VarAssignIdentifierContext *_localctx = _tracker.createInstance<VarAssignIdentifierContext>(_ctx, getState());
  enterRule(_localctx, 56, StcParser::RuleVarAssignIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    varIdentifier();
    setState(235);
    varType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarTypeContext ------------------------------------------------------------------

StcParser::VarTypeContext::VarTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StcParser::TypeContext* StcParser::VarTypeContext::type() {
  return getRuleContext<StcParser::TypeContext>(0);
}


size_t StcParser::VarTypeContext::getRuleIndex() const {
  return StcParser::RuleVarType;
}

void StcParser::VarTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarType(this);
}

void StcParser::VarTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarType(this);
}


std::any StcParser::VarTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitVarType(this);
  else
    return visitor->visitChildren(this);
}

StcParser::VarTypeContext* StcParser::varType() {
  VarTypeContext *_localctx = _tracker.createInstance<VarTypeContext>(_ctx, getState());
  enterRule(_localctx, 58, StcParser::RuleVarType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(237);
    match(StcParser::T__1);
    setState(238);
    type();
    setState(239);
    match(StcParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarReferenceContext ------------------------------------------------------------------

StcParser::VarReferenceContext::VarReferenceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StcParser::VarReferenceContext::REFERENCE_OPERATOR() {
  return getToken(StcParser::REFERENCE_OPERATOR, 0);
}

StcParser::VarIdentifierContext* StcParser::VarReferenceContext::varIdentifier() {
  return getRuleContext<StcParser::VarIdentifierContext>(0);
}


size_t StcParser::VarReferenceContext::getRuleIndex() const {
  return StcParser::RuleVarReference;
}

void StcParser::VarReferenceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarReference(this);
}

void StcParser::VarReferenceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarReference(this);
}


std::any StcParser::VarReferenceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitVarReference(this);
  else
    return visitor->visitChildren(this);
}

StcParser::VarReferenceContext* StcParser::varReference() {
  VarReferenceContext *_localctx = _tracker.createInstance<VarReferenceContext>(_ctx, getState());
  enterRule(_localctx, 60, StcParser::RuleVarReference);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(241);
    match(StcParser::REFERENCE_OPERATOR);
    setState(242);
    varIdentifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarIdentifierContext ------------------------------------------------------------------

StcParser::VarIdentifierContext::VarIdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> StcParser::VarIdentifierContext::ID() {
  return getTokens(StcParser::ID);
}

tree::TerminalNode* StcParser::VarIdentifierContext::ID(size_t i) {
  return getToken(StcParser::ID, i);
}


size_t StcParser::VarIdentifierContext::getRuleIndex() const {
  return StcParser::RuleVarIdentifier;
}

void StcParser::VarIdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarIdentifier(this);
}

void StcParser::VarIdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarIdentifier(this);
}


std::any StcParser::VarIdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitVarIdentifier(this);
  else
    return visitor->visitChildren(this);
}

StcParser::VarIdentifierContext* StcParser::varIdentifier() {
  VarIdentifierContext *_localctx = _tracker.createInstance<VarIdentifierContext>(_ctx, getState());
  enterRule(_localctx, 62, StcParser::RuleVarIdentifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(244);
    match(StcParser::ID);
    setState(251);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StcParser::T__5) {
      setState(247); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(245);
        match(StcParser::T__5);
        setState(246);
        match(StcParser::ID);
        setState(249); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == StcParser::T__5);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

StcParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> StcParser::IdentifierContext::ID() {
  return getTokens(StcParser::ID);
}

tree::TerminalNode* StcParser::IdentifierContext::ID(size_t i) {
  return getToken(StcParser::ID, i);
}

tree::TerminalNode* StcParser::IdentifierContext::STACK_PREVENTION() {
  return getToken(StcParser::STACK_PREVENTION, 0);
}


size_t StcParser::IdentifierContext::getRuleIndex() const {
  return StcParser::RuleIdentifier;
}

void StcParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void StcParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<StcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}


std::any StcParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StcVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

StcParser::IdentifierContext* StcParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 64, StcParser::RuleIdentifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StcParser::STACK_PREVENTION) {
      setState(253);
      match(StcParser::STACK_PREVENTION);
    }
    setState(256);
    match(StcParser::ID);
    setState(263);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StcParser::T__5) {
      setState(259); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(257);
        match(StcParser::T__5);
        setState(258);
        match(StcParser::ID);
        setState(261); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == StcParser::T__5);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void StcParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  stcParserInitialize();
#else
  ::antlr4::internal::call_once(stcParserOnceFlag, stcParserInitialize);
#endif
}
