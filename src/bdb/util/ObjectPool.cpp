#include "ObjectPool.h"
#include "utils.h"

void bdb::ObjectPool::put(ObjectInstance *instance, ObjectPool *pool, std::vector<ObjectPool *> *objectPools) {
    size++;
    if(instance->reference != nullref) return;
    instance->reference = lastReference++;
    if(!usedBefore){
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
        parentInstances.push_back(declarations[instance->parent-LAST_BASE_TYPE-1]->references[i]->reference);

        auto object = instance->instances[i];
        if(object == nullptr) {
            instances.push_back(nullref);
            continue;
        }
        pool[object->parent-LAST_BASE_TYPE-1].put(object, pool, objectPools);
        instances.push_back(object->reference);
    }
}