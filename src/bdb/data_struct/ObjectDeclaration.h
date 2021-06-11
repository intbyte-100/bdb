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
        byte regObject(ObjectDeclaration *objectDeclaration, bool nullByDefault);
        void reg();
        ObjectInstance* newInstance() const;

    };
}



