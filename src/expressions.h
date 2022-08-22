#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H


#include <memory>
#include <vector>
#include <iostream>

#include "environment.h"
#include "tokenizer.h"


/**
 * @brief Abstract base class for all Expressions.
 * 
 */
class Expression {
public:
    /**
     * @brief Evaluate this expression and return its value.
     * 
     * @param env The environment which provides the context for everything
     * relating to variables.
     * @return std::shared_ptr<ExpressionValue> the value of this expression.
     */
    virtual std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env) = 0;
};


/**
 * @brief An Expression that holds literal values contructed from Tokens
 * of type INT, FLOAT or STRING.
 * 
 */
class Literal: public Expression {
public:
    /**
     * @brief Construct a new Literal object based on the passed in token.
     * 
     * @param token a token of TokenType INT, FLOAT or STRING.
     */
    Literal(const Token& token);

    /**
     * @brief Return the ExpressionValue contructed from the passed in Token.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> the value of this expression.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);

private:
    /**
     * @brief The value constructed from the passed in Token.
     * 
     */
    std::shared_ptr<ExpressionValue> value;
};


/**
 * @brief An Expression that holds names constructed from Tokens of type NAME.
 * 
 */
class Name: public Expression {
public:
    /**
     * @brief Construct a new Name object based on the passed in token.
     * 
     * @param token a token of TokenType NAME.
     */
    Name(const Token& token);

    /**
     * @brief Return the ExpressionValue of the variable associated to <name>.
     * 
     * @param env the 
     * @return std::shared_ptr<ExpressionValue> 
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);

    /**
     * @brief The name extracted from the passed in token.
     * 
     */
    std::string name;
};


/**
 * @brief Base class of any binary operation like addition and comparison.
 * 
 */
class BinaryOperation: public Expression {
public:
    /**
     * @brief Construct a new Binary Operation object from the given left and
     * right operands.
     * 
     * @param left the left operand,
     * @param right the right operand.
     */
    BinaryOperation(std::unique_ptr<Expression> left,
        std::unique_ptr<Expression> right);
        
protected:
    /**
     * @brief The left operand.
     * 
     */
    std::unique_ptr<Expression> left;

    /**
     * @brief The right operand.
     * 
     */
    std::unique_ptr<Expression> right;
};


/**
 * @brief An Expression which adds the values of two other expressions.
 * 
 */
class Addition: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    /**
     * @brief Add the two operands and return the result.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> the sum of the operands.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression which subtracts the values of two other expressions.
 * 
 */
class Subtraction: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    /**
     * @brief Subtract the two operands and return the result.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> the difference of the operands.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression which multiplies the values of two other expressions.
 * 
 */
class Multiplication: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    /**
     * @brief Multiply the two operands and return the result.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> the product of the operands.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression which divides the values of two other expressions.
 * 
 */
class Division: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    /**
     * @brief Divide the two operands and return the result.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> the quotient of the operands.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression which compares the values of two other expressions
 * for equality. Only works if the two operand have the exact same type.
 * 
 */
class EqualComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    /**
     * @brief Compare the two operands for equality and return the result.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> ExpressionValue with type INT
     * and value 1 if the operands are equal, 0 if not.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression which compares the values of two other expressions and
 * determines if the left operand is greater than the right operand.
 * Only works if the two operand have the exact same type.
 * 
 */
class GreaterThanComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    /**
     * @brief Compare the two operands and return the result.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> ExpressionValue with type INT
     * and value 1 if the left operand is greater than the right operand,
     * 0 if not.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression which compares the values of two other expressions and
 * determines if the left operand is greater than or equal to the right operand.
 * Only works if the two operand have the exact same type.
 * 
 */
class GreaterThanOrEqualComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    /**
     * @brief Compare the two operands and return the result.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> ExpressionValue with type INT
     * and value 1 if the left operand is greater than or equal to the right
     * operand, 0 if not.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression which compares the values of two other expressions and
 * determines if the left operand is less than the right operand.
 * Only works if the two operand have the exact same type.
 * 
 */
class LessThanComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    /**
     * @brief Compare the two operands and return the result.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> ExpressionValue with type INT
     * and value 1 if the left operand is less than the right operand,
     * 0 if not.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression which compares the values of two other expressions and
 * determines if the left operand is less than or equal to the right operand.
 * Only works if the two operand have the exact same type.
 * 
 */
class LessThanOrEqualComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    /**
     * @brief Compare the two operands and return the result.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> ExpressionValue with type INT
     * and value 1 if the left operand is less than or equal to the right
     * operand, 0 if not.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression which compares the values of two other expressions
 * for inequality.
 * Only works if the two operand have the exact same type.
 * 
 */
class NotEqualComparison: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    /**
     * @brief Compare the two operands for inequality and return the result.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> ExpressionValue with type INT
     * and value 1 if the operands are not equal, 0 if not.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression that connects two operands with an and.
 * 
 */
class AndConnective: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    
    /**
     * @brief Evaluate the and operation.
     * 
     * Evaluate the left operand first. If it is an ExpressionValue with type
     * INT and value 0, stop and return it. Otherwise, return the evaluation
     * of the right operand.
     * 
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> ExpressionValue with the value
     * described above.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression which connets two operands with an or.
 * 
 */
class OrConnective: public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    /**
     * @brief Evaluate the or operation.
     * 
     * Evaluate the left operand first. If it is an ExpressionValue with type
     * INT and value 1, stop and return it. Otherwise, return the evaluation
     * of the right operand.
     * 
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> ExpressionValue with the value
     * described above.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
};


/**
 * @brief An Expression which assigns a value to a name (variable).
 * 
 */
class Assignment: public Expression {
public:
    /**
     * @brief Construct a new Assignment object.
     * 
     * @param left the name to which the value should be assigned.
     * @param right the expression evaluating to what should be assigned.
     */
    Assignment(std::unique_ptr<Name> left,
        std::unique_ptr<Expression> right);

    /**
     * @brief Evaluate the assignment statement.
     * 
     * Set the value to which <right> evaluates to as a variable
     * with name <name>.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> the evaluation of <right>.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);

private:
    std::shared_ptr<Name> left;
    std::shared_ptr<Expression> right;
};


/**
 * @brief An expression which provides a scope for variables.
 * 
 */
class Block: public Expression {
public:
    /**
     * @brief Evaluate all the expressions associated to this block.
     * 
     * Create a new environment for those expressions which has the passed
     * in evironment as its parent.
     * 
     * 
     * @param parent The environment around this block statement.
     * @return std::shared_ptr<ExpressionValue> the value of the last
     * expression in this block.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& parent);

    /**
     * @brief Add an expression to this block.
     * 
     * @param expr the expression that should be added.
     */
    void addExpression(std::unique_ptr<Expression>& expr);

private:
    /**
     * @brief the list of all expression in this block.
     *
     */
    std::vector<std::unique_ptr<Expression>> exprList;
};


/**
 * @brief An expression which executes blocks based on conditions.
 * 
 */
class IfStatement: public Expression {
public:
    /**
     * @brief Construct a new If Statement object.
     * 
     * @param condition if this evaluates to a nonzero value, <ifBlock> will be
     * evaluated, otherwise <elseBlock> will be evaluated.
     * @param ifBlock the block directly following the if statement.
     * @param elseBlock the block following a potential else statement.
     * Can be nullptr.
     */
    IfStatement(std::unique_ptr<Expression>& condition,
        std::unique_ptr<Block>& ifBlock, std::unique_ptr<Block>& elseBlock);

    /**
     * @brief Evaluate the condition and act upon its value.
     * 
     * @param env The environment which provides the context for the variables.
     * This will be passed on to either <ifBlock> or <elseBlock>.
     * @return std::shared_ptr<ExpressionValue> the value of the <ifBlock> or
     * <elseBlock>.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);

private:
    /**
     * @brief The condition which determines whether <ifBlock> or <elseBlock>
     * is evaluated. If this evaluates to a nonzero value, <ifBlock> will be
     * evaluated, otherwise <elseBlock> will be evaluated.
     * 
     */
    std::unique_ptr<Expression> condition;

    /**
     * @brief The block that will be executed if <condition> evaluates to a
     * nonzero value.
     * 
     */
    std::unique_ptr<Expression> ifBlock;

