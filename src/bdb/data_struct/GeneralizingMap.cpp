#include "GeneralizingMap.h"


void bdb::GeneralizingMap::clear() {
    element_8_bit.clear();
    element_16_bit.clear();
    element_32_bit.clear();
    element_64_bit.clear();
    map.clear();
}

byte bdb::GeneralizingMap::getType() {
    return GENERALIZING_MAP;
}

void bdb::GeneralizingMap::readBytes(std::vector<byte> &vector) {
    Serializable::readBytes(vector);
}

void bdb::GeneralizingMap::toBytes(std::vector<byte> &vector) {
    Serializable::toBytes(vector);
}
