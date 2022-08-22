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

std::shared_ptr<ExpressionValue> Literal::evaluate(std::shared_ptr<Environment>& env) {
    return value;
}


Name::Name(const Token& token) {
    if (!token.isType(TokenType::NAME)) {
        throw std::exception("Token not convertible to Name");
    }

    name = token.payloadStr;
}

std::shared_ptr<ExpressionValue> Name::evaluate(std::shared_ptr<Environment>& env) {
    return env->getVariable(name);
}


BinaryOperation::BinaryOperation(std::unique_ptr<Expression> left,
        std::unique_ptr<Expression> right):
            left(std::move(left)), right(std::move(right)) {}


std::shared_ptr<ExpressionValue> Addition::evaluate(std::shared_ptr<Environment>& env) {
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


std::shared_ptr<ExpressionValue> Subtraction::evaluate(std::shared_ptr<Environment>& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Subtraction: Types do not match up");
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


std::shared_ptr<ExpressionValue> Multiplication::evaluate(std::shared_ptr<Environment>& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Multiplication: Types do not match up");
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


std::shared_ptr<ExpressionValue> Division::evaluate(std::shared_ptr<Environment>& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Division: Types do not match up");
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


std::shared_ptr<ExpressionValue> EqualComparison::evaluate(std::shared_ptr<Environment>& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Equal: Types do not match up");
    }

    auto ret = std::make_shared<ExpressionValue>();

    switch (leftValue->type) {
        case ExpressionValueType::INT:
            ret->payloadInt = leftValue->payloadInt == rightValue->payloadInt ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
        case ExpressionValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat == rightValue->payloadFloat ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
    }

    return ret;
}


std::shared_ptr<ExpressionValue> GreaterThanComparison::evaluate(std::shared_ptr<Environment>& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Greater than: Types do not match up");
    }

    auto ret = std::make_shared<ExpressionValue>();

    switch (leftValue->type) {
        case ExpressionValueType::INT:
            ret->payloadInt = leftValue->payloadInt > rightValue->payloadInt ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
        case ExpressionValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat > rightValue->payloadFloat ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
    }

    return ret;
}


std::shared_ptr<ExpressionValue> GreaterThanOrEqualComparison::evaluate(std::shared_ptr<Environment>& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Greater than or equal: Types do not match up");
    }

    auto ret = std::make_shared<ExpressionValue>();

    switch (leftValue->type) {
        case ExpressionValueType::INT:
            ret->payloadInt = leftValue->payloadInt >= rightValue->payloadInt ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
        case ExpressionValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat >= rightValue->payloadFloat ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
    }

    return ret;
}


std::shared_ptr<ExpressionValue> LessThanComparison::evaluate(std::shared_ptr<Environment>& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Less than: Types do not match up");
    }

    auto ret = std::make_shared<ExpressionValue>();

    switch (leftValue->type) {
        case ExpressionValueType::INT:
            ret->payloadInt = leftValue->payloadInt < rightValue->payloadInt ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
        case ExpressionValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat < rightValue->payloadFloat ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
    }

    return ret;
}


std::shared_ptr<ExpressionValue> LessThanOrEqualComparison::evaluate(std::shared_ptr<Environment>& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Less than or equal: Types do not match up");
    }

    auto ret = std::make_shared<ExpressionValue>();

    switch (leftValue->type) {
        case ExpressionValueType::INT:
            ret->payloadInt = leftValue->payloadInt <= rightValue->payloadInt ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
        case ExpressionValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat <= rightValue->payloadFloat ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
    }

    return ret;
}


std::shared_ptr<ExpressionValue> NotEqualComparison::evaluate(std::shared_ptr<Environment>& env) {
    std::shared_ptr<ExpressionValue> leftValue = left->evaluate(env);
    std::shared_ptr<ExpressionValue> rightValue = right->evaluate(env);

    if (leftValue->type != rightValue->type) {
        throw std::exception("Not equal: Types do not match up");
    }

    auto ret = std::make_shared<ExpressionValue>();

    switch (leftValue->type) {
        case ExpressionValueType::INT:
            ret->payloadInt = leftValue->payloadInt != rightValue->payloadInt ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
        case ExpressionValueType::FLOAT:
            ret->payloadFloat = leftValue->payloadFloat != rightValue->payloadFloat ? 1 : 0;
            ret->type = ExpressionValueType::INT;
            break;
    }

    return ret;
}


std::shared_ptr<ExpressionValue> AndConnective::evaluate(std::shared_ptr<Environment>& env) {
    auto leftValue = left->evaluate(env);
    
    if (leftValue->type == ExpressionValueType::INT) {
        if (leftValue->payloadInt == 0) {
            return leftValue;
        } else {
            return right->evaluate(env);
        }
    } else {
        throw std::exception("And: Wrong types");
    }
}


