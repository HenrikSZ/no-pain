#include <gtest/gtest.h>
#include "parser.h"


TEST(Parser, SimpleAddition) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    std::unique_ptr<Input> input = std::make_unique<StringInput>("10 + 5");
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 15);
}

TEST(Parser, ChainedSubtraction) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    std::unique_ptr<Input> input = std::make_unique<StringInput>("50 - 30 - 10");
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 10);
}


TEST(Parser, MultiplicationAndAddition) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    std::unique_ptr<Input> input = std::make_unique<StringInput>("10 + 5 * 3");
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 25);
}


TEST(Parser, ArithmeticWithParentheses) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    std::unique_ptr<Input> input = std::make_unique<StringInput>("(10 + 5) * 3");
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 45);
}


TEST(Parser, OrConnective) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    std::unique_ptr<Input> input = std::make_unique<StringInput>("10 == 11 || 10 == 11 || 5 == 5");
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1);
}


TEST(Parser, Assignment) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    std::unique_ptr<Input> input = std::make_unique<StringInput>("x = (10 + 5) * 3");
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    // Test if assignment passes value through
    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 45);

    auto variable = env->getVariable(std::string("x"));
    ASSERT_EQ(variable->type, ExpressionValueType::INT);
    ASSERT_EQ(variable->payloadInt, 45);
}


TEST(Parser, SimpleEqualityComparisonTrue) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    std::unique_ptr<Input> input = std::make_unique<StringInput>("10 == 10");
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1);
}


TEST(Parser, SimpleEqualityComparisonFalse) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    std::unique_ptr<Input> input = std::make_unique<StringInput>("10 == 9");
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 0);
}


TEST(Parser, ChainedEqualityComparison) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    std::unique_ptr<Input> input = std::make_unique<StringInput>("10 == 10 == 1");
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1);
}


TEST(Parser, IfStatementSimple) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    std::unique_ptr<Input> input = std::make_unique<StringInput>("IF 10 == 10 == 1 10 ELSE 5");
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 10);
}


TEST(Parser, IfStatementComplex) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    const char* program =
        "   var = 10 == 10         "
        "   test = 5               "
        "   IF var {               "
        "       test = test * 5    "
        "   } ELSE {               "
        "       test = 10          "
        "   }                      "
        "   test                   ";

    std::unique_ptr<Input> input = std::make_unique<StringInput>(program);
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseAll();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 25);
}


TEST(Parser, Invocation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    const char* program = "print(\"TEST\")";

    std::unique_ptr<Input> input = std::make_unique<StringInput>(program);
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseAll();
    auto result = tree->evaluate(env);
}


TEST(Parser, FunctionDeclarationAndInvocation) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    const char* program =
        "   func = FUN test {                              "
        "       IF test > 5 test - 10 ELSE 1000            "
        "   }                                              "
        "                                                  "
        "   result = func(func(10))                        ";

    std::unique_ptr<Input> input = std::make_unique<StringInput>(program);
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseAll();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 1000);
}


TEST(Parser, RecursiveFibonacci) {
    std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

    const char* program =
        "   fib = FUN x {                         "
        "      IF x <= 2 {                        "
        "          1                              " 
        "      } ELSE {                           "
        "          fib(x - 1) + fib(x - 2)        "
        "      }                                  "
        "   }                                     "
        "                                         "
        "   fib(6)                                ";


    std::unique_ptr<Input> input = std::make_unique<StringInput>(program);
    auto tokenizer = std::make_unique<Tokenizer>(input);
    auto parser = std::make_unique<Parser>(tokenizer);

    auto tree = parser->parseAll();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 8);
}

