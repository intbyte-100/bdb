#pragma once

#include "../data_struct/ObjectInstance.h"

#include "ArrayBuffer.h"

namespace bdb {
    class DataBuffer;
    class ObjectCache {
        friend class DataBuffer;
    private:
        bool usedBefore = false;
        unsigned short lastReference = 0;
        unsigned short size = 0;
        byte declarationID;
        std::vector<std::shared_ptr<ObjectInstance>> objects;
        std::vector<byte> pointerArrayCache;
        std::vector<unsigned short> instances;
        std::vector<byte> parentInstances;
        std::vector<signed_byte> bytes;
        std::vector<short> shorts;
        std::vector<int> integers;
        std::vector<float> floats;
        std::vector<double> doubles;
        std::vector<long> longs;

        template <typename T>
        void serializeArray(byte type, unsigned short &arrayCount, std::vector<byte> *arrayCache,
                            std::vector<std::vector<T> *> *arrays);
        void serializeObjectArray(DataBuffer *buffer, std::vector<ObjectCache *> *cachePool, unsigned short &arrayCount,
                                  std::vector<byte> *arrayCache,
                                  std::vector<std::vector<std::shared_ptr<ObjectInstance>> *> *arrays);

        public:
        void put(const std::shared_ptr<ObjectInstance>& objectInstance, DataBuffer* buffer, std::vector<ObjectCache*>* objectPools);
        void structureCacheToObjects();
        void clear();
        void flush(ObjectCache *pool, const ArrayBuffer &arrayBuffer);
        ~ObjectCache();
    };
}
