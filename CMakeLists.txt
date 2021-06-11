cmake_minimum_required(VERSION 3.19)


set(CMAKE_CXX_STANDARD 14)
project(bdb7)


add_executable(bdb7
        main.cpp
        src/bdb/DataBuffer.cpp
        src/bdb/DataBuffer.h
        src/bdb/bdb.h
        src/bdb/data_struct/ObjectInstance.cpp
        src/bdb/data_struct/ObjectInstance.h
        src/bdb/bdb.cpp
        src/bdb/util/utils.cpp
        src/bdb/util/utils.h
        src/bdb/data_struct/ObjectDeclaration.cpp
        src/bdb/data_struct/ObjectDeclaration.h
        src/bdb/data_struct/GeneralizingMap.cpp
        src/bdb/data_struct/GeneralizingMap.h
        src/bdb/data_struct/TypedMap.cpp
        src/bdb/data_struct/TypedMap.h
        src/bdb/data_struct/Serializable.h
        src/bdb/data_struct/Map.cpp
        src/bdb/data_struct/Map.h
        src/bdb/util/ObjectPool.cpp
        src/bdb/util/ObjectPool.h
        src/bdb/util/ObjectPool.cpp)