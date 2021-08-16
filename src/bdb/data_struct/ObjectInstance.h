#pragma once

#include <vector>
#include <memory>
#include "../bdb.h"


namespace bdb {
    class ObjectInstance {
    public:
        unsigned int reference = 0;
        byte parentId;
        std::vector<signed_byte> bytes;
        std::vector<short> shorts;
        std::vector<int> integers;
        std::vector<float> floats;
        std::vector<double> doubles;
        std::vector<long> longs;
        std::vector<std::shared_ptr<ObjectInstance>> objects;

		std::vector<std::vector<signed_byte> *> *byteArrays;
		std::vector<std::vector<short> *> *shortArrays;
        std::vector<std::vector<int> *> *intArrays;
        std::vector<std::vector<float> *> *floatArrays;
        std::vector<std::vector<double> *> *doubleArrays;
        std::vector<std::vector<long> *> *longArrays;
        std::vector<std::vector<std::shared_ptr<ObjectInstance>> *> *objectArrays;

        ~ObjectInstance();
    };

}