std::shared_ptr<ExpressionValue> OrConnective::evaluate(std::shared_ptr<Environment>& env) {
    auto leftValue = left->evaluate(env);
    
    if (leftValue->type == ExpressionValueType::INT) {
        if (leftValue->payloadInt == 1) {
            return leftValue;
        } else {
            return right->evaluate(env);
        }
    } else {
        throw std::exception("Or: Wrong types");
    }
}


Assignment::Assignment(std::unique_ptr<Name> left,
        std::unique_ptr<Expression> right):
    left(std::move(left)), right(std::move(right)) {}

std::shared_ptr<ExpressionValue> Assignment::evaluate(std::shared_ptr<Environment>& env) {
    auto value = right->evaluate(env);
    env->setVariable(left->name, std::move(value));

    return value;
}


std::shared_ptr<ExpressionValue> Block::evaluate(std::shared_ptr<Environment>& parent) {
    auto env = std::make_shared<Environment>(parent);
    std::shared_ptr<ExpressionValue> ret;

    for (auto it = exprList.begin(); it != exprList.end(); it++) {
        ret = (*it)->evaluate(std::move(env));
    }

    return ret;
}

void Block::addExpression(std::unique_ptr<Expression>& expr) {
    exprList.push_back(std::move(expr));
}


IfStatement::IfStatement(std::unique_ptr<Expression>& condition,
        std::unique_ptr<Block>& ifBlock, std::unique_ptr<Block>& elseBlock):
    condition(std::move(condition)), ifBlock(std::move(ifBlock)),
        elseBlock(std::move(elseBlock)) {}

std::shared_ptr<ExpressionValue> IfStatement::evaluate(
        std::shared_ptr<Environment>& env) {
    auto conditionResult = condition->evaluate(env);
    
    if (conditionResult->type == ExpressionValueType::INT
            && conditionResult->payloadInt != 0) {
        return ifBlock->evaluate(env);
    } else {
        return elseBlock->evaluate(env);
    }
}


std::shared_ptr<ExpressionValue> CustomFunction::evaluate(
        std::shared_ptr<Environment>& env) {
    return body->evaluate(env);
}

void CustomFunction::addParameter(std::unique_ptr<Name>& name) {
    parameters.push_back(name->name);
}

const std::vector<std::string>& CustomFunction::getParameterNames() const {
    return parameters;
}

void CustomFunction::setBody(std::unique_ptr<Expression>& body) {
    this->body = std::move(body);
}


FunctionWrapper::FunctionWrapper(std::shared_ptr<CustomFunction>& function):
        function(std::move(function)) {}

std::shared_ptr<ExpressionValue> FunctionWrapper::evaluate(
        std::shared_ptr<Environment>& env) {
    auto exprVal = std::make_shared<ExpressionValue>();
    exprVal->type = ExpressionValueType::FUNCTION;
    exprVal->payloadFunc = function;

    return exprVal;
}


PrintFunction::PrintFunction() {
    parameterNames.push_back(std::string("str"));
}

std::shared_ptr<ExpressionValue> PrintFunction::evaluate(
        std::shared_ptr<Environment>& env) {
    auto str = env->getVariable(*parameterNames.begin());

    if (str->type != ExpressionValueType::STRING) {
        throw std::exception("Only print strings");
    }

    std::cout << str->payloadStr;

    return nullptr;
}

const std::vector<std::string>& PrintFunction::getParameterNames() const {
    return parameterNames;
}


Invocation::Invocation(std::unique_ptr<Name>& functionName):
        functionName(functionName->name) {}

std::shared_ptr<ExpressionValue> Invocation::evaluate(
        std::shared_ptr<Environment>& env) {
    auto functionVar = env->getVariable(functionName);

    if (functionVar->type != ExpressionValueType::FUNCTION) {
        throw std::exception("Only invoke functions");
    }

    auto function = functionVar->payloadFunc;
    auto paramNames = function->getParameterNames();

    if (paramNames.size() != arguments.size()) {
        throw std::exception("Function arguments do not map to parameters");
    }

    auto functionEnv = std::make_shared<Environment>(env);

    auto paramName = paramNames.begin();
    auto argValue = arguments.begin();
    while (paramName != paramNames.end()) {
        // TODO decide on what to do with variable shadowing
        functionEnv->setLocalVariable(*paramName, (*argValue)->evaluate(env));

        paramName++;
        argValue++;
    }

    return function->evaluate(functionEnv);
}

void Invocation::addArgument(std::unique_ptr<Expression>& arg) {
    arguments.push_back(std::move(arg));
}


GlobalEnvironment::GlobalEnvironment() {
    std::shared_ptr<Function> printFunction = std::make_shared<PrintFunction>();
    auto printFunctionVar = std::make_shared<ExpressionValue>();

    printFunctionVar->type = ExpressionValueType::FUNCTION;
    printFunctionVar->payloadFunc = printFunction;

    setVariable(std::string("print"), printFunctionVar);
}

