#include "environment.h"


Environment::Environment(): parent(nullptr) {}

Environment::Environment(std::shared_ptr<Environment> parent): parent(parent) {}

std::shared_ptr<Value> Environment::getVariable(std::string& name) {
    auto var = env.find(name);

    if (var == env.end()) {
        if (parent) {
            return parent->getVariable(name);
        } else {
            throw std::exception((std::string("Variable ") + name + std::string(" undefined")).c_str());
        }
    } else {
        return var->second;
    }
}

void Environment::setVariable(std::string& name, std::shared_ptr<Value>& value) {
    env[name] = value;
}
