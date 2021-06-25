#include <iostream>
#include "src/bdb/DataBuffer.h"
#include "src/bdb/data_struct/ObjectDeclaration.h"
#include "src/bdb/data_struct/TypedMap.h"


bdbClass(Entity,
    bdbBytes(x, y, z)
    bdbShorts(d,e,f)
    bdbReg(regShorts(), regBytes())
)


int main() {

    bdb::DataBuffer buffer;

    Entity::reg();

    auto obj = Entity::object->newInstance();
    Entity::x(obj) = 100;
    Entity::y(obj) = 100;
    Entity::z(obj) = 100;
    buffer.write(obj);
}
