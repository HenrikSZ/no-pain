#include <gtest/gtest.h>
#include <memory>

#include "input.h"
#include "tokenizer.h"


TEST(Tokenizer, Keyword) {
    std::unique_ptr<Input> input(new StringInput(std::string("IF FOR ELSE WHILE FUN")));
    Tokenizer tokenizer(std::move(input));

    std::shared_ptr<Token> token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::IF);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::FOR);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::ELSE);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::WHILE);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::FUN);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::END_OF_FILE);
}
