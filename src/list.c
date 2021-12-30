#include "list.h"
#include "malloc.h"

void __bdbExtendList(BdbList* list, int elementSize, int elementsCount)
{
    if (!(list->size>= list->array.size+elementsCount*elementSize)){
        int newSize = list->array.size*1.60;
        __bdbResizeList(list, newSize);
        list->array.size = newSize;
        list->size += elementsCount * elementSize;
    } else{
        list->size += elementsCount * elementSize;
    }
}

void __bdbResizeList(BdbList* list, int newSize)
{
    realloc(list->array.values, newSize);
    list->array.size = newSize;
}

char * __bdbAddElement(BdbList* list, int size)
{
    __bdbExtendList(list, size, 1);
    return &list->array.values[list->array.size - size];
}


