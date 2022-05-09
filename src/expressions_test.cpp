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
