#pragma once

#include <cstdint>

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

