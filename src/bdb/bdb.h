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
#define bdbByteGetter(name) inline signed_byte& name(const std::shared_ptr<bdb::ObjectInstance> &instance) {\
    return instance->bytes[variables::name];                                        \
}
#define bdbBytes(...) namespace variables { FOR_EACH(bdbVar, __VA_ARGS__) }         \
void regBytes() {                                                                   \
    using namespace variables;                                                      \
    FOR_EACH(bdbByteReg, __VA_ARGS__)                                               \
}                                                                                   \
FOR_EACH(bdbByteGetter, __VA_ARGS__)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define bdbShortReg(name) byte name = object->regShort();
#define bdbShortGetter(name) inline short& name(const std::shared_ptr<bdb::ObjectInstance> &instance) {    \
    return instance->shorts[variables::name];                                       \
}
#define bdbShorts(...)                                                                                                 \
    namespace variables {                                                                                              \
        FOR_EACH(bdbShortReg, __VA_ARGS__)                                                                             \
    }                                                                                                                  \
                                                                                                                       \
    FOR_EACH(bdbShortGetter, __VA_ARGS__)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define bdbIntReg(name) byte name = object->regInt();
#define bdbIntGetter(name) inline int& name(const std::shared_ptr<bdb::ObjectInstance> &instance) {        \
    return instance->integers[variables::name];                                     \
}
#define bdbInts(...)                                                                                                   \
    namespace variables {                                                                                              \
        FOR_EACH(bdbIntReg, __VA_ARGS__)                                                                               \
    }                                                                                                                  \
                                                                                                                       \
    FOR_EACH(bdbIntGetter, __VA_ARGS__)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define bdbFloatReg(name) name = object->regFloat();
#define bdbFloatGetter(name) inline float& name(const std::shared_ptr<bdb::ObjectInstance> &instance) {    \
    return instance->floats[variables::name];                                       \
}
#define bdbFloats(...) namespace variables { FOR_EACH(bdbVar, __VA_ARGS__) }        \
void regFloats() {                                                                  \
    using namespace variables;                                                      \
    FOR_EACH(bdbFloatReg, __VA_ARGS__)                                              \
}                                                                                   \
FOR_EACH(bdbFloatGetter, __VA_ARGS__)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#define bdbDoubleReg(name) name = object->regDouble();
#define bdbDoubleGetter(name) inline double& name(const std::shared_ptr<bdb::ObjectInstance> &instance) {  \
    return instance->doubles[variables::name];                                      \
}
#define bdbDoubles(...)                                                                                      \
	namespace variables {                                                                                    \
	FOR_EACH(bdbVar, __VA_ARGS__)                                                                            \
	}                                                                                                        \
	void regDoubles() {                                                                                      \
		using namespace variables;                                                                           \
		FOR_EACH(bdbDoubleReg, __VA_ARGS__)                                                                  \
	}                                                                                                        \
	FOR_EACH(bdbDoubleGetter, __VA_ARGS__)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#define bdbLongReg(name) name = object->regLong();
#define bdbLongGetter(name) inline long& name(const std::shared_ptr<bdb::ObjectInstance> &instance) {  \
    return instance->longs[variables::name];                                    \
}
#define bdbLongs(...) namespace variables { FOR_EACH(bdbVar, __VA_ARGS__) }     \
void regLongs() {                                                              \
    using namespace variables;                                                  \
    FOR_EACH(bdbLongReg, __VA_ARGS__)                                           \
}                                                                               \
FOR_EACH(bdbLongGetter, __VA_ARGS__)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define bdbObjectGetter(name)                                                                                          \
    inline std::shared_ptr<bdb::ObjectInstance> &name(const std::shared_ptr<bdb::ObjectInstance> &instance) {          \
        return instance->objects[variables::name];                                                                     \
    }
#define bdbObject(name, declaration, feelWithNulls)                                                                    \
    namespace variables {                                                                                              \
        byte name = object->regObject(declaration, feelWithNulls);                                                     \
    }                                                                                                                  \
    bdbObjectGetter(name)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef uint8_t byte;
typedef char signed_byte;

namespace bdb {

    const byte version = 1;

    // flags
    const byte COMPRESSING = 0x01;
    const byte THIRTY_TWO_BIT_POINTERS = 0x02;

    const byte BYTE = 0;
    const byte SHORT = 1;
    const byte INT = 2;
    const byte FLOAT = 3;
    const byte DOUBLE = 4;
    const byte LONG = 5;
    const byte GENERALIZING_MAP = 6;
    const byte TYPED_MAP = 7;
    const byte OBJECT = 8;
    const byte POINTER = 9;

    const byte BYTE_ARRAY = 0;
    const byte SHORT_ARRAY = 1;
    const byte INT_ARRAY = 2;
    const byte FLOAT_ARRAY = 3;
    const byte DOUBLE_ARRAY = 4;
    const byte LONG_ARRAY = 5;
    const byte OBJECT_ARRAY = 6;

    extern unsigned short null_ref;


    void update();
}

