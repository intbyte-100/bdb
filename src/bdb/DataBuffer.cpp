#include "DataBuffer.h"
#include "util/ObjectPool.h"

#define putPrimitivesToBuffer(type_code, type, vector) \
if(!vector.empty()) { \
    buffer::put(type_code, &serializedObject); \
    buffer::put((unsigned short) vector.size(), &serializedObject); \
    buffer::put<type>(&vector, &serializedObject); \
}

void bdb::DataBuffer::enable(byte attribute) {
    config = config | attribute;
}

void bdb::DataBuffer::disable(byte attribute) {
    config &= ~attribute;
}

bool bdb::DataBuffer::isEnable(byte attribute) {
    byte cfg = config;
    if(attribute != ZIP) cfg &= ~ZIP;
    if(attribute != REF_32_BIT) cfg &= ~REF_32_BIT;
    return attribute == cfg;
}

std::vector<byte> bdb::DataBuffer::write(bdb::ObjectInstance *objectInstance) {
    std::vector<byte> wroteData;
    std::vector<ObjectPool*> objectPools;
    updatePool();
    pool[objectInstance->parent-LAST_BASE_TYPE-1].put(objectInstance, pool, &objectPools);
    std::vector<byte> byteBuffer;
    std::vector<byte> serializedObject;

    for (auto objectPool: objectPools) {
        serializedObject.clear();
        objectPool->usedBefore = false;

        buffer::put<byte>(objectPool->declarationID, &serializedObject);
        buffer::put(objectPool->size, &serializedObject);

        putPrimitivesToBuffer(BYTE, signed_byte, objectPool->bytes)
        putPrimitivesToBuffer(SHORT, short, objectPool->shorts)
        putPrimitivesToBuffer(INT, int, objectPool->integers)
        putPrimitivesToBuffer(FLOAT, float, objectPool->floats)
        putPrimitivesToBuffer(DOUBLE, double, objectPool->doubles)
        putPrimitivesToBuffer(LONG, long, objectPool->longs)

        buffer::put<byte>(OBJECT, &serializedObject);
        buffer::put<unsigned short>(objectPool->instances.size(), &serializedObject);
        for (int i = 0; i < objectPool->instances.size(); i++) {
            buffer::put<byte>(objectPool->parentInstances[i], &serializedObject);
            buffer::put<unsigned short>(objectPool->instances[i], &serializedObject);
        }
        buffer::merge(&wroteData, serializedObject);
    }
    return wroteData;
}


bdb::ObjectInstance *bdb::DataBuffer::read(std::vector<byte> &data, byte declarationID) {
    unsigned long index = 0;
    updatePool();
    while (true){
        unsigned int bufferIndex = 0;

        auto id = buffer::get<byte>(&data, bufferIndex);
        auto normalizedID = id - LAST_BASE_TYPE - 1;
        auto countObject = buffer::get<unsigned short>(&data, bufferIndex);
        auto objectPool = pool[normalizedID];
        index += 3;
        while (true) {
            auto type = buffer::get<byte>(&data, bufferIndex);
            auto count = buffer::get<unsigned short>(&data, bufferIndex);
            switch (type) {
                case BYTE:


                    break;
                case SHORT: break;
                case INT: break;
                case FLOAT: break;
                case DOUBLE: break;
                case LONG: break;
                case OBJECT: break;
                case GENERALIZING_MAP: break;
                case TYPED_MAP: break;
                default: throw std::runtime_error(std::string("unknown type "+std::to_string((int) type)+": element index = "+std::to_string(bufferIndex)+"; object id "+std::to_string(id)));
            }
        }
        if(++index > data.size()) break;
    }
    return nullptr;
}


void bdb::DataBuffer::updatePool() {
    if(pool == nullptr || poolSize < declarations.size()){
        delete[] pool;
        poolSize = declarations.size();
        pool = new ObjectPool[poolSize];
    }
}

bdb::DataBuffer::~DataBuffer() {
    delete[] pool;
}




