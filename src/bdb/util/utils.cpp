#include "utils.h"


std::vector<bdb::ObjectInstance*> bdb::instances = std::vector<ObjectInstance*>();
std::vector<bdb::ObjectDeclaration*> bdb::declarations = std::vector<ObjectDeclaration*>();


std::shared_ptr<bdb::ObjectInstance> bdb::getInstance() {
    return std::make_shared<ObjectInstance>();
}


