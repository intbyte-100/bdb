#include "ObjectInstance.h"

#define deleteIfNotNull(name)                                                                                          \
    if (name != nullptr) {                                                                                             \
        for (auto i : *name) {                                                                                         \
            delete i;                                                                                                  \
        }                                                                                                              \
        delete name;                                                                                                   \
    }

bdb::ObjectInstance::~ObjectInstance() {
    deleteIfNotNull(byteArrays);
    deleteIfNotNull(shortArrays);
    deleteIfNotNull(intArrays);
    deleteIfNotNull(floatArrays);
    deleteIfNotNull(doubleArrays);
    deleteIfNotNull(longArrays);
}
