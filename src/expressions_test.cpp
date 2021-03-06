#include <gtest/gtest.h>
#include "expressions.h"


TEST(Expression, LiteralInit) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token token(TokenType::INT);
    token.payloadInt = 10;

    Literal literal(token);
    auto value = literal.evaluate(env);

    ASSERT_EQ(value->type, ExpressionValueType::INT);
    ASSERT_EQ(value->payloadInt, 10);
}


TEST(Expression, AdditionEvaluationSimple) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

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
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

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
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

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


TEST(Expression, Equalvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token leftToken(TokenType::INT);
    leftToken.payloadInt = 10;

    Token equalToken(TokenType::INT);
    equalToken.payloadInt = 10;

    Token notEqualToken(TokenType::INT);
    notEqualToken.payloadInt = 11;

    std::unique_ptr<Expression> leftLiteral =
        std::make_unique<Literal>(leftToken);
    std::unique_ptr<Expression> equalLiteral =
        std::make_unique<Literal>(equalToken);
    std::unique_ptr<Expression> notEqualLiteral =
        std::make_unique<Literal>(notEqualToken);

    EqualComparison equalComparison(std::move(leftLiteral),
        std::move(equalLiteral));
    auto result = equalComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1);

    leftLiteral = std::make_unique<Literal>(leftToken);

    EqualComparison notEqualComparison(std::move(leftLiteral),
        std::move(notEqualLiteral));
    result = notEqualComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 0);
}


TEST(Expression, GreaterThanEvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token leftToken(TokenType::INT);
    leftToken.payloadInt = 10;

    Token greatherThanToken(TokenType::INT);
    greatherThanToken.payloadInt = 9;

    Token notGreatherThanToken(TokenType::INT);
    notGreatherThanToken.payloadInt = 10;

    std::unique_ptr<Expression> leftLiteral =
        std::make_unique<Literal>(leftToken);
    std::unique_ptr<Expression> greatherThanLiteral =
        std::make_unique<Literal>(greatherThanToken);
    std::unique_ptr<Expression> notGreaterThanLiteral =
        std::make_unique<Literal>(notGreatherThanToken);

    GreaterThanComparison greaterThanComparison(std::move(leftLiteral),
        std::move(greatherThanLiteral));
    auto result = greaterThanComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1);

    leftLiteral = std::make_unique<Literal>(leftToken);

    GreaterThanComparison notGreaterThanComparison(std::move(leftLiteral),
        std::move(notGreaterThanLiteral));
    result = notGreaterThanComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 0);
}


TEST(Expression, GreaterThanOrEqualEvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token leftToken(TokenType::INT);
    leftToken.payloadInt = 10;

    Token greatherThanToken(TokenType::INT);
    greatherThanToken.payloadInt = 10;

    Token notGreatherThanToken(TokenType::INT);
    notGreatherThanToken.payloadInt = 11;

    std::unique_ptr<Expression> leftLiteral =
        std::make_unique<Literal>(leftToken);
    std::unique_ptr<Expression> greatherThanLiteral =
        std::make_unique<Literal>(greatherThanToken);
    std::unique_ptr<Expression> notGreaterThanLiteral =
        std::make_unique<Literal>(notGreatherThanToken);

    GreaterThanOrEqualComparison greaterThanComparison(std::move(leftLiteral),
        std::move(greatherThanLiteral));
    auto result = greaterThanComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1);

    leftLiteral = std::make_unique<Literal>(leftToken);

    GreaterThanOrEqualComparison notGreaterThanComparison(std::move(leftLiteral),
        std::move(notGreaterThanLiteral));
    result = notGreaterThanComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 0);
}


TEST(Expression, LessThanEvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token leftToken(TokenType::INT);
    leftToken.payloadInt = 10;

    Token greatherThanToken(TokenType::INT);
    greatherThanToken.payloadInt = 11;

    Token notGreatherThanToken(TokenType::INT);
    notGreatherThanToken.payloadInt = 10;

    std::unique_ptr<Expression> leftLiteral =
        std::make_unique<Literal>(leftToken);
    std::unique_ptr<Expression> greatherThanLiteral =
        std::make_unique<Literal>(greatherThanToken);
    std::unique_ptr<Expression> notGreaterThanLiteral =
        std::make_unique<Literal>(notGreatherThanToken);

    LessThanComparison greaterThanComparison(std::move(leftLiteral),
        std::move(greatherThanLiteral));
    auto result = greaterThanComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1);

    leftLiteral = std::make_unique<Literal>(leftToken);

    LessThanComparison notGreaterThanComparison(std::move(leftLiteral),
        std::move(notGreaterThanLiteral));
    result = notGreaterThanComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 0);
}


TEST(Expression, LessThanOrEqualEvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token leftToken(TokenType::INT);
    leftToken.payloadInt = 10;

    Token greatherThanToken(TokenType::INT);
    greatherThanToken.payloadInt = 10;

    Token notGreatherThanToken(TokenType::INT);
    notGreatherThanToken.payloadInt = 9;

    std::unique_ptr<Expression> leftLiteral =
        std::make_unique<Literal>(leftToken);
    std::unique_ptr<Expression> greatherThanLiteral =
        std::make_unique<Literal>(greatherThanToken);
    std::unique_ptr<Expression> notGreaterThanLiteral =
        std::make_unique<Literal>(notGreatherThanToken);

    LessThanOrEqualComparison greaterThanComparison(std::move(leftLiteral),
        std::move(greatherThanLiteral));
    auto result = greaterThanComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1);

    leftLiteral = std::make_unique<Literal>(leftToken);

    LessThanOrEqualComparison notGreaterThanComparison(std::move(leftLiteral),
        std::move(notGreaterThanLiteral));
    result = notGreaterThanComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 0);
}


