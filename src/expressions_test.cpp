#include <gtest/gtest.h>
#include "expressions.h"


TEST(Expression, LiteralInit) {
    Environment env;

    Token token(TokenType::INT);
    token.payloadInt = 10;

    Literal literal(token);
    auto value = literal.evaluate(env);

    ASSERT_EQ(value->type, ExpressionValueType::INT);
    ASSERT_EQ(value->payloadInt, 10);
}


TEST(Expression, AdditionEvaluationSimple) {
    Environment env;

    Token leftToken(TokenType::INT);
    leftToken.payloadInt = 10;

    Token rightToken(TokenType::INT);
    rightToken.payloadInt = 10;

    std::unique_ptr<Expression> leftLiteral = std::make_unique<Literal>(leftToken);
    std::unique_ptr<Expression> rightLiteral = std::make_unique<Literal>(rightToken);

    Addition addition(std::move(leftLiteral), std::move(rightLiteral));
    auto value = addition.evaluate(env);

    ASSERT_EQ(value->type, ExpressionValueType::INT);
    ASSERT_EQ(value->payloadInt, 20);
}


TEST(Expression, MultiplicationEvaluationSimple) {
    Environment env;

    Token leftToken(TokenType::INT);
    leftToken.payloadInt = 10;

    Token rightToken(TokenType::INT);
    rightToken.payloadInt = 10;

    std::unique_ptr<Expression> leftLiteral = std::make_unique<Literal>(leftToken);
    std::unique_ptr<Expression> rightLiteral = std::make_unique<Literal>(rightToken);

    Multiplication multiplication(std::move(leftLiteral), std::move(rightLiteral));
    auto value = multiplication.evaluate(env);

    ASSERT_EQ(value->type, ExpressionValueType::INT);
    ASSERT_EQ(value->payloadInt, 100);
}


TEST(Expression, MultiplicationAdditionCombined) {
     Environment env;

    Token leftToken(TokenType::INT);
    leftToken.payloadInt = 10;

    Token middleToken(TokenType::INT);
    middleToken.payloadInt = 10;

    Token rightToken(TokenType::INT);
    rightToken.payloadInt = 10;

    std::unique_ptr<Expression> leftLiteral = std::make_unique<Literal>(leftToken);
    std::unique_ptr<Expression> middleLiteral = std::make_unique<Literal>(middleToken);
    std::unique_ptr<Expression> rightLiteral = std::make_unique<Literal>(rightToken);

    std::unique_ptr<Expression> multiplication =
        std::make_unique<Multiplication>(std::move(leftLiteral), std::move(middleLiteral));
    Addition addition(std::move(multiplication), std::move(rightLiteral));
    auto value = addition.evaluate(env);

    ASSERT_EQ(value->type, ExpressionValueType::INT);
    ASSERT_EQ(value->payloadInt, 110);
}
