#pragma once
#include<vector>
#include "../bdb.h"

namespace bdb {
    class ArrayBuffer{
	  public:
		std::vector<std::vector<signed_byte> *> byteArrays;
		std::vector<std::vector<short> *> shortArrays;
		std::vector<std::vector<int> *> intArrays;
		std::vector<std::vector<float> *> floatArrays;
		std::vector<std::vector<double> *> doubleArrays;
		std::vector<std::vector<long> *> longArrays;
        std::vector<std::vector<byte> *> objectArrays;
    };
}


