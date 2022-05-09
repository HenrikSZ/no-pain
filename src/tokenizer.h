#ifndef TOKENIZER_H
#define TOKENIZER_H


#include <string>
#include <fstream>
#include <sstream>
#include <memory>

#include "input.h"


enum class TokenType {
    UNKNOWN,
    END_OF_FILE,
    END_OF_LINE,
    COMMA,
    RETURN,
    OPEN_PAR,
    CLOSE_PAR,
    OPEN_BLOCK,
    CLOSE_BLOCK,
    NAME,
    INT,
    FLOAT,
    STRING,
    IF,
    ELSE,
    FOR,
    WHILE,
    FUN,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    ASSIGN,
    EQUALS,
    GREATER,
    GREATER_OR_EQUALS,
    LESS,
    LESS_OR_EQUAL,
    NOT,
    AND,
    OR,
    MODULO
};

class Token {
public:
    Token(TokenType tokenType);
    TokenType getType() const;
    bool isType(TokenType tokenType) const;

    std::string payloadStr;
    int payloadInt;
    float payloadFloat;

private:
    TokenType tokenType;
};

std::ostream& operator << (std::ostream& outs, const Token& token);


class Tokenizer {
public:
    Tokenizer(std::unique_ptr<Input> input);
    ~Tokenizer();

    std::shared_ptr<Token> peekNextToken();
    std::shared_ptr<Token> getNextToken();
private:
    std::shared_ptr<Token> getStringToken();
    std::shared_ptr<Token> getNumericalToken();
    std::shared_ptr<Token> getNameToken();
    std::unique_ptr<Input> input;
    std::shared_ptr<Token> nextToken;
};

#endif
