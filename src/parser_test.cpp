#include <gtest/gtest.h>
#include "parser.h"


TEST(Parser, SimpleAddition) {
    Environment env;

    std::unique_ptr<Input> input = std::make_unique<StringInput>("10 + 5");
    auto tokenizer = std::make_unique<Tokenizer>(std::move(input));
    auto parser = std::make_unique<Parser>(std::move(tokenizer));

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 15);
}


TEST(Parser, MultiplicationAndAddition) {
    Environment env;

    std::unique_ptr<Input> input = std::make_unique<StringInput>("10 + 5 * 3");
    auto tokenizer = std::make_unique<Tokenizer>(std::move(input));
    auto parser = std::make_unique<Parser>(std::move(tokenizer));

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 25);
}


TEST(Parser, ArithmeticWithParentheses) {
    Environment env;

    std::unique_ptr<Input> input = std::make_unique<StringInput>("(10 + 5) * 3");
    auto tokenizer = std::make_unique<Tokenizer>(std::move(input));
    auto parser = std::make_unique<Parser>(std::move(tokenizer));

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 45);
}


TEST(Parser, Assignment) {
    Environment env;

    std::unique_ptr<Input> input = std::make_unique<StringInput>("x = (10 + 5) * 3");
    auto tokenizer = std::make_unique<Tokenizer>(std::move(input));
    auto parser = std::make_unique<Parser>(std::move(tokenizer));

    auto tree = parser->parseExpression();
    auto result = tree->evaluate(env);

    // Test if assignment passes value through
    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 45);

    auto variable = env.getVariable(std::string("x"));
    ASSERT_EQ(variable->type, ExpressionValueType::INT);
    ASSERT_EQ(variable->payloadInt, 45);

}
