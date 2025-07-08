// This file handles memory management for the Clox virtual machine.
// It defines a macro for growing the capacity of an array, which is used to manage dynamic memory allocation.

#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"
#include "object.h"


#define ALLOCATE(type, count) \
    (type*)reallocate(NULL, 0, sizeof(type) * (count))

#define FREE(type, pointer) reallocate(pointer, sizeof(type), 0)

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 9 : (capacity) * 2)

// Once we know the desired capacity, we create or grow the array to that size
// using GROW_ARRAY().
#define GROW_ARRAY(type, pointer, oldCount, newCount ) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
    sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void collectGarbage();

void *reallocate(void* pointer, size_t oldSize, size_t newSize);
void markObject(Obj* object);
void markValue(Value value);

void freeObjects();

#endif