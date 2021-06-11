#pragma once

#include "../data_struct/ObjectInstance.h"

namespace bdb {
    class ObjectPool {
        friend class DataBuffer;
    private:
        bool usedBefore = false;
        unsigned short lastReference = 0;
        unsigned short size = 1;
        byte declarationID;
        std::vector<unsigned short> instances;
        std::vector<byte> parentInstances;
        std::vector<signed_byte> bytes;
        std::vector<short> shorts;
        std::vector<int> integers;
        std::vector<float> floats;
        std::vector<double> doubles;
        std::vector<long> longs;
    public:
        void put(ObjectInstance *instance, ObjectPool* pool, std::vector<ObjectPool*>* objectPools);
    };
}


