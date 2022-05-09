#include "parser.h"


std::unique_ptr<Expression> Parser::parseParentheses() {
    auto left = tokenizer->peekNextToken();

    if (left->isType(TokenType::OPEN_PAR)) {
        tokenizer->getNextToken();
        auto ret = parseLine();
        tokenizer->getNextToken(); // Remove closing parentheses
        return ret;
    } else if (left->isType(TokenType::INT) || left->isType(TokenType::FLOAT)) {
        tokenizer->getNextToken();
        return std::make_unique<Literal>(*left);
    } else {
        throw std::exception("Multiplication/Division: Wrong type for left operand");
    }
}


std::unique_ptr<Expression> Parser::parseMulOrDiv() {
    auto l_operand = parseParentheses();

    auto middle = tokenizer->peekNextToken();
    if (middle->isType(TokenType::MULTIPLY)) {
        tokenizer->getNextToken();
        return std::make_unique<Multiplication>(std::move(l_operand), parseLine());
    } else if (middle->isType(TokenType::DIVIDE)) {
        tokenizer->getNextToken();
        return std::make_unique<Division>(std::move(l_operand), parseLine());
    }

    return l_operand;
}

std::unique_ptr<Expression> Parser::parseAddOrSub() {
    auto l_operand = parseMulOrDiv();

    auto middle = tokenizer->peekNextToken();
    if (middle->isType(TokenType::ADD)) {
        tokenizer->getNextToken();
        return std::make_unique<Addition>(std::move(l_operand), parseLine());
    } else if (middle->isType(TokenType::SUBTRACT)) {
        tokenizer->getNextToken();
        return std::make_unique<Subtraction>(std::move(l_operand), parseLine());
    }

    return l_operand;
}

std::unique_ptr<Expression> Parser::parseLine() {
    return parseAddOrSub();
}