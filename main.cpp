#include "src/bdb/DataBuffer.h"
#include "src/bdb/data_struct/ObjectDeclaration.h"
#include <iostream>

// clang-format off
bdbClass(Entity,
    bdbInts(a, b, c, d)
    bdbReg()
);

int main() {
    bdb::DataBuffer buffer;

    Entity::object->regFloatArray();
    Entity::object->regIntArray();
    Entity::object->regObjectArray();

    Entity::reg();
    bdb::update();
      
    auto obj = Entity::object->newInstance();
    
    obj->objectArrays->at(0)->push_back(obj);
    obj->intArrays->at(0)->push_back(3);
    obj->intArrays->at(0)->push_back(3);
    obj->intArrays->at(0)->push_back(3);
    

    obj->floatArrays->at(0)->push_back(3);
    obj->floatArrays->at(0)->push_back(3);
    obj->floatArrays->at(0)->push_back(3);
    
    obj->floatArrays->at(0)->push_back(3);
    auto bytes = buffer.serialize(obj);
    auto object = buffer.deserialize(bytes, obj->parentId);
    
    std::cout << bytes.size();
    return 0;
}
