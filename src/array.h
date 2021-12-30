#pragma once

#define bdbAllocArray(type, size) __bdbAllocArray(size*sizeof(type))
#define bdbLength(type, array) array->size/sizeof(type)

typedef struct
{
    char *values;
    int size;
} Array;

char* bdbGetChar(Array *array, int index);
short* bdbGetShort(Array *array, int index);
int* bdbGetInt(Array *array, int index);
float* bdbGetFloat(Array *array, int index);
double* bdbGetDouble(Array *array, int index);
long* bdbGetLong(Array *array, int index);

void bdbDeleteArray(Array *Array);
Array* __bdbAllocArray(int size);

