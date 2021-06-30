#include "ObjectInstance.h"
#include "../util/utils.h"

void bdb::ObjectInstance::free() {
    bytes.clear();
    shorts.clear();
    integers.clear();
    floats.clear();
    doubles.clear();
    longs.clear();
    instances.clear();
}


