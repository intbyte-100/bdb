#pragma once


#include "../bdb.h"
#include "ObjectInstance.h"
#include "../util/ObjectCache.h"

namespace bdb {
    class ObjectDeclaration {
        friend class ObjectCache;

    private:
        std::vector<bool> nullptrByDefault;
    public:
        unsigned short size = 0;
        byte manifestSize = 0;
        std::vector<ObjectDeclaration *> references;
        byte shortCount = 0;
        byte intCount = 0;
        byte floatCount = 0;
        byte doubleCount = 0;
        byte longCount = 0;
        byte byteCount = 0;
        byte floatArrayCount = 0;
        byte doubleArrayCount = 0;
        byte longArrayCount = 0;
        byte objectArrayCount = 0;
        byte intArrayCount = 0;
        byte shortArrayCount = 0;
        byte byteArrayCount = 0;
        byte arrayCount = 0;
        byte id;

        byte regByte();
        byte regShort();
        byte regInt();
        byte regFloat();
        byte regDouble();
        byte regLong();

        byte regByteArray();
        byte regShortArray();
        byte regIntArray();
        byte regFloatArray();
        byte regDoubleArray();
        byte regLongArray();
        byte regObjectArray();

        byte regObject(ObjectDeclaration *objectDeclaration, bool nullByDefault);

        void reg();

        std::shared_ptr<ObjectInstance> newInstance(bool feelInstancesWithNulls = false) const;

    };
}



