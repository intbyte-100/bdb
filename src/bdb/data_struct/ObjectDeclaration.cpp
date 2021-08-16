#include "ObjectDeclaration.h"
#include "../util/utils.h"

#define fori(var) for(int i = 0; i < var; i++)

#define initArrays(arrayType, arrayName, arrayCount)                                                                   \
    if (arrayCount > 0) {                                                                                              \
        instance->arrayName = new std::vector<std::vector<arrayType> *>();                                             \
        fori(arrayCount) { instance->arrayName->push_back(new std::vector<arrayType>()); }                             \
    }

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


byte bdb::ObjectDeclaration::regByteArray() {
    return byteArrayCount++;
}

byte bdb::ObjectDeclaration::regShortArray() {
    return shortArrayCount++;
}

byte bdb::ObjectDeclaration::regIntArray() {
    return intArrayCount++;
}

byte bdb::ObjectDeclaration::regFloatArray() {
    return floatArrayCount++;
}

byte bdb::ObjectDeclaration::regDoubleArray() {
    return doubleArrayCount++;
}

byte bdb::ObjectDeclaration::regLongArray() {
    return longArrayCount++;
}

byte bdb::ObjectDeclaration::regObjectArray() {
    return objectArrayCount++;
}


void bdb::ObjectDeclaration::reg() {
    declarations.push_back(this);
    id = declarations.size() - 1;
}

std::shared_ptr<bdb::ObjectInstance> bdb::ObjectDeclaration::newInstance(bool feelInstancesWithNulls) const {
	auto instance = getInstance();
	instance->reference = null_ref;
	instance->bytes.resize(byteCount);
	instance->shorts.resize(shortCount);
    instance->integers.resize(intCount);
    instance->floats.resize(floatCount);
    instance->doubles.resize(doubleCount);
    instance->longs.resize(longCount);
    fori(references.size()) {
        instance->objects.push_back(nullptrByDefault[i] || feelInstancesWithNulls ? nullptr
                                                                                  : references[i]->newInstance());
    }

    initArrays(signed_byte, byteArrays, byteArrayCount);
    initArrays(short, shortArrays, shortArrayCount);
    initArrays(int, intArrays, intArrayCount);
    initArrays(float, floatArrays, floatArrayCount);
    initArrays(double, doubleArrays, doubleArrayCount);
    initArrays(long, longArrays, longArrayCount);
    initArrays(std::shared_ptr<ObjectInstance>, objectArrays, objectArrayCount);
    instance->parentId = id;
    return instance;
}

byte bdb::ObjectDeclaration::regObject(ObjectDeclaration *objectDeclaration, bool nullByDefault) {
    references.push_back(objectDeclaration);
    nullptrByDefault.push_back(nullByDefault);
    return references.size() - 1;
}



