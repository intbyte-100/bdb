#include "stdio.h"
#include "array.h"
#include "list.h"

int main() {
    BdbArray* array = bdbAllocArray(int, 200);
    printf("array element = %i\n", *bdbArrayElement(int, array, 0));
    bdbDeleteArray(array);

    BdbList *list = bdbCreateList();
}
