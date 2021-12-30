#include "array.h"
#include "malloc.h"


BdbArray *__bdbAllocArray(int size){
    BdbArray *array = malloc(sizeof(BdbArray));
    array->size = size;
    array->values = malloc(size);
    return array;
}

void bdbDeleteArray(BdbArray *array){
    free(array->values);
    free(array);
}
