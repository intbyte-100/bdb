
#include "data_struct/ObjectInstance.h"
#include "bdb.h"
#include "util/utils.h"


unsigned int bdb::poolSize = 16;
unsigned short bdb::null_ref = 65535;

void bdb::update() {
    for (auto declaration: declarations) {
        declaration->size = declaration->byteCount +
                declaration->shortCount * sizeof(short) +
                declaration->intCount * sizeof(int) +
                declaration->floatCount * sizeof(float) +
                declaration->doubleCount * sizeof(double) +
                declaration->longCount * sizeof(long) +
                declaration->references.size() * 3;
        declaration->manifestSize = (declaration->byteCount != 0 ? 3 : 0) +
                (declaration->shortCount != 0 ? 3 : 0) +
                (declaration->intCount != 0 ? 3 : 0) +
                (declaration->floatCount != 0 ? 3 : 0) +
                (declaration->doubleCount != 0 ? 3 : 0) +
                (declaration->longCount != 0 ? 3 : 0) +
                (!declaration->references.empty() ? 3 : 0);
    }
}
