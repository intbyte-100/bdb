#include "src/bdb/DataBuffer.h"
#include "src/bdb/data_struct/ObjectDeclaration.h"
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp)
#include <iostream>

// clang-format off
bdbClass(Entity,
   bdbReg()
);


bdbClass(Test,
    bdbInts(a, b, c, d, e)
    bdbReg()
)
int main() {
    //serialization tests:

    bdb::DataBuffer buffer;

    Entity::object->regObjectArray();
    Entity::reg();
    Test::reg();
    
    bdb::update();
      
    auto obj = Entity::object->newInstance();
    
    for (int i = 0; i < 21845; i++) {
        auto test = Test::object->newInstance();
        Test::a(test) = 4;
        Test::b(test) = 5;
        Test::c(test) = 6;
        obj->objectArrays->at(0)->push_back(test);
    }

    
    
    auto bytes = buffer.serialize(obj);
    auto object = buffer.deserialize(bytes, obj->parentId);
    
    std::cout << bytes.size();
    return 0;
}
