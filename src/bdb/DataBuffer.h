#pragma once


#include <vector>
#include "bdb.h"
#include "util/utils.h"
#include "util/ObjectPool.h"

namespace bdb {
    class DataBuffer {

    private:
        byte config = 0;
        ObjectPool *pool = nullptr;
        byte poolSize = 0;
    public:
        void updatePool();
        std::vector<byte> write(std::shared_ptr<ObjectInstance> instance);
        std::shared_ptr<ObjectInstance> read(std::vector<byte> &data, byte declarationID);
        void enable(byte attribute);
        void disable(byte attribute);
        bool isEnable(byte attribute);
        ~DataBuffer();
    };

}


