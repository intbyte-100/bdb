#pragma once

#include "Serializable.h"
#include "GeneralizingMap.h"
#include "../util/utils.h"
#include <vector>

namespace bdb {
    class TypedMap : public Serializable {

    private:
        std::map<std::string, std::tuple<byte, unsigned short >> map;
        std::vector<signed_byte> bytes;
        std::vector<short> shorts;
        std::vector<int> integers;
        std::vector<float> floats;
        std::vector<double> doubles;
        std::vector<long> longs;
    public:
        void toBytes(std::vector<byte> &vector) override;

        void readBytes(std::vector<byte> &vector) override;

        byte getType() override;

        void put(const std::string& key, signed_byte value);
        void put(const std::string& key, short value);
        void put(const std::string& key, int value);
        void put(const std::string& key, float value);
        void put(const std::string& key, double value);
        void put(const std::string& key, long value);

        signed_byte getByte(const std::string& key);
        short getShort(const std::string& key);
        int getInt(const std::string& key);
        float getFloat(const std::string& key);
        double getDouble(const std::string& key);
        long getLong(const std::string& key);

        bool contains(const std::string &key);

        template<typename T>
        bool containsType(const std::string &key){
            if(contains(key))
                return std::get<0>(map[key]) == getTypeCode<T>();
        }
    };
}



