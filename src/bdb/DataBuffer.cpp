#include "DataBuffer.h"
#include "util/ArrayBuffer.h"
#include "util/ObjectCache.h"
#include <sstream>

#define putPrimitivesToBuffer(type_code, type, vector)                                                                 \
    if (!vector.empty()) {                                                                                             \
        buffer::put(type_code, &serializedObject);                                                                     \
        buffer::put((unsigned short)vector.size(), &serializedObject);                                                 \
        buffer::put<type>(&vector, &serializedObject);                                                                 \
    }

void bdb::DataBuffer::enable(byte attribute) { config = config | attribute; }
void bdb::DataBuffer::disable(byte attribute) { config &= ~attribute; }

bool bdb::DataBuffer::isEnable(byte attribute) {
    byte cfg = config;
    if (attribute != COMPRESSING)
        cfg &= ~COMPRESSING;
    if (attribute != THIRTY_TWO_BIT_POINTERS)
        cfg &= ~THIRTY_TWO_BIT_POINTERS;
    return attribute == cfg;
}

void mergeCache(byte type, unsigned short arrayCount, std::vector<byte> &cache, std::vector<byte> &data) {
    if (arrayCount == 0)
        return;

    bdb::buffer::put(type, &data);
    bdb::buffer::put(arrayCount, &data);
    bdb::buffer::merge(&data, &cache);
}
std::vector<byte> bdb::DataBuffer::serialize(const std::shared_ptr<bdb::ObjectInstance> &objectInstance) {
    updateCache();
    std::vector<byte> wroteData;
    std::vector<ObjectCache *> objectPools;
    std::vector<byte> byteBuffer;
    std::vector<byte> serializedObject;

    cache[objectInstance->parentId].put(objectInstance, this, &objectPools);

    if (!extraCacheIsEmpty()) {
        wroteData.push_back(255);

        buffer::put<unsigned short>(extraCacheSize(), &wroteData);

        mergeCache(BYTE_ARRAY, byteArrayCount, byteArrayCache, wroteData);
        mergeCache(SHORT_ARRAY, shortArrayCount, shortArrayCache, wroteData);
        mergeCache(INT_ARRAY, intArrayCount, intArrayCache, wroteData);
        mergeCache(FLOAT_ARRAY, floatArrayCount, floatArrayCache, wroteData);
        mergeCache(DOUBLE_ARRAY, doubleArrayCount, doubleArrayCache, wroteData);
        mergeCache(LONG_ARRAY, longArrayCount, longArrayCache, wroteData);
        mergeCache(OBJECT_ARRAY, objectArrayCount, objectArrayCache, wroteData);
    }

    for (auto objectPool : objectPools) {
        unsigned short id = objectPool->declarationID;
        unsigned short size = declarations[id]->size * objectPool->size + declarations[id]->manifestSize +
                              objectPool->pointerArrayCache.size() + (objectPool->pointerArrayCache.empty() ? 0 : 3);

        serializedObject.clear();
        objectPool->usedBefore = false;

        buffer::put<byte>(objectPool->declarationID, &serializedObject);
        buffer::put(objectPool->size, &serializedObject);
        buffer::put(size, &serializedObject);

        putPrimitivesToBuffer(BYTE, signed_byte, objectPool->bytes);
        putPrimitivesToBuffer(SHORT, short, objectPool->shorts);
        putPrimitivesToBuffer(INT, int, objectPool->integers);
        putPrimitivesToBuffer(FLOAT, float, objectPool->floats);
        putPrimitivesToBuffer(DOUBLE, double, objectPool->doubles);
        putPrimitivesToBuffer(LONG, long, objectPool->longs);

        if (!objectPool->instances.empty()) {
            buffer::put(OBJECT, &serializedObject);
            buffer::put<unsigned short>(objectPool->instances.size(), &serializedObject);
            for (int i = 0; i < objectPool->instances.size(); i++) {
                buffer::put(objectPool->parentInstances[i], &serializedObject);
                buffer::put(objectPool->instances[i], &serializedObject);
            }
        }

        if (!objectPool->pointerArrayCache.empty()) {
            buffer::put(POINTER, &serializedObject);
            buffer::put<unsigned short>(objectPool->pointerArrayCache.size(), &serializedObject);
            buffer::merge(&serializedObject, &objectPool->pointerArrayCache);
        }

        buffer::merge(&wroteData, &serializedObject);

        for (auto &i : objectPool->objects) {
            i->reference = null_ref;
        }
        objectPool->clear();
    }
    clear();
    return wroteData;
}

template <typename T>
void desirializeArray(bdb::ArrayBuffer *arrayBuffer,
                      std::vector<std::vector<T> *> &vector,
                      unsigned short size,
                      std::vector<byte> *data,
                      unsigned int &index) {

    auto array = new std::vector<T>(bdb::buffer::get<T>(size, data, index));
    vector.push_back(array);
}

