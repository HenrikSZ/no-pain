#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>

#include "expressions.h"


class Parser {
public:
    Parser(std::unique_ptr<Tokenizer> tokenizer): tokenizer(std::move(tokenizer)) {}
    std::unique_ptr<Expression> parseExpression();

private:
    std::unique_ptr<Expression> parseBlock();
    std::unique_ptr<Expression> parseAssignment();
    std::unique_ptr<Expression> Parser::parseOr();
    std::unique_ptr<Expression> Parser::parseAnd();
    std::unique_ptr<Expression> parseComparison();
    std::unique_ptr<Expression> parseAddOrSub();
    std::unique_ptr<Expression> parseMulOrDiv();
    std::unique_ptr<Expression> parseIfStatement();
    std::unique_ptr<Expression> parseParentheses();

    std::unique_ptr<Tokenizer> tokenizer;
};


#endif
