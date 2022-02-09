#pragma once

#define bdbSetStruct(context, structure, objectsCount) context.dataSize = sizeof(structure); \
                                                       context.bdbCreateObjectContext = objectsCount;

struct BdbObjectContext {
    int dataSize;
    int objectReferenceCount;
};

struct BdbObjectContext bdbCreateObjectContext();

