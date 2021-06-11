#pragma once

#include <map>
#include <string>

namespace bdb {
    template<typename T>
    class Map {
    private:
        std::map<std::string, T> map;
    public:
        const bool fixElementSize;
        Map(bool fixElementSize);
        T& operator[](const std::string &key){
            return map[key];
        }
        bool contains(const std::string &key);

    };
}

template<typename T>
bool bdb::Map<T>::contains(const std::string &key) {
    return map.count(key);
}

template<typename T>
bdb::Map<T>::Map(bool fixElementSize) {
    this->fixElementSize = fixElementSize;
}



