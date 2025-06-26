#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

// As usual, we start simple. The VM will gradually acquire a whole pile of state it
// needs to keep track of, so we define a struct now to stuff that all in. 
typedef struct {
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;


void initVM();
void freeVM();

// Main entry point for the VM
InterpretResult interpret(const char* source);

// The stack protocol supports two operations:
void push(Value value);
Value pop();

#endif

