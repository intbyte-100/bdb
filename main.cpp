#include <iostream>
#include "src/bdb/DataBuffer.h"
#include "src/bdb/data_struct/ObjectDeclaration.h"
#include "src/bdb/data_struct/TypedMap.h"


int main() {

    bdb::DataBuffer buffer;

    auto entity = new bdb::ObjectDeclaration();
    auto entity2 = new bdb::ObjectDeclaration();

    entity->reg();
    entity2->reg();
    entity2->regLong();
    byte object = entity->regObject(entity, true);
    entity->regObject(entity, true);
    entity->regObject(entity, true);
    entity->regObject(entity, true);


    bdb::update();

    auto instance = entity->newInstance();
    instance->instances[object] = instance;

    auto bytes = buffer.write(instance);
    std::cout << "entity size: " << entity->size << "\n" << "buffer size: " << bytes.size() << "\n" << "total size: " << entity->size + entity->manifestSize << "\n";

    for(auto i: bytes)
        std::cout << (int) i << " ";

    std::cout << std::endl;


    std::vector<byte> buffer2;
    bdb::buffer::put(5, &buffer2);
    bdb::buffer::put(58, &buffer2);

    delete entity;
    delete entity2;
    delete instance;
    return 0;
}
