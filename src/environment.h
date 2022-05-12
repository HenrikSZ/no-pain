#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <string>
#include <unordered_map>


class Function;


enum class ExpressionValueType {
    STRING,
    INT,
    FLOAT,
    FUNCTION
};


class ExpressionValue {
public:
    ExpressionValue() {}
    ~ExpressionValue() {}
    union {
        int payloadInt;
        float payloadFloat;
    };
    std::string payloadStr;
    std::shared_ptr<Function> payloadFunc;

    ExpressionValueType type;
};


class Environment {
public:
    Environment();
    Environment(std::shared_ptr<Environment>& parent);
    
    void setParent(std::shared_ptr<Environment>& parent);
    std::shared_ptr<ExpressionValue> getVariable(std::string& name);
    bool setVariableIfDefined(std::string& name, std::shared_ptr<ExpressionValue>& value);
    void setVariable(std::string& name, std::shared_ptr<ExpressionValue>& value);
    void setLocalVariable(std::string& name, std::shared_ptr<ExpressionValue>& value);

private:
    std::shared_ptr<Environment> parent;
    std::unordered_map<std::string, std::shared_ptr<ExpressionValue>> env;
};


#endif
