#include "ObjectCache.h"
#include "../DataBuffer.h"
#include "utils.h"

template <typename T>
void bdb::ObjectCache::serializeArray(byte type, unsigned short &arrayCount, std::vector<byte> *arrayCache,
                                      std::vector<std::vector<T> *> *arrays) {
    if (arrays != nullptr) {
        for (auto i : *arrays) {
            buffer::put<byte>(type, &pointerArrayCache);

            if (i != nullptr) {
                buffer::put((unsigned short) i->size(), arrayCache);
                buffer::put(i, arrayCache);
                buffer::put(arrayCount++, &pointerArrayCache);
                continue;
            }
            buffer::put(null_ref, &pointerArrayCache);
        }
    }
}

void bdb::ObjectCache::serializeObjectArray(DataBuffer *buffer, std::vector<ObjectCache *> *cachePool,
                                            unsigned short &arrayCount, std::vector<byte> *arrayCache,
                                            std::vector<std::vector<std::shared_ptr<ObjectInstance>> *> *arrays) {
    if (arrays == nullptr)
        return;
    for (auto i : *arrays) {
        buffer::put<byte>(OBJECT_ARRAY, &pointerArrayCache);
        if (i != nullptr) {
            buffer::put((unsigned short)i->size(), arrayCache);
            for (auto &object : *i) {
                if (object == nullptr) {
                    buffer::put((byte)0, arrayCache);
                    buffer::put(null_ref, arrayCache);
                } else {
                    put(object, buffer, cachePool);
                    buffer::put(object->parentId, arrayCache);
                    buffer::put((unsigned short)object->reference, arrayCache);
                }
            }
            buffer::put(arrayCount++, &pointerArrayCache);
            continue;
        }
        buffer::put(null_ref, &pointerArrayCache);
    }
}

void bdb::ObjectCache::put(const std::shared_ptr<ObjectInstance> &instance, DataBuffer *buffer,
                           std::vector<ObjectCache *> *objectPools) {
    size++;
    if (instance->reference != null_ref) return;
    instance->reference = lastReference++;
    if (!usedBefore) {
        usedBefore = true;
        declarationID = instance->parentId;
        objectPools->push_back(this);
    }

    buffer::merge(&bytes, &instance->bytes);
    buffer::merge(&shorts, &instance->shorts);
    buffer::merge(&integers, &instance->integers);
    buffer::merge(&floats, &instance->floats);
    buffer::merge(&doubles, &instance->doubles);
    buffer::merge(&longs, &instance->longs);

    for (int i = 0; i < instance->objects.size(); i++) {
        parentInstances.push_back(declarations[instance->parentId]->references[i]->id);

        auto object = instance->objects[i];
        if (object == nullptr) {
            instances.push_back(null_ref);
            continue;
        }

        buffer->cache[object->parentId].put(object, buffer, objectPools);
        instances.push_back(object->reference);
    }

    serializeArray(BYTE_ARRAY, buffer->byteArrayCount, &buffer->byteArrayCache, instance->byteArrays);
    serializeArray(SHORT_ARRAY, buffer->shortArrayCount, &buffer->shortArrayCache, instance->shortArrays);
    serializeArray(INT_ARRAY, buffer->intArrayCount, &buffer->intArrayCache, instance->intArrays);
    serializeArray(FLOAT_ARRAY, buffer->floatArrayCount, &buffer->floatArrayCache, instance->floatArrays);
    serializeArray(DOUBLE_ARRAY, buffer->doubleArrayCount, &buffer->doubleArrayCache, instance->doubleArrays);
    serializeArray(LONG_ARRAY, buffer->longArrayCount, &buffer->longArrayCache, instance->longArrays);

    serializeObjectArray(buffer, objectPools, buffer->objectArrayCount, &buffer->objectArrayCache,
                         instance->objectArrays);
}

void bdb::ObjectCache::clear() {
    pointerArrayCache.clear();
    parentInstances.clear();
    instances.clear();
    integers.clear();
    doubles.clear();
    objects.clear();
    shorts.clear();
    floats.clear();
    longs.clear();
    bytes.clear();
    lastReference = 0;
    size = 0;
}

void bdb::ObjectCache::structureCacheToObjects(const ArrayBuffer &arrayBuffer) {
    unsigned short byteVectorIndex = 0, shortVectorIndex = 0, intVectorIndex = 0, floatVectorIndex = 0,
                   doubleVectorIndex = 0, longVectorIndex = 0;

    auto declaration = declarations[declarationID];
    unsigned int bufferIndex = 0;

    for (int i = 0; i < size; i++) {
        unsigned short byteArrayIndex = 0, shortArrayIndex = 0, intArrayIndex = 0, floatArrayIndex = 0,
                       doubleArrayIndex = 0, longArrayIndex = 0;

        auto instance = declaration->newInstance(true);

        for (int j = 0; j < declaration->arrayCount; j++) {
            auto type = buffer::get<byte>(&pointerArrayCache, bufferIndex);
            auto pointer = buffer::get<unsigned short>(&pointerArrayCache, bufferIndex);

            if (type == BYTE_ARRAY)
                instance->byteArrays->at(byteArrayIndex++) = arrayBuffer.byteArrays[pointer];
            else if (type == SHORT_ARRAY)
                instance->shortArrays->at(shortArrayIndex++) = arrayBuffer.shortArrays[pointer];
            else if (type == INT_ARRAY)
                instance->intArrays->at(intArrayIndex++) = arrayBuffer.intArrays[pointer];
            else if (type == FLOAT_ARRAY)
                instance->floatArrays->at(floatArrayIndex++) = arrayBuffer.floatArrays[pointer];
            else if (type == DOUBLE_ARRAY)
                instance->doubleArrays->at(doubleArrayIndex++) = arrayBuffer.doubleArrays[pointer];
            else if (type == LONG_ARRAY)
                instance->longArrays->at(longArrayIndex++) = arrayBuffer.longArrays[pointer];
        }

        for (int j = 0; j < declaration->byteCount; j++)
            instance->bytes[j] = bytes[byteVectorIndex++];
        for (int j = 0; j < declaration->shortCount; j++)
            instance->shorts[j] = shorts[shortVectorIndex++];
        for (int j = 0; j < declaration->intCount; j++)
            instance->integers[j] = integers[intVectorIndex++];
        for (int j = 0; j < declaration->floatCount; j++)
            instance->floats[j] = floats[floatVectorIndex++];
        for (int j = 0; j < declaration->doubleCount; j++)
            instance->doubles[j] = doubles[doubleVectorIndex++];
        for (int j = 0; j < declaration->longCount; j++)
            instance->longs[j] = longs[longVectorIndex++];
        objects.push_back(instance);
    }
}

void bdb::ObjectCache::flush(ObjectCache *pool) {

    auto declaration = declarations[declarationID];
    unsigned short objectVectorIndex = 0;
    for (const auto &object : objects) {
        for (int j = 0; j < declaration->references.size(); j++) {
            if (instances[objectVectorIndex] == null_ref) {
                object->objects[j] = nullptr;
                objectVectorIndex++;
                continue;
            }
            object->objects[j] = pool[parentInstances[objectVectorIndex]].objects[instances[objectVectorIndex]];
            objectVectorIndex++;
        }
    }
}

bdb::ObjectCache::~ObjectCache() = default;
