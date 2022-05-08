cc_binary(
    name = "main",
    srcs=["main.cpp", "input.cpp", "tokenizer.cpp", "input.h", "tokenizer.h"])

cc_test(
  name = "main_test",
  size = "small",
  srcs = ["input_test.cpp", "input.cpp", "input.h", "tokenizer_test.cpp", "tokenizer.cpp", "tokenizer.h"],
  deps = ["@com_google_googletest//:gtest_main"],
)
