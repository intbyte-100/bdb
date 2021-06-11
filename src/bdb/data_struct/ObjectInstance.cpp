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
    if(instances.size() < poolSize)
        instances.push_back(this);
    else
        delete this;
}


