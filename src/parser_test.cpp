#include <gtest/gtest.h>
#include "parser.h"


TEST(Parser, SimpleAddition) {
    Environment env;

    std::unique_ptr<Input> input = std::make_unique<StringInput>("10 + 5");
    auto tokenizer = std::make_unique<Tokenizer>(std::move(input));
    auto parser = std::make_unique<Parser>(std::move(tokenizer));

    auto tree = parser->parseLine();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 15);
}


TEST(Parser, MultiplicationAndAddition) {
    Environment env;

    std::unique_ptr<Input> input = std::make_unique<StringInput>("10 + 5 * 3");
    auto tokenizer = std::make_unique<Tokenizer>(std::move(input));
    auto parser = std::make_unique<Parser>(std::move(tokenizer));

    auto tree = parser->parseLine();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 25);
}


TEST(Parser, ArithmeticWithParentheses) {
    Environment env;

    std::unique_ptr<Input> input = std::make_unique<StringInput>("(10 + 5) * 3");
    auto tokenizer = std::make_unique<Tokenizer>(std::move(input));
    auto parser = std::make_unique<Parser>(std::move(tokenizer));

    auto tree = parser->parseLine();
    auto result = tree->evaluate(env);

    ASSERT_EQ(result->type, ExpressionValueType::INT);
    ASSERT_EQ(result->payloadInt, 45);
}
