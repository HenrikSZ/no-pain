#ifndef PARSER_H
#define PARSER_H

#include <memory>

#include "expressions.h"

class Parser {
public:
    Parser(std::unique_ptr<Tokenizer> tokenizer): tokenizer(std::move(tokenizer)) {}
    std::unique_ptr<Expression> parseExpression();

private:
    std::unique_ptr<Expression> parseAssignment();
    std::unique_ptr<Expression> parseAddOrSub();
    std::unique_ptr<Expression> parseMulOrDiv();
    std::unique_ptr<Expression> parseParentheses();

    std::unique_ptr<Tokenizer> tokenizer;
};


#endif
