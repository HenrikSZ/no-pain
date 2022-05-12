#include "environment.h"


Environment::Environment(): parent(nullptr) {}

Environment::Environment(std::shared_ptr<Environment>& parent): parent(parent) {}

void Environment::setParent(std::shared_ptr<Environment>& parent) {
    this->parent = parent;
}

std::shared_ptr<ExpressionValue> Environment::getVariable(std::string& name) {
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

bool Environment::setVariableIfDefined(
        std::string& name, std::shared_ptr<ExpressionValue>& value) {
    if (env.find(name) == env.end()) {
        if (parent) {
            return parent->setVariableIfDefined(name, value);
        } else {
            return false;
        }
    } else {
        env[name] = value;
        return true;
    }
}

void Environment::setVariable(
        std::string& name, std::shared_ptr<ExpressionValue>& value) {
    if (!parent || !parent->setVariableIfDefined(name, value))
        setLocalVariable(name, value);
}

void Environment::setLocalVariable(
        std::string& name, std::shared_ptr<ExpressionValue>& value) {
    env[name] = value;
}
