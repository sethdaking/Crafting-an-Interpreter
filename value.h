#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

// Dynamic Array to store Values
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeArray(ValueArray* array);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif