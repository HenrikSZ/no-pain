#include <gtest/gtest.h>
#include <memory>

#include "input.h"
#include "tokenizer.h"


TEST(Tokenizer, Keywords) {
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


TEST(Tokenizer, Symbols) {
    std::unique_ptr<Input> input(new StringInput("(){};,"));
    Tokenizer tokenizer(std::move(input));

    auto token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::OPEN_PAR);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::CLOSE_PAR);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::OPEN_BLOCK);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::CLOSE_BLOCK);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::END_OF_LINE);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::COMMA);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::END_OF_FILE);
}


void testStringTokenizer(char* testStr) {
    std::string completeStr = std::string("\"") + std::string(testStr) + std::string("\"");
    std::unique_ptr<Input> input(new StringInput(completeStr));
    Tokenizer tokenizer(std::move(input));

    std::shared_ptr<Token> token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::STRING);
    ASSERT_STREQ(token->payloadStr.c_str(), testStr);
}

TEST(Tokenizer, SimpleString) {
    testStringTokenizer("Test");
}

TEST(Tokenizer, EscapedString) {
    testStringTokenizer("Test \n\t test2");
}


TEST(Tokenizer, Name) {
    std::unique_ptr<Input> input(new StringInput("abc DEF"));
    Tokenizer tokenizer(std::move(input));

    auto token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::NAME);
    ASSERT_STREQ(token->payloadStr.c_str(), "abc");

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::NAME);
    ASSERT_STREQ(token->payloadStr.c_str(), "DEF");

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::END_OF_FILE);
}


TEST(Tokenizer, Integer) {
    std::unique_ptr<Input> input(new StringInput("20234324 2109090"));
    Tokenizer tokenizer(std::move(input));

    auto token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::INT);
    ASSERT_EQ(token->payloadInt, 20234324);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::INT);
    ASSERT_EQ(token->payloadInt, 2109090);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::END_OF_FILE);
}


TEST(Tokenizer, Float) {
    std::unique_ptr<Input> input(new StringInput("2.542 100.323"));
    Tokenizer tokenizer(std::move(input));

    auto token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::FLOAT);
    ASSERT_FLOAT_EQ(token->payloadFloat, 2.542);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::FLOAT);
    ASSERT_FLOAT_EQ(token->payloadFloat, 100.323);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::END_OF_FILE);
}


TEST(Tokenizer, Jumble) {
    std::unique_ptr<Input> input(new StringInput("2.542 \n\"Test\" = var FUN {100}"));
    Tokenizer tokenizer(std::move(input));

    auto token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::FLOAT);
    ASSERT_FLOAT_EQ(token->payloadFloat, 2.542);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::STRING);
    ASSERT_STREQ(token->payloadStr.c_str(), "Test");

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::ASSIGN);
    
    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::NAME);
    ASSERT_STREQ(token->payloadStr.c_str(), "var");
    
    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::FUN);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::OPEN_BLOCK);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::INT);
    ASSERT_EQ(token->payloadInt, 100);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::CLOSE_BLOCK);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::END_OF_FILE);
}


TEST(Tokenizer, Peeking) {
    std::unique_ptr<Input> input(new StringInput("2.542 \n\"Test\" = var FUN {100}"));
    Tokenizer tokenizer(std::move(input));

    auto token = tokenizer.peekNextToken();
    ASSERT_EQ(token->getType(), TokenType::FLOAT);
    ASSERT_FLOAT_EQ(token->payloadFloat, 2.542);

    token = tokenizer.peekNextToken();
    ASSERT_EQ(token->getType(), TokenType::FLOAT);
    ASSERT_FLOAT_EQ(token->payloadFloat, 2.542);

    token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::FLOAT);
    ASSERT_FLOAT_EQ(token->payloadFloat, 2.542);

     token = tokenizer.getNextToken();
    ASSERT_EQ(token->getType(), TokenType::STRING);
    ASSERT_STREQ(token->payloadStr.c_str(), "Test");
}
