#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <memory>

#include "environment.h"
#include "tokenizer.h"


class Expression {
public:
    virtual std::shared_ptr<ExpressionValue> evaluate(Environment& env) = 0;
};


class Literal: public Expression {
public:
    Literal(const Token& token);

    std::shared_ptr<ExpressionValue> evaluate(Environment& env);

private:
    std::shared_ptr<ExpressionValue> value;
};


class Name: public Expression {
public:
    Name(const Token& token);

    std::shared_ptr<ExpressionValue> evaluate(Environment& env);

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

    std::shared_ptr<ExpressionValue> evaluate(Environment& env);
};

class Subtraction: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    std::shared_ptr<ExpressionValue> evaluate(Environment& env);
};

class Multiplication: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    std::shared_ptr<ExpressionValue> evaluate(Environment& env);
};

class Division: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    std::shared_ptr<ExpressionValue> evaluate(Environment& env);
};


class Assignment: public Expression {
public:
    Assignment(std::unique_ptr<Name> left,
        std::unique_ptr<Expression> right):
            left(std::move(left)), right(std::move(right)) {}

    std::shared_ptr<ExpressionValue> evaluate(Environment& env);

private:
    std::shared_ptr<Name> left;
    std::shared_ptr<Expression> right;
};


#endif
