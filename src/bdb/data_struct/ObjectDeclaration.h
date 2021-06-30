#pragma once


#include "../bdb.h"
#include "ObjectInstance.h"
#include "../util/ObjectPool.h"

namespace bdb {
    class ObjectDeclaration {
        friend class ObjectPool;
    private:

        std::vector<bool> nullptrByDefault;
    public:
        unsigned short size = 0;
        byte manifestSize = 0;
        std::vector<ObjectDeclaration*> references;
        byte byteCount, shortCount, intCount, floatCount, doubleCount, longCount;
        byte reference;
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

        byte regObject(ObjectDeclaration *objectDeclaration, bool nullByDefault);
        void reg();
        std::shared_ptr<ObjectInstance> newInstance(bool feelInstancesWithNulls = false) const;

    };
}



