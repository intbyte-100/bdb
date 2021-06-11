#pragma once


#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include "../bdb.h"
#include "ObjectInstance.h"
#include "Serializable.h"

namespace bdb {
    class GeneralizingMap: public Serializable{
    private:
        std::map<std::string, std::tuple<byte, unsigned short>> map;
        std::vector<unsigned long> element_64_bit;
        std::vector<unsigned int> element_32_bit;
        std::vector<unsigned short> element_16_bit;
        std::vector<byte> element_8_bit;
        std::vector<ObjectInstance *> instances;
    public:
        bool hash = false;

        byte getType() override;
        void readBytes(std::vector<byte> &vector) override;
        void toBytes(std::vector<byte> &vector) override;
        template<typename T>
        void put(const std::string& key, T value) {
            byte size = sizeof(T);
            if (size == 1) {
                element_8_bit.push_back(*reinterpret_cast<byte *>(&value));
                map[key] = std::make_tuple(size, element_8_bit.size() - 1);
            } else if (size == 2) {
                element_16_bit.push_back(*reinterpret_cast<unsigned short*>(&value));
                map[key] = std::make_tuple(size, element_16_bit.size() - 1);
            } else if (size == 4) {
                element_32_bit.push_back(*reinterpret_cast<unsigned int*>(&value));
                map[key] = std::make_tuple(size, element_32_bit.size()-1);
            } else if (size == 8) {
                element_64_bit.push_back(*reinterpret_cast<unsigned long*>(&value));
                map[key] = std::make_tuple(size, element_64_bit.size()-1);
            } else
                throw std::invalid_argument("value");
        }


        template<typename T>
        T get(const std::string& key){
            auto tuple = map[key];
            byte size = std::get<0>(tuple);
            if(size == 1) return *reinterpret_cast<T*>(&element_8_bit[std::get<1>(tuple)]);
            if(size == 2) return *reinterpret_cast<T*>(&element_16_bit[std::get<1>(tuple)]);
            if(size == 4) return *reinterpret_cast<T*>(&element_32_bit[std::get<1>(tuple)]);
            if(size == 8) return *reinterpret_cast<T*>(&element_64_bit[std::get<1>(tuple)]);
        }

        void clear();
    };
}



