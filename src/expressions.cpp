#include "expressions.h"


Literal::Literal(const Token& token) {
    switch (token.getType()) {
        case TokenType::STRING:
            value = std::make_shared<ExpressionValue>();
            value->payloadStr = token.payloadStr;
            value->type = ExpressionValueType::STRING;
            break;
        case TokenType::INT:
            value = std::make_shared<ExpressionValue>();
            value->payloadInt = token.payloadInt;
            value->type = ExpressionValueType::INT;
            break;
        case TokenType::FLOAT:
            value = std::make_shared<ExpressionValue>();
            value->payloadFloat = token.payloadFloat;
            value->type = ExpressionValueType::FLOAT;
            break;
        default:
            throw std::exception("Token not convertible to Literal");
    }
}

std::shared_ptr<ExpressionValue> Literal::evaluate(Environment& env) {
    return value;
}


Name::Name(const Token& token) {
    if (!token.isType(TokenType::NAME)) {
        throw std::exception("Token not convertible to Name");
    }

    name = token.payloadStr;
}

std::shared_ptr<ExpressionValue> Name::evaluate(Environment& env) {
    return env.getVariable(name);
}


std::shared_ptr<ExpressionValue> Addition::evaluate(Environment& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Addition: Types do not match up");
    }

    auto ret = std::make_shared<ExpressionValue>();

    switch (leftValue->type) {
        case ExpressionValueType::INT:
            ret->payloadInt = leftValue->payloadInt + rightValue->payloadInt;
            ret->type = ExpressionValueType::INT;
            break;
        case ExpressionValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat + rightValue->payloadFloat;
            ret->type = ExpressionValueType::FLOAT;
            break;
        case ExpressionValueType::STRING:
            ret->payloadStr = leftValue->payloadStr + rightValue->payloadStr;
            ret->type = ExpressionValueType::STRING;
            break;
        default:
            throw std::exception("Addition: Invalid type");
    }

    return ret;
}


std::shared_ptr<ExpressionValue> Subtraction::evaluate(Environment& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Addition: Types do not match up");
    }

    auto ret = std::make_shared<ExpressionValue>();

    switch (leftValue->type) {
        case ExpressionValueType::INT:
            ret->payloadInt = leftValue->payloadInt - rightValue->payloadInt;
            ret->type = ExpressionValueType::INT;
            break;
        case ExpressionValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat - rightValue->payloadFloat;
            ret->type = ExpressionValueType::FLOAT;
            break;
    }

    return ret;
}


std::shared_ptr<ExpressionValue> Multiplication::evaluate(Environment& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Addition: Types do not match up");
    }

    auto ret = std::make_shared<ExpressionValue>();

    switch (leftValue->type) {
        case ExpressionValueType::INT:
            ret->payloadInt = leftValue->payloadInt * rightValue->payloadInt;
            ret->type = ExpressionValueType::INT;
            break;
        case ExpressionValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat * rightValue->payloadFloat;
            ret->type = ExpressionValueType::FLOAT;
            break;
    }

    return ret;
}


std::shared_ptr<ExpressionValue> Division::evaluate(Environment& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Addition: Types do not match up");
    }

    auto ret = std::make_shared<ExpressionValue>();

    switch (leftValue->type) {
        case ExpressionValueType::INT:
            ret->payloadInt = leftValue->payloadInt / rightValue->payloadInt;
            ret->type = ExpressionValueType::INT;
            break;
        case ExpressionValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat / rightValue->payloadFloat;
            ret->type = ExpressionValueType::FLOAT;
            break;
    }

    return ret;
}


std::shared_ptr<ExpressionValue> Assignment::evaluate(Environment& env) {
    auto value = right->evaluate(env);
    env.setVariable(left->name, std::move(value));

    return value;
}
