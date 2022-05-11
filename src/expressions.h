#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <memory>
#include <vector>
#include <iostream>

#include "environment.h"
#include "tokenizer.h"


class Expression {
public:
    virtual std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env) = 0;
};


class Literal: public Expression {
public:
    Literal(const Token& token);

    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);

private:
    std::shared_ptr<ExpressionValue> value;
};


class Name: public Expression {
public:
    Name(const Token& token);

    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);

    std::string name;
};


class BinaryOperation: public Expression {
public:
    BinaryOperation(std::unique_ptr<Expression> left,
        std::unique_ptr<Expression> right):
            left(std::move(left)), right(std::move(right)) {}
protected:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};


class Addition: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};

class Subtraction: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};

class Multiplication: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};

class Division: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};


class EqualComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};


class GreaterThanComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};


class GreaterThanOrEqualComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};


class LessThanComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};


class LessThanOrEqualComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};


class NotEqualComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};


class AndConnective: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};


class OrConnective: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
};


class Assignment: public Expression {
public:
    Assignment(std::unique_ptr<Name> left,
        std::unique_ptr<Expression> right):
            left(std::move(left)), right(std::move(right)) {}

    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);

private:
    std::shared_ptr<Name> left;
    std::shared_ptr<Expression> right;
};


class Block: public Expression {
public:
    void addExpression(std::unique_ptr<Expression>& expr);

    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& parent);

private:
    std::vector<std::unique_ptr<Expression>> exprList;
};


class IfStatement: public Expression {
public:
    IfStatement(std::unique_ptr<Expression>& condition, std::unique_ptr<Block>& ifBlock,
        std::unique_ptr<Block>& elseBlock):
        condition(std::move(condition)), ifBlock(std::move(ifBlock)),
        elseBlock(std::move(elseBlock)) {}

    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);

private:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Expression> ifBlock;
    std::unique_ptr<Expression> elseBlock;
};


class Function: public Expression {
public:
    virtual const std::vector<std::string>& getParameterNames() const = 0;
};


class CustomFunction: public Function {
public:
    CustomFunction::CustomFunction(std::unique_ptr<Expression>& body):
        body(std::move(body)) {}

    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
    const std::vector<std::string>& getParameterNames() const;
    void addParameter(std::unique_ptr<Name>& name);

private:
    std::vector<std::string> parameters;
    std::unique_ptr<Expression> body;
};


class PrintFunction: public Function {
public:
    PrintFunction();
    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);
    const std::vector<std::string>& getParameterNames() const;

private:
    std::vector<std::string> parameterNames;
};


class Invocation: public Expression {
public:
    Invocation(std::unique_ptr<Name>& functionName):
        functionName(functionName->name) {}
     void addArgument(std::unique_ptr<Expression>& arg);

    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);

private:
    std::string functionName;
    std::vector<std::unique_ptr<Expression>> arguments;
};


class GlobalEnvironment: public Environment {
public:
    GlobalEnvironment();  
};


#endif
