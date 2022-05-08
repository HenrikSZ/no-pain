#include <gtest/gtest.h>

#include "input.h"


TEST(FileInput, CheckInit) {
    FileInput input(std::string("D:\\IT\\c++\\no-pain\\test-scripts\\simple.npn"));
    ASSERT_TRUE(input.hasNext());
    input.advance();
    ASSERT_EQ(input.getCurrentChar(), 'p');
}


TEST(StringInput, CheckInit) {
    StringInput input(std::string("print(\"Hello, world!\")"));
    ASSERT_TRUE(input.hasNext());
    input.advance();
    ASSERT_EQ(input.getCurrentChar(), 'p');
}
