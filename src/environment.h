#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <string>
#include <unordered_map>


class Function;


/**
 * @brief The type an expression evaluates to.
 * 
 * This can be STRING, INT, FLOAT or FUNCTION;
 * 
 */
enum class ExpressionValueType {
    STRING,
    INT,
    FLOAT,
    FUNCTION
};


/**
 * @brief The value an expression evaluates to.
 * 
 * There are different types of expression values, defined under
 * ExpressionValueType. Always set the <type> according to
 * the value type assigned to this Expression Value.
 * 
 */
class ExpressionValue {
public:
    /**
     * @brief Construct a new Expression Value object.
     * 
     */
    ExpressionValue();

    /**
     * @brief Destroy the Expression Value object.
     * 
     */
    ~ExpressionValue();

    union {
        /**
         * @brief Contains an integer value as an Expression Value,
         * if <type> is ExpressionValueType::INT.
         * 
         */
        int payloadInt;

         /**
         * @brief Contains a float value as an Expression Value,
         * if <type> is ExpressionValueType::FLOAT.
         * 
         */
        float payloadFloat;
    };
    /**
     * @brief Contains a string value as an Expression Value,
     * if <type> is ExpressionValueType::STRING.
     * 
     */
    std::string payloadStr;

    /**
     * @brief Contains a ifunction value as an Expression Value,
     * if <type> is ExpressionValueType::FUNCTION.
     * 
     */
    std::shared_ptr<Function> payloadFunc;

    /**
     * @brief The type of this Expression Value. Must be set in
     * accordance with the actual type stored in this object.
     * 
     */
    ExpressionValueType type;
};


/**
 * @brief The environment under which variables are defined.
 * 
 * An Environment can have access to a parent which will be
 * used to resolve variable names not found in itself. Usually,
 * variables should be set using setVariable. For initializing
 * function parameters for example, you would use setLocalVariable,
 * so that variables with the same name from an outer scope are reliably
 * shadowed. For assignments to bubble up to potential parent environments,
 * setVariableIfDefined is used internally.
 *
 */
class Environment {
public:
    /**
     * @brief Construct a new Environment object with no parent.
     * 
     */
    Environment();

    /**
     * @brief Construct a new Environment object with a parent.
     * 
     * @param parent the parent this environment should have.
     * 
     */
    Environment(std::shared_ptr<Environment>& parent);
    

    /**
     * @brief Set the Parent object.
     * 
     * @param parent the parent this environment should have.
     */
    void setParent(std::shared_ptr<Environment>& parent);

    /**
     * @brief Get the Variable object associated with name <name>.
     * 
     * If no variable is found under this name in this environment,
     * the search bubbles up to the <parent>.
     * 
     * @param name the name of the variable that should be searched for.
     * @return std::shared_ptr<ExpressionValue> to the variable
     * if it exists, otherwise nullptr.
     */
    std::shared_ptr<ExpressionValue> getVariable(std::string& name);
    

    /**
     * @brief Set a variable if it is defined in this environment.
     * 
     * If no variable is found under this name in this environment,
     * the search bubbles up to the <parent> (also using setVariableIfDefined).
     * 
     * @param name the name the variable.
     * @param value the value that should be stored in that variable.
     * @return true if a variable was found in this environment or a parent
     * environment and could be reassigned, false otherwise.
     */
    bool setVariableIfDefined(std::string& name,
        std::shared_ptr<ExpressionValue>& value);

    /**
     * @brief Set a variable in this environment or a parent environment.
     * 
     * If no variable is found under this name in this environment,
     * the search bubbles up to the <parent> (using setVariableIfDefined).
     * 
     * @param name the name the variable.
     * @param value the value that should be stored in that variable.
     */
    void setVariable(std::string& name,
        std::shared_ptr<ExpressionValue>& value);

    /**
     * @brief Set a variable in this environment.
     * 
     * The search DOES NOT bubble to the parent.
     * 
     * @param name the name the variable.
     * @param value the value that should be stored in that variable.
     */
    void setLocalVariable(std::string& name,
        std::shared_ptr<ExpressionValue>& value);

private:
    /**
     * @brief The parent of this environment.
     * 
     * It will be consulted for variables under certain conditions
     * when variables are not found in this environment.
     * 
     */
    std::shared_ptr<Environment> parent;

    /**
     * @brief The map of variable names to their value.
     * 
     */
    std::unordered_map<std::string, std::shared_ptr<ExpressionValue>> env;
};


#endif