TEST(Expression, NotEqualvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token leftToken(TokenType::INT);
    leftToken.payloadInt = 10;

    Token equalToken(TokenType::INT);
    equalToken.payloadInt = 10;

    Token notEqualToken(TokenType::INT);
    notEqualToken.payloadInt = 11;

    std::unique_ptr<Expression> leftLiteral =
        std::make_unique<Literal>(leftToken);
    std::unique_ptr<Expression> equalLiteral =
        std::make_unique<Literal>(equalToken);
    std::unique_ptr<Expression> notEqualLiteral =
        std::make_unique<Literal>(notEqualToken);

    NotEqualComparison equalComparison(std::move(leftLiteral),
        std::move(equalLiteral));
    auto result = equalComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 0);

    leftLiteral = std::make_unique<Literal>(leftToken);

    NotEqualComparison notEqualComparison(std::move(leftLiteral),
        std::move(notEqualLiteral));
    result = notEqualComparison.evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1);
}


TEST(Expression, NameEvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

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

TEST(Expression, AndConnectiveTrueEvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token trueToken(TokenType::INT);
    trueToken.payloadInt = 1;

    std::unique_ptr<Expression> leftTrueLiteral =
        std::make_unique<Literal>(trueToken);
    std::unique_ptr<Expression> rightTrueLiteral =
        std::make_unique<Literal>(trueToken);

    std::unique_ptr<Expression> andTrue =
        std::make_unique<AndConnective>(std::move(leftTrueLiteral), std::move(rightTrueLiteral));

    auto result = andTrue->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1);
}

TEST(Expression, AndConnectiveFalseEvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token trueToken(TokenType::INT);
    trueToken.payloadInt = 1;
    Token falseToken(TokenType::INT);
    falseToken.payloadInt = 0;

    std::unique_ptr<Expression> leftTrueLiteral =
        std::make_unique<Literal>(trueToken);
    std::unique_ptr<Expression> rightFalseLiteral =
        std::make_unique<Literal>(falseToken);

    std::unique_ptr<Expression> andTrue =
        std::make_unique<AndConnective>(std::move(leftTrueLiteral), std::move(rightFalseLiteral));

    auto result = andTrue->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 0);
}

TEST(Expression, OrConnectiveTrueEvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token trueToken(TokenType::INT);
    trueToken.payloadInt = 1;
    Token falseToken(TokenType::INT);
    falseToken.payloadInt = 0;

    std::unique_ptr<Expression> leftTrueLiteral =
        std::make_unique<Literal>(trueToken);
    std::unique_ptr<Expression> rightFalseLiteral =
        std::make_unique<Literal>(falseToken);

    std::unique_ptr<Expression> orTrue =
        std::make_unique<OrConnective>(std::move(leftTrueLiteral), std::move(rightFalseLiteral));

    auto result = orTrue->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1);
}

TEST(Expression, OrConnectiveFalseEvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token falseToken(TokenType::INT);
    falseToken.payloadInt = 0;

    std::unique_ptr<Expression> leftFalseLiteral =
        std::make_unique<Literal>(falseToken);
    std::unique_ptr<Expression> rightFalseLiteral =
        std::make_unique<Literal>(falseToken);

    std::unique_ptr<Expression> andTrue =
        std::make_unique<AndConnective>(std::move(leftFalseLiteral), std::move(rightFalseLiteral));

    auto result = andTrue->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 0);
}

TEST(Expression, AssignmentEvaluation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

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
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

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

TEST(Expression, IfStatement) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token conditionalToken(TokenType::INT);
    conditionalToken.payloadInt = 1;

    Token onTrueToken(TokenType::INT);
    onTrueToken.payloadInt = 10;

    Token onFalseToken(TokenType::INT);
    onFalseToken.payloadInt = 20;

    std::unique_ptr<Expression> conditionalLiteral =
        std::make_unique<Literal>(conditionalToken);

    std::unique_ptr<Expression> onTrueLiteral =
        std::make_unique<Literal>(onTrueToken);
    
    std::unique_ptr<Expression> onFalseLiteral =
        std::make_unique<Literal>(onFalseToken);

    auto trueBlock =
        std::make_unique<Block>();
    
    auto falseBlock =
        std::make_unique<Block>();

    trueBlock->addExpression(onTrueLiteral);
    falseBlock->addExpression(onFalseLiteral);

    IfStatement ifStmt(conditionalLiteral, trueBlock, falseBlock);

    auto result = ifStmt.evaluate(env);
    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 10);
}

TEST(Expression, PrintFunction) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    Token printToken(TokenType::NAME);
    printToken.payloadStr = std::string("print");

    Token stringToken(TokenType::STRING);
    stringToken.payloadStr = std::string("Hello, world!");

    auto printFuncName = std::make_unique<Name>(printToken);

    std::unique_ptr<Expression> arg = std::make_unique<Literal>(stringToken);
    auto printExpr = std::make_unique<Invocation>(printFuncName);

    printExpr->addArgument(arg);

    printExpr->evaluate(env);
}
