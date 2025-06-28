// oldSize newSize Operation
// 0 Non‑zero Allocate new block.
// Non‑zero 0 Free allocation.
// Non-zero Smaller than oldSize Shrink existing allocation.
// Non‑zero Larger than oldSize Grow existing allocation

#include <stdlib.h>

#include "memory.h"
#include "vm.h"


void* reallocate(void *pointer, size_t oldSize, size_t newSize){
    if (newSize == 0){
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, newSize);
    if (result == NULL) exit(1); // Exit if memory allocation fails
    return result;
}

static void freeObject(Obj* object) {
    switch (object->type) {
        case OBJ_STRING: {
            ObjString* string = (ObjString*)object;
            FREE_ARRAY(char, string->chars, string->length+1);
            FREE(ObjString, object);
            break;
        }
    }
}

void freeObjects() {
    Obj* object = vm.objects;
    while (object != NULL) {
        Obj* next = object->next;
        freeObject(object);
        object=next;
    }
}