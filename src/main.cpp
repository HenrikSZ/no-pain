#include <iostream>

#include "parser.h"


int main(int argc, char* argv[]) {
    if (argc == 2) {
        auto filename = std::string(argv[1]);

        std::unique_ptr<Input> input = std::make_unique<FileInput>(filename);
        auto tokenizer = std::make_unique<Tokenizer>(std::move(input));
        auto parser = std::make_unique<Parser>(std::move(tokenizer));

        std::shared_ptr<Environment> env = std::make_shared<GlobalEnvironment>();

        auto tree = parser->parseAll();
        auto result = tree->evaluate(env);

        switch (result->type) {
            case ExpressionValueType::INT:
                std::cout << result->payloadInt;
                break;
            case ExpressionValueType::FLOAT:
                std::cout << result->payloadFloat;
                break;
            case ExpressionValueType::STRING:
                std::cout << result->payloadStr;
                break;
        }
    }
}
