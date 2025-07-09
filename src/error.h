//
// Created by julian on 7/7/25.
//

#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <antlr4-runtime.h>

void throwParserError(const std::string& file, const std::string& line, int lineNumber, const std::string& msg);



using namespace antlr4;
class ParserError : public std::exception {
    std::string message, file, line, fullMessage;
    int lineNumber;
public:
    explicit ParserError(const std::string& file, const std::string& line, const int lineNumber, const std::string& msg) : message(msg), file(file), line(line), lineNumber(lineNumber)
    {
        fullMessage = ("\n"+file + ": " + std::to_string(lineNumber) + ":\n "+ line+"\n\tERROR\n\t"+message);
    }
    const char* what() const noexcept override;
};
std::string getWholeLine(Token* token);
#endif //ERROR_H
