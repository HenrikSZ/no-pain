#include <gtest/gtest.h>
#include "expressions.h"


TEST(Expression, LiteralInit) {
    auto env = std::make_shared<Environment>();

    Token token(TokenType::INT);
    token.payloadInt = 10;

    Literal literal(token);
    auto value = literal.evaluate(env);

    ASSERT_EQ(value->type, ExpressionValueType::INT);
    ASSERT_EQ(value->payloadInt, 10);
}


TEST(Expression, AdditionEvaluationSimple) {
    auto env = std::make_shared<Environment>();

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
    auto env = std::make_shared<Environment>();

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
    auto env = std::make_shared<Environment>();

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
    auto env = std::make_shared<Environment>();

    Token valToken(TokenType::INT);
    valToken.payloadInt = 10;

    Token nameToken(TokenType::NAME);
    nameToken.payloadStr = "x";

    std::unique_ptr<Expression> valLiteral = std::make_unique<Literal>(valToken);
    auto value = valLiteral->evaluate(env);

    env->setVariable(std::string("x"), value);

    Name name(nameToken);
    auto eval = name.evaluate(env);

    ASSERT_EQ(eval->type, ExpressionValueType::INT);
    ASSERT_EQ(eval->payloadInt, 10);
}

TEST(Expression, AssignmentEvaluation) {
    auto env = std::make_shared<Environment>();

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

    auto result = env->getVariable(std::string("x"));

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 10);
}

TEST(Expression, BlockEvaluation) {
    // (outer is int 50)
    // { inner = outer }
    auto env = std::make_shared<Environment>();

    auto value = std::make_shared<ExpressionValue>();
    value->payloadInt = 50;
    value->type = ExpressionValueType::INT;
    env->setVariable(std::string("outer"), value);

    Token rightToken(TokenType::NAME);
    rightToken.payloadStr = std::string("outer");

    Token nameToken(TokenType::NAME);
    nameToken.payloadStr = "inner";

    std::unique_ptr<Expression> rightName =
        std::make_unique<Name>(rightToken);
    auto name = std::make_unique<Name>(nameToken);
    
    std::unique_ptr<Expression> assignment =
        std::make_unique<Assignment>(std::move(name), std::move(rightName));

    std::unique_ptr<Block> block =
        std::make_unique<Block>();
    
    block->addExpression(std::move(assignment));

    auto result = block->evaluate(env);
    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 50);
}
