#include "list.h"
#include "malloc.h"

void __bdbExtendList(BdbList* list, int elementSize, int elementsCount)
{
    if (list->size >= list->array.size + elementsCount * elementSize) {
        int newSize = list->array.size*1.60;
        __bdbResizeList(list, newSize);
        list->array.size = newSize;
        list->size += elementsCount * elementSize;
    } else {
        list->size += elementsCount * elementSize;
    }
}

void __bdbResizeList(BdbList* list, int newSize)
{
    list->array.values = realloc(list->array.values, newSize);
    list->array.size = newSize;
}

char * __bdbAddElement(BdbList* list, int size)
{
    __bdbExtendList(list, size, 1);
    return &list->array.values[list->array.size - size];
}


BdbList * bdbCreateList()
{
    BdbList *list = malloc(sizeof(BdbList));
    list->array.values = malloc(14);
    list->array.size = 14;
    return list;
}


