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


        src/bdb/data_struct/Serializable.h

        src/bdb/util/ObjectCache.cpp
        src/bdb/util/ObjectCache.h
        src/bdb/util/ObjectCache.cpp
        src/bdb/util/macros_foreach.h
        src/bdb/util/ArrayBuffer.h
        src/bdb/util/ArrayBuffer.cpp
)
