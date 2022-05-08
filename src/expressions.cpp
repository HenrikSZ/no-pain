#include "expressions.h"


Literal::Literal(const Token& token) {
    switch (token.getType()) {
        case TokenType::STRING:
            value = std::make_shared<Value>();
            value->payloadStr = token.payloadStr;
            value->type = ValueType::STRING;
            break;
        case TokenType::INT:
            value = std::make_shared<Value>();
            value->payloadStr = token.payloadStr;
            value->type = ValueType::INT;
            break;
        case TokenType::FLOAT:
            value = std::make_shared<Value>();
            value->payloadStr = token.payloadStr;
            value->type = ValueType::FLOAT;
            break;
        default:
            throw std::exception("Token not convertible to literal");
    }
}


std::shared_ptr<Value> Literal::evaluate(Environment& env) {
    return value;
}


std::shared_ptr<Value> Addition::evaluate(Environment& env) {
    std::shared_ptr<Value> leftValue = left->evaluate(env);
    std::shared_ptr<Value> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Addition: Types do not match up");
    }

    auto ret = std::make_shared<Value>();

    switch (leftValue->type) {
        case ValueType::INT:
            ret->payloadInt = leftValue->payloadInt + rightValue->payloadInt;
            ret->type = ValueType::INT;
            break;
        case ValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat + rightValue->payloadFloat;
            ret->type = ValueType::FLOAT;
            break;
        case ValueType::STRING:
            ret->payloadStr = leftValue->payloadStr + rightValue->payloadStr;
            ret->type = ValueType::STRING;
            break;
        default:
            throw std::exception("Addition: Invalid type");
    }
    
    return ret;
}


std::shared_ptr<Value> Subtraction::evaluate(Environment& env) {
    std::shared_ptr<Value> leftValue = left->evaluate(env);
    std::shared_ptr<Value> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Addition: Types do not match up");
    }

    auto ret = std::make_shared<Value>();

    switch (leftValue->type) {
        case ValueType::INT:
            ret->payloadInt = leftValue->payloadInt - rightValue->payloadInt;
            ret->type = ValueType::INT;
            break;
        case ValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat - rightValue->payloadFloat;
            ret->type = ValueType::FLOAT;
            break;
    }

    return ret;
}


std::shared_ptr<Value> Multiplication::evaluate(Environment& env) {
    std::shared_ptr<Value> leftValue = left->evaluate(env);
    std::shared_ptr<Value> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Addition: Types do not match up");
    }

    auto ret = std::make_shared<Value>();

    switch (leftValue->type) {
        case ValueType::INT:
            ret->payloadInt = leftValue->payloadInt * rightValue->payloadInt;
            ret->type = ValueType::INT;
            break;
        case ValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat * rightValue->payloadFloat;
            ret->type = ValueType::FLOAT;
            break;
    }

    return ret;
}


std::shared_ptr<Value> Division::evaluate(Environment& env) {
    std::shared_ptr<Value> leftValue = left->evaluate(env);
    std::shared_ptr<Value> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Addition: Types do not match up");
    }

    auto ret = std::make_shared<Value>();

    switch (leftValue->type) {
        case ValueType::INT:
            ret->payloadInt = leftValue->payloadInt / rightValue->payloadInt;
            ret->type = ValueType::INT;
            break;
        case ValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat / rightValue->payloadFloat;
            ret->type = ValueType::FLOAT;
            break;
    }

    return ret;
}
