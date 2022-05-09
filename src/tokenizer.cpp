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


Tokenizer::Tokenizer(std::unique_ptr<Input> input): input(std::move(input)) {}

std::shared_ptr<Token> Tokenizer::getStringToken() {
    auto ret = std::make_shared<Token>(TokenType::STRING);

    bool escapeNext = false;

    char nextChar = input->getNextChar();
    while (input->hasNext()) {
        nextChar = input->getNextChar();
        if (escapeNext) {
            escapeNext = false;
            switch (nextChar) {
                case 't':
                    ret->payloadStr += '\t';
                    break;
                case 'r':
                    ret->payloadStr += '\r';
                    break;
                case 'n':
                    ret->payloadStr += '\n';
                    break;
                case '"':
                    ret->payloadStr += '"';
                    break;
                case '\\':
                    ret->payloadStr += '\\';
                    break;
                default:
                    throw std::exception("Malformed escape character");
            }
        } else if (nextChar == '"') {
            return ret;
        } else {
            ret->payloadStr += nextChar;
        }
    }
    
    throw std::exception("Reached end of file while tokenizing string");
}

std::shared_ptr<Token> Tokenizer::getNumericalToken() {
    std::string numStr;
    bool isFloat = false;

    char nextChar = input->peekNextChar();
    while (isdigit(nextChar) || nextChar == '.') {
        if (nextChar == '.') {
            if (isFloat)
                throw std::exception("Malformed floating point number");

            isFloat = true;
        }
        numStr += input->getNextChar();
        if (input->hasNext()) nextChar = input->peekNextChar();
        else break;
    }

    if (isFloat) {
        auto ret = std::make_shared<Token>(TokenType::FLOAT);
        ret->payloadFloat = std::stof(numStr);

        return ret;
    } else {
        auto ret = std::make_shared<Token>(TokenType::INT);
        ret->payloadInt = std::stoi(numStr);

        return ret;
    }    
}

std::shared_ptr<Token> Tokenizer::getNameToken() {
   std::string nameStr;

    char nextChar = input->peekNextChar();
    while (isalpha(nextChar)) {
        nameStr += input->getNextChar();

        if (input->hasNext()) nextChar = input->peekNextChar();
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

    if (!input->hasNext()) {
        return std::make_shared<Token>(TokenType::END_OF_FILE);
    }

    char nextChar = input->peekNextChar();
    while (isspace(nextChar) && input->hasNext()) {
        input->getNextChar();
        nextChar = input->peekNextChar();
    }

    if (isspace(nextChar) && !input->hasNext()) {
        return std::make_shared<Token>(TokenType::END_OF_FILE);
    }

    switch (nextChar) {
        case '(':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::OPEN_PAR);
        case ')':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::CLOSE_PAR);
        case ',':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::COMMA);
        case ';':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::END_OF_LINE);
        case '{':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::OPEN_BLOCK);
        case '}':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::CLOSE_BLOCK);
        case '=':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::ASSIGN);
        case '+':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::ADD);
        case '-':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::SUBTRACT);
        case '*':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::MULTIPLY);
        case '/':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::DIVIDE);
        case '%':
            input->getNextChar();
            return std::make_shared<Token>(TokenType::MODULO);
        case '"':
            return getStringToken();
    }

    if (isdigit(nextChar)) {
        return getNumericalToken();
    }

    if (isalpha(nextChar)) {
        return getNameToken();
    }

    throw std::exception("Malformed token");
}


std::shared_ptr<Token> Tokenizer::peekNextToken() {
    if (!nextToken) {
        nextToken = getNextToken();
    }

    return nextToken;
}

