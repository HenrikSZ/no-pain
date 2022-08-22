#ifndef TOKENIZER_H
#define TOKENIZER_H


#include <string>
#include <fstream>
#include <sstream>
#include <memory>

#include "input.h"


/**
 * @brief The type of a token.
 * 
 */
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
    LESS_OR_EQUALS,
    NOT_EQUALS,
    NOT,
    AND,
    OR,
    MODULO
};

/**
 * @brief A token that represents either literals or operation indicators.
 * 
 */
class Token {
public:
    /**
     * @brief Construct a new Token object.
     * 
     * @param tokenType the type of the token.
     */
    Token(TokenType tokenType);

    /**
     * @brief Get the type of this token.
     * 
     * @return TokenType the type of this token.
     */
    TokenType getType() const;

    /**
     * @brief Check if a token is a certain type.
     * 
     * @param tokenType the type that should be checked against.
     * @return true if <tokenType> and the type of this token match.
     * @return false otherwise.
     */
    bool isType(TokenType tokenType) const;

    /**
     * @brief The string this token holds if its type is any of
     * NAME, STRING.
     * 
     */
    std::string payloadStr;

    /**
     * @brief The int this token holds if its type is INT.
     * 
     */
    int payloadInt;

    /**
     * @brief The int this token holds it its type is FLOAT.
     * 
     */
    float payloadFloat;

private:
    /**
     * @brief The type of this token.
     * 
     */
    TokenType tokenType;
};


/**
 * @brief Tokenizer to create a stream of tokens from an input.
 * 
 */
class Tokenizer {
public:
    /**
     * @brief Construct a new Tokenizer object.
     * 
     * @param input the input to retrieve characters from.
     */
    Tokenizer(std::unique_ptr<Input>& input);

    /**
     * @brief Peek at the next token without advancing to it.
     * 
     * @return std::shared_ptr<Token> the token that is coming up next.
     */
    std::shared_ptr<Token> peekNextToken();

    /**
     * @brief Advance to the next token and return it.
     * 
     * @return std::shared_ptr<Token> the token that is coming up next.
     */
    std::shared_ptr<Token> getNextToken();
    
private:
    /**
     * @brief Construct a string token from the upcoming characters.
     * 
     * @return std::shared_ptr<Token> the contructed string token.
     */
    std::shared_ptr<Token> getStringToken();
    /**
     * @brief Construct a numerical token from the upcoming characters.
     * 
     * @return std::shared_ptr<Token> the contructed int or float token.
     */
    std::shared_ptr<Token> getNumericalToken();
    /**
     * @brief Construct a name token from the upcoming characters.
     * 
     * @return std::shared_ptr<Token> the contructed name token.
     */
    std::shared_ptr<Token> getNameToken();

    /**
     * @brief the input to retrieve characters from.
     * 
     */
    std::unique_ptr<Input> input;

    /**
     * @brief the next token if it has already been peeked.
     * 
     */
    std::shared_ptr<Token> nextToken;
};

#endif
