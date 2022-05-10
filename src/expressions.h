#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <memory>
#include <vector>

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


#endif
