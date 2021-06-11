#pragma once

#include <vector>
#include <stdexcept>
#include "../bdb.h"

class Serializable{
public:
    virtual void toBytes(std::vector<byte> &vector){throw std::runtime_error("Serializable class is abstract!");};
    virtual void readBytes(std::vector<byte> &vector){throw std::runtime_error("Serializable class is abstract!");};
    virtual byte getType(){throw std::runtime_error("Serializable class is abstract!");}
};



