#include "stdio.h"
#include "array.h"

int main() {
    Array* array = bdbAllocArray(int, 200);
    bdbDeleteArray(array);
}
