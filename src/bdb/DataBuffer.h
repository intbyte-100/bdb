#pragma once


#include <vector>
#include "bdb.h"
#include "util/utils.h"
#include "util/ObjectCache.h"

namespace bdb {
    class DataBuffer {
        friend ObjectCache;

    private:
        byte config = 0;
        ObjectCache *cache = nullptr;
        byte cacheInstancesCount = 0;

        std::vector<byte> byteArrayCache;
        std::vector<byte> shortArrayCache;
        std::vector<byte> intArrayCache;
        std::vector<byte> floatArrayCache;
        std::vector<byte> doubleArrayCache;
        std::vector<byte> longArrayCache;
        std::vector<byte> objectArrayCache;

        unsigned short byteArrayCount = 0;
        unsigned short shortArrayCount = 0;
        unsigned short intArrayCount = 0;
        unsigned short floatArrayCount = 0;
        unsigned short doubleArrayCount = 0;
        unsigned short longArrayCount = 0;
        unsigned short objectArrayCount = 0;

        bool extraCacheIsEmpty();
		unsigned short extraCacheSize();
		void clear();

    public:
        void updateCache();
        std::vector<byte> serialize(const std::shared_ptr<ObjectInstance>& objectInstance);
        std::shared_ptr<ObjectInstance> deserialize(std::vector<byte> &data, byte declarationID);
        void enable(byte attribute);
        void disable(byte attribute);
        bool isEnable(byte attribute);
        ~DataBuffer();
    };

}


