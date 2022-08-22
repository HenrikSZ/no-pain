#ifndef PARSER_H
#define PARSER_H


#include <memory>
#include <vector>

#include "expressions.h"


/**
 * @brief Parser to turn no-pain code scripts into an expression tree.
 * 
 */
class Parser {
public:
    /**
     * @brief Construct a new Parser object
     * 
     * @param tokenizer The tokenizer from which tokens should be obtained.
     */
    Parser(std::unique_ptr<Tokenizer>& tokenizer);

    /**
     * @brief Parse all tokens retrievable from the tokenizer
     * 
     * @return std::unique_ptr<Expression> the Expression Tree created from all
     * tokens
     */
    std::unique_ptr<Expression> parseAll();

    /**
     * @brief Parse one expression.
     * 
     * @return std::unique_ptr<Expression> The expression that has been parsed.
     */
    std::unique_ptr<Expression> parseExpression();

private:
    /**
     * @brief Attempt to parse a block of expressions.
     * 
     * @return std::unique_ptr<Expression> the parsed block, or any other
     * expression further down the priority tree.
     */
    std::unique_ptr<Expression> parseBlock();

    /**
     * @brief Attempt to parse an assignment statement.
     * 
     * @return std::unique_ptr<Expression> the parsed assignment, or any other
     * expression further down the priority tree.
     */
    std::unique_ptr<Expression> parseAssignment();

    /**
     * @brief Attempt to parse an or expression.
     * 
     * @return std::unique_ptr<Expression> the parsed or expression, or any
     * other expression further down the priority tree.
     */
    std::unique_ptr<Expression> parseOr();

    /**
     * @brief Attempt to parse an and expression.
     * 
     * @return std::unique_ptr<Expression> the parsed and expression, or any
     * other expression further down the priority tree.
     */
    std::unique_ptr<Expression> parseAnd();

    /**
     * @brief Attempt to parse a comparison expression.
     * 
     * @return std::unique_ptr<Expression> the parsed comparison expression,
     * or any other expression further down the priority tree.
     */
    std::unique_ptr<Expression> parseComparison();

    /**
     * @brief Attempt to parse an addition or subtraction expression.
     * 
     * @return std::unique_ptr<Expression> the parsed addition/subtraction
     * expression, or any other expression further down the priority tree.
     */
    std::unique_ptr<Expression> parseAddOrSub();

    /**
     * @brief Attempt to parse a multiplication or division expression.
     * 
     * @return std::unique_ptr<Expression> the parsed multiplication/division
     * expression, or any other expression further down the priority tree.
     */
    std::unique_ptr<Expression> parseMulOrDiv();

    /**
     * @brief Attempt to parse a function declaration expression.
     * 
     * @return std::unique_ptr<Expression> the parsed function declaration
     * expression, or any other expression further down the priority tree.
     */
    std::unique_ptr<Expression> parseFunctionDeclaration();

    /**
     * @brief Attempt to parse an if expression.
     * 
     * @return std::unique_ptr<Expression> the parsed if
     * expression, or any other expression further down the priority tree.
     */
    std::unique_ptr<Expression> parseIfExpression();

    /**
     * @brief Attempt to parse an invocation expression.
     * 
     * @return std::unique_ptr<Expression> the parsed invocation
     * expression, or any other expression further down the priority tree.
     */
    std::unique_ptr<Expression> parseInvocation();

    /**
     * @brief Attempt to parse parentheses which have priority over anything
     * else.
     * 
     * @return std::unique_ptr<Expression> the parsed expression which was
     * surrounded by parentheses.
     */
    std::unique_ptr<Expression> parseParentheses();

    /**
     * @brief The tokenizer to use to retrieve all tokens.
     * 
     */
    std::unique_ptr<Tokenizer> tokenizer;
};


#endif
