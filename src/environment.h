#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <string>
#include <unordered_map>


enum ValueType {
    STRING,
    INT,
    FLOAT
};


struct Value {
    union {
        std::string payloadStr;
        int payloadInt;
        float payloadFloat;
    };

    ValueType type;
};


class Environment {
public:
    Environment();
    Environment(std::shared_ptr<Environment> parent);
    
    std::shared_ptr<Value> getVariable(std::string& name);
    void setVariable(std::string& name, std::shared_ptr<Value>& value);

private:
    std::shared_ptr<Environment> parent;
    std::unordered_map<std::string, std::shared_ptr<Value>> env;
};


#endif
