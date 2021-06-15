#include <iostream>
#include "src/bdb/DataBuffer.h"
#include "src/bdb/data_struct/ObjectDeclaration.h"
#include "src/bdb/data_struct/TypedMap.h"


int main() {

    bdb::DataBuffer buffer;

    auto entity = new bdb::ObjectDeclaration();
    auto entity2 = new bdb::ObjectDeclaration();
    byte i = entity2->regLong();
    byte i3 = entity2->regLong();
    entity->regFloat();
    entity->regObject(entity2, false);
    entity->regObject(entity2, true);


    entity->reg();
    entity2->reg();


    bdb::update();

    auto instance = entity->newInstance();
    auto bytes = buffer.write(instance);
    buffer.read(bytes, entity->reference);
    std::cout << "entity size: " << entity->size << "\n" << "buffer size: " << bytes.size() << "\n" << "total size: " << entity->size + entity->manifestSize << "\n";

    for(auto i: bytes)
        std::cout << (int) i << " ";

    std::cout << std::endl;


    std::vector<byte> buffer2;
    bdb::buffer::put(5, &buffer2);
    bdb::buffer::put(58, &buffer2);

    delete entity;
    delete instance;
    return 0;
}
