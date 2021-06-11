#pragma once

#include <vector>
#include "../bdb.h"



namespace bdb {
    class ObjectInstance {
    public:
        unsigned int reference = 0;
        byte parent;
        std::vector<signed_byte> bytes;
        std::vector<short> shorts;
        std::vector<int> integers;
        std::vector<float> floats;
        std::vector<double> doubles;
        std::vector<long> longs;
        std::vector<ObjectInstance*> instances;
    public:
        void free();
    };

}


