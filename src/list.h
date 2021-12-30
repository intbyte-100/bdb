#pragma once
#include "array.h"

#define bdbExtendList(list, type, count) __bdbExtendList(list, sizeof(type), count)
#define bdbResizeList(list, type, newSize) __bdbResizeList(list, newSize*sizeof(type))
#define bdbListSize(type, list) list->size / sizeof(type)
#define bdbAddElement(type, list, element) *((type*) __bdbAddElement(list, sizeof(type))) = element;


typedef struct 
{
    BdbArray array;
    int size;

} BdbList;

BdbList* bdbCreateList();
void __bdbResizeList(BdbList* list, int newSize);
void __bdbExtendList(BdbList* list, int elementSize, int elementsCount);
char* __bdbAddElement(BdbList* list, int size);

