//
// Created by julian on 7/7/25.
//

#include "error.h"

#include <stdexcept>

const char *ParserError::what() const noexcept
{
    return fullMessage.c_str();
}

std::string getWholeLine(Token* token) {
    CharStream* input = token->getInputStream();
    if (!input) return "";

    size_t inputSize = input->size();
    size_t startIdx = token->getStartIndex();

    // Scan backwards to find start of line
    size_t begin = startIdx;
    while (begin > 0) {
        char ch = input->getText(misc::Interval(begin, begin))[0];
        if (ch == '\n' || ch == '\r') {
            begin++; // move to first character after newline
            break;
        }
        --begin;
    }

    // Scan forward to find end of line
    size_t end = startIdx;
    while (end < inputSize - 1) {
        char ch = input->getText(misc::Interval(end + 1, end + 1))[0];
        if (ch == '\n' || ch == '\r') {
            break;
        }
        ++end;
    }

    return input->getText(misc::Interval(begin, end));
}