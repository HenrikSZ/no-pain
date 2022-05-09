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


TEST(Expression, NameEvaluation) {
    Environment env;

    Token valToken(TokenType::INT);
    valToken.payloadInt = 10;

    Token nameToken(TokenType::NAME);
    nameToken.payloadStr = "x";

    std::unique_ptr<Expression> valLiteral = std::make_unique<Literal>(valToken);
    auto value = valLiteral->evaluate(env);

    env.setVariable(std::string("x"), value);

    Name name(nameToken);
    auto eval = name.evaluate(env);

    ASSERT_EQ(eval->type, ExpressionValueType::INT);
    ASSERT_EQ(eval->payloadInt, 10);
}

TEST(Expression, AssignmentEvaluation) {
    Environment env;

    Token valToken(TokenType::INT);
    valToken.payloadInt = 10;

    Token nameToken(TokenType::NAME);
    nameToken.payloadStr = "x";

    std::unique_ptr<Expression> valLiteral =
        std::make_unique<Literal>(valToken);
    auto name = std::make_unique<Name>(nameToken);
    
    std::unique_ptr<Expression> assignment =
        std::make_unique<Assignment>(std::move(name), std::move(valLiteral));

    assignment->evaluate(env);

    auto result = env.getVariable(std::string("x"));

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 10);
}
