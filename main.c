#include "array.h"
#include "list.h"
#include "stdio.h"
#include "object_context.h"

int main() {
    BdbList *list = bdbCreateList();
    bdbAddElement(int, list, 31);
    bdbAddElement(int, list, 319);
    printf("list element = %i", *bdbListElement(int, list, 1));
    bdbDeleteList(list);
}
