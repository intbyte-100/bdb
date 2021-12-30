#include "array.h"
#include "malloc.h"

#define implGet(name, type) \
    type* name(Array *array, int index) { return (type*) &array->values[index * sizeof(type)]; }

implGet(bdbGetChar, char);
implGet(bdbGetShort, short);
implGet(bdbGetInt, int);
implGet(bdbGetFloat, float);
implGet(bdbGetDouble, double);
implGet(bdbGetLong, long);


Array *__bdbAllocArray(int size){
    Array *array = malloc(sizeof(Array));
    array->size = size;
    array->values = malloc(size);
    return array;
}

void bdbDeleteArray(Array *array){
    free(array->values);
    free(array);
}