std::shared_ptr<bdb::ObjectInstance> bdb::DataBuffer::deserialize(std::vector<byte> &data, byte declarationID) {
    unsigned int index = 0;
    std::vector<ObjectCache *> usedPools;
    ArrayBuffer arrayBuffer;
    updateCache();

    if (data[0] == 255) {
        index = 1;
        unsigned short extraCacheSize = buffer::get<unsigned short>(&data, index) + 2;

        while (index < extraCacheSize) {
            byte type = buffer::get<byte>(&data, index);
            unsigned short count = buffer::get<unsigned short>(&data, index);

            for (int i = 0; i < count; i++) {
                unsigned short size = buffer::get<unsigned short>(&data, index);

                if (type == BYTE_ARRAY)
                    desirializeArray<signed_byte>(&arrayBuffer, arrayBuffer.byteArrays, size, &data, index);
                else if (type == SHORT_ARRAY)
                    desirializeArray<short>(&arrayBuffer, arrayBuffer.shortArrays, size, &data, index);
                else if (type == INT_ARRAY)
                    desirializeArray<int>(&arrayBuffer, arrayBuffer.intArrays, size, &data, index);
                else if (type == FLOAT_ARRAY)
                    desirializeArray<float>(&arrayBuffer, arrayBuffer.floatArrays, size, &data, index);
                else if (type == DOUBLE_ARRAY)
                    desirializeArray<double>(&arrayBuffer, arrayBuffer.doubleArrays, size, &data, index);
                else if (type == LONG_ARRAY)
                    desirializeArray<long>(&arrayBuffer, arrayBuffer.longArrays, size, &data, index);
                else if (type == OBJECT_ARRAY)
                    desirializeArray<byte>(
                        &arrayBuffer, arrayBuffer.serializedObjectPointerArrays, size * 3, &data, index);
            }
        }
    }

    while (index != data.size()) {
        unsigned int bufferIndex = index;

        auto id = buffer::get<byte>(&data, bufferIndex);

        auto objectCount = buffer::get<unsigned short>(&data, bufferIndex);
        auto size = buffer::get<unsigned short>(&data, bufferIndex);
        auto objectCache = &cache[id];

        objectCache->declarationID = id;
        objectCache->size = objectCount;
        index = bufferIndex;
        unsigned int objectsLastIndex = index + size;

        usedPools.push_back(objectCache);

        while (bufferIndex != objectsLastIndex) {
            auto type = buffer::get<byte>(&data, bufferIndex);
            unsigned short count = buffer::get<unsigned short>(&data, bufferIndex);

            if (type == BYTE)
                objectCache->bytes = buffer::get<signed_byte>(count, &data, bufferIndex);
            else if (type == SHORT)
                objectCache->shorts = buffer::get<short>(count, &data, bufferIndex);
            else if (type == INT)
                objectCache->integers = buffer::get<int>(count, &data, bufferIndex);
            else if (type == FLOAT)
                objectCache->floats = buffer::get<float>(count, &data, bufferIndex);
            else if (type == DOUBLE)
                objectCache->doubles = buffer::get<double>(count, &data, bufferIndex);
            else if (type == LONG)
                objectCache->longs = buffer::get<long>(count, &data, bufferIndex);
            else if (type == POINTER)
                objectCache->pointerArrayCache = buffer::get<byte>(count, &data, bufferIndex);
            else if (type == OBJECT)
                for (int i = 0; i < count; i++) {
                    objectCache->parentInstances.push_back(buffer::get<byte>(&data, bufferIndex));
                    objectCache->instances.push_back(buffer::get<unsigned short>(&data, bufferIndex));
                }
            else {
                std::stringstream stream;
                stream << "unknown type " << (int)type << ": element index = " << bufferIndex << "; object id " << id;
                throw std::runtime_error(stream.str());
            }
        }
        index = bufferIndex;
    }

    for (auto i : usedPools)
        i->structureCacheToObjects();
    for (auto i : usedPools) {
        i->flush(cache, arrayBuffer);
    }
    return cache[declarationID].objects[0];
}

void bdb::DataBuffer::updateCache() {
    if (cache == nullptr || cacheInstancesCount < declarations.size()) {
        delete[] cache;
        cacheInstancesCount = declarations.size();
        cache = new ObjectCache[cacheInstancesCount];
    }
}

bdb::DataBuffer::~DataBuffer() { delete[] cache; }

bool bdb::DataBuffer::extraCacheIsEmpty() {
    return byteArrayCache.empty() && shortArrayCache.empty() && intArrayCache.empty() && floatArrayCache.empty() &&
           doubleArrayCache.empty() && longArrayCache.empty() && objectArrayCache.empty();
}

unsigned short bdb::DataBuffer::extraCacheSize() {
    return byteArrayCache.size() + shortArrayCache.size() + intArrayCache.size() + floatArrayCache.size() +
           doubleArrayCache.size() + longArrayCache.size() + objectArrayCache.size() +
           (byteArrayCache.size() > 0 ? 3 : 0) + (shortArrayCache.size() > 0 ? 3 : 0) +
           (intArrayCache.size() > 0 ? 3 : 0) + (floatArrayCache.size() > 0 ? 3 : 0) +
           (doubleArrayCache.size() > 0 ? 3 : 0) + (longArrayCache.size() > 0 ? 3 : 0) +
           (objectArrayCache.size() > 0 ? 3 : 0);
}

void bdb::DataBuffer::clear() {
    byteArrayCache.clear();
    shortArrayCache.clear();
    intArrayCache.clear();
    floatArrayCache.clear();
    doubleArrayCache.clear();
    longArrayCache.clear();

    byteArrayCount = 0;
    shortArrayCount = 0;
    intArrayCount = 0;
    floatArrayCount = 0;
    doubleArrayCount = 0;
    longArrayCount = 0;
    objectArrayCount = 0;
}
     
