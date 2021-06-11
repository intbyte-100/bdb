#include "utils.h"


std::vector<bdb::ObjectInstance*> bdb::instances = std::vector<ObjectInstance*>();
std::vector<bdb::ObjectDeclaration*> bdb::declarations = std::vector<ObjectDeclaration*>();


bdb::ObjectInstance* bdb::getInstance() {
    if (!instances.empty()) {
        auto element = instances.back();
        instances.pop_back();
        return element;
    } else {
        return new bdb::ObjectInstance();
    }
}