    /**
     * @brief The block that will be executed if it is not a nullptr and
     * <condition> evaluates to 0.
     * 
     */
    std::unique_ptr<Expression> elseBlock;
};


/**
 * @brief An Abstract Expression that holds a function with its parameter names
 * and its body.
 * 
 */
class Function: public Expression {
public:
    /**
     * @brief Get the Parameter Names list.
     * 
     * @return const std::vector<std::string>& The list of parameter names
     * that are defined for this function.
     */
    virtual const std::vector<std::string>& getParameterNames() const = 0;
};


/**
 * @brief An Expression which holds a function defined dynamically while
 * parsing.
 * 
 */
class CustomFunction: public Function {
public:
    /**
     * @brief Evaluate the function body.
     * 
     * @param env The environment which provides the context for the variables.
     * Parameters must already be assigned to the names in <parameters>.
     * @return std::shared_ptr<ExpressionValue> The value of the function body
     * block <body>.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);

    /**
     * @brief Get the Parameter Names list.
     * 
     * @return const std::vector<std::string>& The list of parameter names
     * that are defined for this function.
     */
    const std::vector<std::string>& getParameterNames() const;

    /**
     * @brief Add a parameter to the parameters list.
     * 
     * @param name the name of that parameter.
     */
    void addParameter(std::unique_ptr<Name>& name);

    /**
     * @brief Set the <body> of the function, which is usually a Block.
     * 
     * @param body 
     */
    void setBody(std::unique_ptr<Expression>& body);

private:
    /**
     * @brief The list of parameters of this function.
     * 
     */
    std::vector<std::string> parameters;

    /**
     * @brief The body of this function.
     * 
     */
    std::unique_ptr<Expression> body;
};


/**
 * @brief An Expression that wraps a CustomFunction, so that it can be assigned
 * to a variable instead of being executed directly.
 * 
 */
class FunctionWrapper: public Expression {
public:
    /**
     * @brief Construct a new Function Wrapper object.
     * 
     * @param function the CustomFunction to wrap.
     */
    FunctionWrapper(std::shared_ptr<CustomFunction>& function);
    
    /**
     * @brief Evaluate this FunctionWrapper by returning the function which
     * was wrapped.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> the function which has been
     * wrapped by this.
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);

private:
    /**
     * @brief The function that is wrapped.
     * 
     */
    std::shared_ptr<CustomFunction> function;
};


/**
 * @brief An Expression which is a function that prints a string to stdout.
 * 
 */
class PrintFunction: public Function {
public:
    /**
     * @brief Construct a new Print Function object.
     * 
     */
    PrintFunction();
    
    /**
     * @brief Evaluate the print function by printing its parameter to stdout.
     * 
     * @param env The environment which provides the context for the variables.
     * @return std::shared_ptr<ExpressionValue> a nullptr;
     */
    std::shared_ptr<ExpressionValue> evaluate(
        std::shared_ptr<Environment>& env);
    
    /**
     * @brief Get the Parameter Names list.
     * 
     * @return const std::vector<std::string>& The list of parameter names
     * that are defined for this function.
     */
    const std::vector<std::string>& getParameterNames() const;

private:
    /**
     * @brief The list of parameters of this function.
     * 
     */
    std::vector<std::string> parameterNames;
};


/**
 * @brief An Expression which invokes a function.
 * 
 */
class Invocation: public Expression {
public:
    /**
     * @brief Construct a new Invocation object which calls the function
     * <functionName>.
     * 
     * @param functionName the name of the function which is called.
     */
    Invocation(std::unique_ptr<Name>& functionName);

    /**
     * @brief Evaluate this Invocation.
     * 
     * Create a new environment which has all the parameters assigned.
     * 
     * @param env The environment which provides the context for the variables.
     * Contains only the parameters to the function. All the other variables
     * are accessible through its parent.
     * @return std::shared_ptr<ExpressionValue> the value returned by the
     * function.
     */
    std::shared_ptr<ExpressionValue> evaluate(std::shared_ptr<Environment>& env);

    /**
     * @brief Add an argument to this invocation.
     * 
     * @param arg the argument to add.
     */
    void addArgument(std::unique_ptr<Expression>& arg);

private:
    /**
     * @brief The name of the function to call.
     * 
     */
    std::string functionName;

    /**
     * @brief The list of arguments to the function call.
     * 
     */
    std::vector<std::unique_ptr<Expression>> arguments;
};


/**
 * @brief A global environment pre-populated with all global variables and
 * builtins.
 * 
 */
class GlobalEnvironment: public Environment {
public:
    /**
     * @brief Construct a new Global Environment object.
     * 
     */
    GlobalEnvironment();  
};


#endif
