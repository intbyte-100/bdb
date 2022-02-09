#include "object_context.h"

struct BdbObjectContext bdbCreateObjectContext()
{
    struct BdbObjectContext context;
    context.dataSize = 0;
    context.objectReferenceCount = 0;
    return context;
}

