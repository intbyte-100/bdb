#include "ObjectPool.h"
#include "utils.h"

void bdb::ObjectPool::put(ObjectInstance *instance, ObjectPool *pool, std::vector<ObjectPool *> *objectPools) {
    size++;
    if (instance->reference != nullref) return;
    instance->reference = lastReference++;
    if (!usedBefore) {
        usedBefore = true;
        declarationID = instance->parent;
        objectPools->push_back(this);
    }

    for (auto i: instance->bytes)
        bytes.push_back(i);
    for (auto i: instance->shorts)
        shorts.push_back(i);
    for (auto i: instance->integers)
        integers.push_back(i);
    for (auto i: instance->floats)
        floats.push_back(i);
    for (auto i: instance->doubles)
        doubles.push_back(i);
    for (auto i: instance->longs)
        longs.push_back(i);


    for (int i = 0; i < instance->instances.size(); i++) {
        parentInstances.push_back(declarations[instance->parent - LAST_BASE_TYPE - 1]->references[i]->reference);

        auto object = instance->instances[i];
        if (object == nullptr) {
            instances.push_back(nullref);
            continue;
        }

        pool[object->parent - LAST_BASE_TYPE - 1].put(object, pool, objectPools);
        instances.push_back(object->reference);
    }
}

void bdb::ObjectPool::clear() {
    parentInstances.clear();
    instances.clear();
    integers.clear();
    doubles.clear();
    shorts.clear();
    floats.clear();
    longs.clear();
    bytes.clear();
    lastReference = 0;
    size = 0;
}

void bdb::ObjectPool::structureDataToObjects() {
    unsigned short byteVectorIndex = 0, shortVectorIndex = 0, intVectorIndex = 0, floatVectorIndex = 0, doubleVectorIndex = 0, longVectorIndex = 0;
    for (int i = 0; i < size; i++) {
        auto declaration = declarations[declarationID - 1 - LAST_BASE_TYPE];
        auto instance = declaration->newInstance(true);

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

void bdb::ObjectPool::flush(ObjectPool *pool) {

    auto declaration = declarations[declarationID - 1 - LAST_BASE_TYPE];
    unsigned short objectVectorIndex = 0;
    for (auto object : objects) {
        for (int j = 0; j < declaration->references.size(); j++) {
            if (instances[objectVectorIndex] == nullref) {
                object->instances[j] = nullptr;
                objectVectorIndex++;
                continue;
            }
            object->instances[j] =
                    pool[parentInstances[objectVectorIndex] - LAST_BASE_TYPE - 1]
                            .objects[instances[objectVectorIndex]];
            objectVectorIndex++;
        }
    }

}
