#include "../data_struct/ObjectDeclaration.h"
#include "../data_struct/ObjectInstance.h"
#include <cstring>
#include <iostream>
#include <vector>

#pragma once

namespace bdb {

    extern std::vector<ObjectInstance *> instances;
    extern std::vector<ObjectDeclaration *> declarations;

    std::shared_ptr<ObjectInstance> getInstance();

    template <typename T>
    byte getTypeCode() {
        if (std::is_same<byte, T>())
            return BYTE;
        if (std::is_same<short, T>())
            return SHORT;
        if (std::is_same<int, T>())
            return INT;
        if (std::is_same<float, T>())
            return FLOAT;
        if (std::is_same<double, T>())
            return DOUBLE;
        if (std::is_same<long, T>())
            return LONG;
    }

    namespace buffer {

        template <typename T>
        void put(T t, std::vector<byte> *byteVector) {
            byte *bytePointer = reinterpret_cast<byte *>(&t);
            for (int i = 0; i < sizeof(T); i++)
                byteVector->push_back(bytePointer[i]);
        }

        template <typename T>
        void put(std::vector<T> *vector, std::vector<byte> *byteVector) {
            auto bytes = std::vector<byte>();
            for (auto i : *vector) {
                put(i, &bytes);
                for (auto byte : bytes)
                    byteVector->push_back(byte);
                bytes.clear();
            }
        }

        template <typename T>
        T get(std::vector<byte> *byteVector, unsigned int &index) {
            byte bytes[sizeof(T)];
            T value;
            for (int i = 0; i < sizeof(T); i++)
                bytes[i] = byteVector->at(index++);
            std::memcpy(&value, bytes, sizeof(T));
            return value;
        }

        template <typename T>
        std::vector<T> get(unsigned int size, std::vector<byte> *byteVector, unsigned int &index) {
            std::vector<T> value;
            while (value.size() < size) {
                value.push_back(get<T>(byteVector, index));
            }
            return value;
        }

        template <typename T>
        inline void merge(std::vector<T> *first, const std::vector<T> *second) {
            first->insert(first->end(), second->begin(), second->end());
        }
    }
}
