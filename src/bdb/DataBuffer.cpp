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
    if (attribute != ZIP) cfg &= ~ZIP;
    if (attribute != REF_32_BIT) cfg &= ~REF_32_BIT;
    return attribute == cfg;
}

std::vector<byte> bdb::DataBuffer::write(std::shared_ptr<bdb::ObjectInstance> objectInstance) {
    std::vector<byte> wroteData;
    std::vector<ObjectPool *> objectPools;
    updatePool();
    pool[objectInstance->parent].put(objectInstance, pool, &objectPools);
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

        if (!objectPool->instances.empty()) {
            buffer::put<byte>(OBJECT, &serializedObject);
            buffer::put<unsigned short>(objectPool->instances.size(), &serializedObject);
            for (int i = 0; i < objectPool->instances.size(); i++) {
                buffer::put<byte>(objectPool->parentInstances[i], &serializedObject);
                buffer::put<unsigned short>(objectPool->instances[i], &serializedObject);
            }
        }
        buffer::merge(&wroteData, &serializedObject);
        objectPool->clear();
    }
    return wroteData;
}


std::shared_ptr<bdb::ObjectInstance> bdb::DataBuffer::read(std::vector<byte> &data, byte declarationID) {
    unsigned int index = 0;
    std::vector<ObjectPool *> usedPools;
    updatePool();
    while (index != data.size()) {
        unsigned int bufferIndex = index;

        auto id = buffer::get<byte>(&data, bufferIndex);
        auto countObject = buffer::get<unsigned short>(&data, bufferIndex);
        auto objectPool = &pool[id];
        objectPool->declarationID = id;
        objectPool->size = countObject;
        index = bufferIndex;
        unsigned int objectsLastIndex =
                index + declarations[id]->size * countObject +
                declarations[id]->manifestSize;

        usedPools.push_back(objectPool);

        while (bufferIndex != objectsLastIndex) {
            auto type = buffer::get<byte>(&data, bufferIndex);
            auto count = buffer::get<unsigned short>(&data, bufferIndex);
            switch (type) {
                case BYTE: {
                    objectPool->bytes = buffer::get<signed_byte>(count, &data, bufferIndex);
                    break;
                }
                case SHORT: {
                    objectPool->shorts = buffer::get<short>(count, &data, bufferIndex);
                    break;
                }
                case INT: {
                    objectPool->integers = buffer::get<int>(count, &data, bufferIndex);
                    break;
                }
                case FLOAT: {
                    objectPool->floats = buffer::get<float>(count, &data, bufferIndex);
                    break;
                }
                case DOUBLE: {
                    objectPool->doubles = buffer::get<double>(count, &data, bufferIndex);
                    break;
                }
                case LONG: {
                    objectPool->longs = buffer::get<long>(count, &data, bufferIndex);
                    break;
                }
                case OBJECT: {
                    for (int i = 0; i < count; i++) {
                        objectPool->parentInstances.push_back(buffer::get<byte>(&data, bufferIndex));
                        objectPool->instances.push_back(buffer::get<unsigned short>(&data, bufferIndex));
                    }
                    break;
                }
                case GENERALIZING_MAP:
                case TYPED_MAP:
                    break;
                default:
                    throw std::runtime_error(std::string(
                            "unknown type " + std::to_string((int) type) + ": element index = " +
                            std::to_string(bufferIndex) + "; object id " + std::to_string(id)));
            }
        }
        index = bufferIndex;
    }

    for (auto i: usedPools) i->structureDataToObjects();
    for (auto i: usedPools){
        i->flush(pool);
    }
    return pool[declarationID].objects[0];
}


void bdb::DataBuffer::updatePool() {
    if (pool == nullptr || poolSize < declarations.size()) {
        delete[] pool;
        poolSize = declarations.size();
        pool = new ObjectPool[poolSize];
    }
}

bdb::DataBuffer::~DataBuffer() {
    delete[] pool;
}




