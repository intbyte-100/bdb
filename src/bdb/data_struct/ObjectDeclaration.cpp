#include "ObjectDeclaration.h"
#include "../util/utils.h"



byte bdb::ObjectDeclaration::regByte() {
    return byteCount++;
}

byte bdb::ObjectDeclaration::regShort() {
    return shortCount++;
}

byte bdb::ObjectDeclaration::regInt() {
    return intCount++;
}

byte bdb::ObjectDeclaration::regFloat() {
    return floatCount++;
}

byte bdb::ObjectDeclaration::regDouble() {
    return doubleCount++;
}

byte bdb::ObjectDeclaration::regLong() {
    return longCount++;
}

void bdb::ObjectDeclaration::reg() {
    declarations.push_back(this);
    reference = declarations.size()-1;
}

std::shared_ptr<bdb::ObjectInstance> bdb::ObjectDeclaration::newInstance(bool feelInstancesWithNulls) const {
    auto instance = getInstance();
    instance->reference = null_ref;
    for (int i = 0; i < byteCount; ++i) instance->bytes.push_back(0);
    for (int i = 0; i < shortCount; ++i) instance->shorts.push_back(0);
    for (int i = 0; i < intCount; ++i) instance->integers.push_back(0);
    for (int i = 0; i < floatCount; ++i) instance->floats.push_back(0);
    for (int i = 0; i < doubleCount; ++i) instance->doubles.push_back(0);
    for (int i = 0; i < longCount; ++i) instance->longs.push_back(0);
    for (int i = 0; i < references.size(); i++) {
        instance->instances.push_back(nullptrByDefault[i] || feelInstancesWithNulls ? nullptr : references[i]->newInstance());
    }
    instance->parent = reference;
    return instance;
}

byte bdb::ObjectDeclaration::regObject(ObjectDeclaration *objectDeclaration, bool nullByDefault) {
    references.push_back(objectDeclaration);
    nullptrByDefault.push_back(nullByDefault);
    return references.size() - 1;
}

