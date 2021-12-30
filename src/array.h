#pragma once

#define bdbAllocArray(type, size) __bdbAllocArray(size*sizeof(type))
#define bdbArrayLength(type, array) array->size/sizeof(type)
#define bdbArrayElement(type, array, index) ((type*) &array->values[index*sizeof(type)])

typedef struct
{
    char *values;
    int size;
} BdbArray;



void bdbDeleteArray(BdbArray* bdbArray);
BdbArray* __bdbAllocArray(int size);

