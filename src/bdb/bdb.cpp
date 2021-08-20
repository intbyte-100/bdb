
#include "bdb.h"
#include "data_struct/ObjectInstance.h"
#include "util/utils.h"

unsigned short bdb::null_ref = 65535;
const std::string bdb::stringVersion = "1.0.0 alpha";
void bdb::update() {
    for (auto declaration : declarations) {
        declaration->size = declaration->byteCount + declaration->shortCount * sizeof(short) +
                            declaration->intCount * sizeof(int) + declaration->floatCount * sizeof(float) +
                            declaration->doubleCount * sizeof(double) + declaration->longCount * sizeof(long) +
                            declaration->references.size() * 3;

        declaration->manifestSize = (declaration->byteCount != 0 ? 5 : 0) + (declaration->shortCount != 0 ? 5 : 0) +
                                    (declaration->intCount != 0 ? 5 : 0) + (declaration->floatCount != 0 ? 5 : 0) +
                                    (declaration->doubleCount != 0 ? 5 : 0) + (declaration->longCount != 0 ? 5 : 0) +
                                    (!declaration->references.empty() ? 5 : 0);

        declaration->arrayCount = declaration->byteArrayCount + declaration->shortArrayCount +
                                  declaration->intArrayCount + declaration->floatArrayCount +
                                  declaration->doubleArrayCount + declaration->longArrayCount +
                                  declaration->objectArrayCount;
    }
}
