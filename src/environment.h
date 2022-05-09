#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <string>
#include <unordered_map>


enum class ExpressionValueType {
    STRING,
    INT,
    FLOAT
};


class ExpressionValue {
public:
    ExpressionValue() {}
    ~ExpressionValue() {}
    union {
        std::string payloadStr;
        int payloadInt;
        float payloadFloat;
    };

    ExpressionValueType type;
};


class Environment {
public:
    Environment();
    Environment(std::shared_ptr<Environment> parent);
    
    std::shared_ptr<ExpressionValue> getVariable(std::string& name);
    void setVariable(std::string& name, std::shared_ptr<ExpressionValue>& value);

private:
    std::shared_ptr<Environment> parent;
    std::unordered_map<std::string, std::shared_ptr<ExpressionValue>> env;
};


#endif
