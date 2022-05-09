#include "parser.h"


std::unique_ptr<Expression> Parser::parseParentheses() {
    auto left = tokenizer->peekNextToken();

    if (left->isType(TokenType::OPEN_PAR)) {
        tokenizer->getNextToken();
        auto ret = parseExpression();
        tokenizer->getNextToken(); // Remove closing parentheses
        return ret;
    } else if (left->isType(TokenType::NAME)) {
        tokenizer->getNextToken();
        return std::make_unique<Name>(*left);
    } else if (left->isType(TokenType::INT) || left->isType(TokenType::FLOAT)) {
        tokenizer->getNextToken();
        return std::make_unique<Literal>(*left);
    } else {
        throw std::exception("Wrong type for left operand");
    }
}


std::unique_ptr<Expression> Parser::parseMulOrDiv() {
    auto leftOperand = parseParentheses();

    auto middle = tokenizer->peekNextToken();
    if (middle->isType(TokenType::MULTIPLY)) {
        tokenizer->getNextToken();
        return std::make_unique<Multiplication>(std::move(leftOperand), parseExpression());
    } else if (middle->isType(TokenType::DIVIDE)) {
        tokenizer->getNextToken();
        return std::make_unique<Division>(std::move(leftOperand), parseExpression());
    }

    return leftOperand;
}

std::unique_ptr<Expression> Parser::parseAddOrSub() {
    auto leftOperand = parseMulOrDiv();

    auto middle = tokenizer->peekNextToken();
    if (middle->isType(TokenType::ADD)) {
        tokenizer->getNextToken();
        return std::make_unique<Addition>(std::move(leftOperand), parseExpression());
    } else if (middle->isType(TokenType::SUBTRACT)) {
        tokenizer->getNextToken();
        return std::make_unique<Subtraction>(std::move(leftOperand), parseExpression());
    }

    return leftOperand;
}

std::unique_ptr<Expression> Parser::parseAssignment() {
    auto left = tokenizer->peekNextToken();
    auto leftOperand = parseAddOrSub();

    auto middle = tokenizer->peekNextToken();

    if (left->isType(TokenType::NAME) && middle->isType(TokenType::ASSIGN)) {
        auto name = std::make_unique<Name>(*left);
        tokenizer->getNextToken();
        return std::make_unique<Assignment>(std::move(name), parseExpression());
    } else {
        return leftOperand;
    }
}

std::unique_ptr<Expression> Parser::parseBlock() {
    auto token = tokenizer->getNextToken();
    auto block = std::make_unique<Block>();

    while (!token->isType(TokenType::END_OF_FILE)
            && !token->isType(TokenType::CLOSE_BLOCK)) {
        block->addExpression(parseExpression());
        
        token = tokenizer->getNextToken();
    }

    if (token->isType(TokenType::END_OF_FILE)) {
        throw std::exception("Block not closed");
    }

    return block;
}

std::unique_ptr<Expression> Parser::parseExpression() {
    auto token = tokenizer->peekNextToken();

    if (token->isType(TokenType::OPEN_BLOCK)) {
        return parseBlock();
    } else {
        return parseAssignment();
    }
}
