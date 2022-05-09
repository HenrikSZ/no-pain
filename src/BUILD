cc_binary(
    name = "main",
    srcs=["main.cpp", "input.cpp", "tokenizer.cpp", "expressions.cpp", "environment.cpp", 
    "parser.cpp", "input.h", "tokenizer.h", "expressions.h", "environment.h", 
    "parser.h"])

cc_test(
  name = "main_test",
  size = "small",
  srcs = ["input_test.cpp", "input.cpp", "input.h",
  "tokenizer_test.cpp", "tokenizer.cpp", "tokenizer.h",
  "expressions_test.cpp", "expressions.cpp", "expressions.h",
  "environment.cpp", "environment.h",
  "parser_test.cpp", "parser.cpp", "parser.h"
  ],
  deps = ["@com_google_googletest//:gtest_main"],
)
