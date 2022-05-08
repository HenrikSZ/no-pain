#include "tokenizer.h"


Token::Token(TokenType tokenType): tokenType(tokenType) {}

TokenType Token::getType() const {
    return tokenType;
}

bool Token::isType(TokenType type) const {
    return tokenType == type;
}

std::ostream& operator << (std::ostream& os, const Token& token) {
    os << "Token" << token.getType();
    return os;
}


Tokenizer::Tokenizer(std::unique_ptr<Input> input): input(std::move(input)) {
}

Tokenizer::~Tokenizer() {
    //
}

std::shared_ptr<Token> Tokenizer::getStringToken() {
    auto ret = std::make_shared<Token>(TokenType::STRING);

    bool escapeNext = false;

    while (input->hasNext()) {
        if (escapeNext) {
            escapeNext = false;
            switch (input->getCurrentChar()) {
                case 't':
                    ret->payloadStr += '\t';
                    break;
                case 'r':
                    ret->payloadStr += '\r';
                    break;
                case 'n':
                    ret->payloadStr += '\n';
                    break;
                default:
                    ret->payloadStr += input->getCurrentChar();
                    break;
            }
        } else if (input->getCurrentChar() == '"') {
            return ret;
        } else {
            ret->payloadStr += input->getCurrentChar();
        }

        input->advance();
    }
    
    throw std::exception("Reached end of file while tokenizing string");
}

std::shared_ptr<Token> Tokenizer::getNumericalToken() {
    std::string numStr;

    while (isdigit(input->getCurrentChar())) {
        numStr += input->getCurrentChar();
        if (input->hasNext()) input->advance();
        else break;
    }

    auto ret = std::make_shared<Token>(TokenType::INT);
    ret->payloadInt = std::stoi(numStr);

    return ret;
}

std::shared_ptr<Token> Tokenizer::getNameToken() {
   std::string nameStr;

    while (isalpha(input->getCurrentChar())) {
        nameStr += input->getCurrentChar();

        if (input->hasNext()) input->advance();
        else break;
    }

    if (nameStr == "IF") {
        return std::make_shared<Token>(TokenType::IF);
    } else if (nameStr == "ELSE") {
        return std::make_shared<Token>(TokenType::ELSE);
    } else if (nameStr == "FOR") {
        return std::make_shared<Token>(TokenType::FOR);
    } else if (nameStr == "WHILE") {
        return std::make_shared<Token>(TokenType::WHILE);
    } else if (nameStr == "FUN") {
        return std::make_shared<Token>(TokenType::FUN);
    }

    auto ret = std::make_shared<Token>(TokenType::NAME);
    ret->payloadStr = nameStr;

    return ret;
}


std::shared_ptr<Token> Tokenizer::getNextToken() {
    if (nextToken) {
        auto ret = nextToken;
        nextToken = nullptr;
        return ret;
    }

    input->advance();
    while (input->hasNext() && isspace(input->getCurrentChar())) {
        input->advance();
    }

    if (!input->hasNext()) {
        return std::make_shared<Token>(TokenType::END_OF_FILE);
    }

    switch (input->getCurrentChar()) {
        case '(':
            return std::make_shared<Token>(TokenType::OPEN_PAR);
        case ')':
            return std::make_shared<Token>(TokenType::OPEN_PAR);
        case ',':
            return std::make_shared<Token>(TokenType::COMMA);
        case '{':
            return std::make_shared<Token>(TokenType::OPEN_BLOCK);
        case '}':
            return std::make_shared<Token>(TokenType::CLOSE_BLOCK);
        case '+':
            return std::make_shared<Token>(TokenType::ADD);
        case '-':
            return std::make_shared<Token>(TokenType::SUBTRACT);
        case '*':
            return std::make_shared<Token>(TokenType::MULTIPLY);
        case '/':
            return std::make_shared<Token>(TokenType::DIVIDE);
        case '%':
            return std::make_shared<Token>(TokenType::MODULO);
        case '"':
            return getStringToken();
    }

    if (isdigit(input->getCurrentChar())) {
        return getNumericalToken();
    }

    if (isalpha(input->getCurrentChar())) {
        return getNameToken();
    }

    throw std::exception("");
}

