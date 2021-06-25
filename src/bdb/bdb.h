#pragma once

#include "util/macros_foreach.h"
#include <cstdint>


#define bdbClass(name, code) namespace name { bdb::ObjectDeclaration *object = new bdb::ObjectDeclaration(); code}
#define bdbVar(name) byte name;
#define DEFINE(macro) macro;

#define bdbReg(...) void reg() { \
    object->reg();               \
    FOR_EACH(DEFINE, __VA_ARGS__)\
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define bdbByteReg(name) name = object->regByte();
#define bdbByteGetter(name) signed_byte& name(bdb::ObjectInstance* instance) {\
    return instance->bytes[variables::name];                                  \
}
#define bdbBytes(...) namespace variables { FOR_EACH(bdbVar, __VA_ARGS__) } \
void regBytes() {                                                           \
    using namespace variables;                                              \
    FOR_EACH(bdbByteReg, __VA_ARGS__)                                       \
}                                                                           \
FOR_EACH(bdbByteGetter, __VA_ARGS__)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define bdbShortReg(name) name = object->regShort();
#define bdbShortGetter(name) short& name(bdb::ObjectInstance* instance) {      \
    return instance->shorts[variables::name];                                  \
}
#define bdbShorts(...) namespace variables { FOR_EACH(bdbVar, __VA_ARGS__) } \
void regShorts() {                                                           \
    using namespace variables;                                               \
    FOR_EACH(bdbShortReg, __VA_ARGS__)                                       \
}                                                                            \
FOR_EACH(bdbShortGetter, __VA_ARGS__)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef uint8_t byte;
typedef char signed_byte;

namespace bdb {


    const byte version = 1;
    const byte ZIP = 0x01;
    const byte REF_32_BIT = 0x02;


    const byte BYTE = 0;
    const byte SHORT = 1;
    const byte INT = 2;
    const byte FLOAT = 3;
    const byte DOUBLE = 4;
    const byte LONG = 5;
    const byte ARRAY = 6;
    const byte GENERALIZING_MAP = 7;
    const byte TYPED_MAP = 8;
    const byte OBJECT = 9;
    const byte LAST_BASE_TYPE = OBJECT;

    extern unsigned int poolSize;
    extern unsigned short nullref;


    void update();
}

