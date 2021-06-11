#include "TypedMap.h"
#include <stdexcept>

#define type_error(type) throw std::runtime_error(std::string("value put to the map before is not ")+type)
#define element_not_found_error(key) throw std::runtime_error(std::string("element in the map with the key \""+key+"\" was not found"));
void bdb::TypedMap::toBytes(std::vector<byte> &vector) {
    Serializable::toBytes(vector);
}

void bdb::TypedMap::readBytes(std::vector<byte> &vector) {
    Serializable::readBytes(vector);
}

byte bdb::TypedMap::getType() {
    return TYPED_MAP;
}

void bdb::TypedMap::put(const std::string& key, signed_byte value) {
    if(map.count(key)){
        auto tuple = map[key];
        if(std::get<0>(tuple) != BYTE) type_error("byte");
        bytes[std::get<1>(tuple)] = value;
        return;
    }
    map[key] = std::make_tuple(BYTE, (unsigned short) bytes.size());
    bytes.push_back(value);
}

void bdb::TypedMap::put(const std::string& key, short value) {
    if(map.count(key)){
        auto tuple = map[key];
        if(std::get<0>(tuple) != SHORT) type_error("short");
        shorts[std::get<1>(tuple)] = value;
        return;
    }
    map[key] = std::make_tuple(SHORT, (unsigned short) shorts.size());
    shorts.push_back(value);
}

void bdb::TypedMap::put(const std::string& key, int value) {
    if(map.count(key)){
        auto tuple = map[key];
        if(std::get<0>(tuple) != INT) type_error("int");
        integers[std::get<1>(tuple)] = value;
        return;
    }
    map[key] = std::make_tuple(INT, (unsigned short) integers.size());
    integers.push_back(value);
}

void bdb::TypedMap::put(const std::string& key, float value) {
    if(map.count(key)){
        auto tuple = map[key];
        if(std::get<0>(tuple) != FLOAT) type_error("float");
        floats[std::get<1>(tuple)] = value;
        return;
    }
    map[key] = std::make_tuple(FLOAT, (unsigned short) floats.size());
    floats.push_back(value);
}

void bdb::TypedMap::put(const std::string& key, double value) {
    if(map.count(key)){
        auto tuple = map[key];
        if(std::get<0>(tuple) != DOUBLE) type_error("double");
        doubles[std::get<1>(tuple)] = value;
        return;
    }
    map[key] = std::make_tuple(DOUBLE, (unsigned short) doubles.size());
    doubles.push_back(value);
}

void bdb::TypedMap::put(const std::string& key, long value) {
    if(map.count(key)){
        auto tuple = map[key];
        if(std::get<0>(tuple) != LONG) type_error("long");
        longs[std::get<1>(tuple)] = value;
        return;
    }
    map[key] = std::make_tuple(LONG, (unsigned short) longs.size());
    longs.push_back(value);
}

signed_byte bdb::TypedMap::getByte(const std::string &key) {
    if(map.count(key)) {
        auto tuple = map[key];
        if(std::get<0>(tuple) != BYTE) type_error("byte");
        return bytes[std::get<1>(tuple)];
    }
    element_not_found_error(key);
}

short bdb::TypedMap::getShort(const std::string &key) {
    if(map.count(key)) {
        auto tuple = map[key];
        if(std::get<0>(tuple) != SHORT) type_error("short");
        return shorts[std::get<1>(tuple)];
    }
    element_not_found_error(key);
}

int bdb::TypedMap::getInt(const std::string &key) {
    if(map.count(key)) {
        auto tuple = map[key];
        if(std::get<0>(tuple) != INT) type_error("int");
        return integers[std::get<1>(tuple)];
    }
    element_not_found_error(key);
}

float bdb::TypedMap::getFloat(const std::string &key) {
    if(map.count(key)) {
        auto tuple = map[key];
        if(std::get<0>(tuple) != FLOAT) type_error("float");
        return floats[std::get<1>(tuple)];
    }
    element_not_found_error(key);
}

double bdb::TypedMap::getDouble(const std::string &key) {
    if(map.count(key)) {
        auto tuple = map[key];
        if(std::get<0>(tuple) != DOUBLE) type_error("double");
        return doubles[std::get<1>(tuple)];
    }
    element_not_found_error(key);
}

long bdb::TypedMap::getLong(const std::string &key) {
    if(map.count(key)) {
        auto tuple = map[key];
        if(std::get<0>(tuple) != LONG) type_error("long");
        return longs[std::get<1>(tuple)];
    }
    element_not_found_error(key);
}

bool bdb::TypedMap::contains(const std::string &key) {
    return map.count(key);
}

