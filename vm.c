#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM(){
    resetStack();
}

void freeVM(){

}

// push a value onto the stack
void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

// Pos a value from the stack
Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run () {
    #define READ_BYTE() (*vm.ip++) // Instruction pointer always points to the next instruction
    #define READ_CONSTANT() (vm.chunk -> constants.values[READ_BYTE()])
    #define BINARY_OP(op) \
    do { \
        
            double b = pop(); \
            double a = pop();\
            push(a op b); \

        } while (false);
    for(;;) {
#ifndef DEBUG_TRACE_EXECUTION
        printf("               ");
        for (Value* slot = vm.stack; slot < vm.stackTop; slot++){
            printf("[ ");
            print Value(*slot);
            printf(" ]");
        }
        printf("\n");
        disassemebleInstruction(vm.chunk, (int) (vm.ip - vm.chunk-> code));
        #endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_NEGATE: {
                push(-pop());
                break;
            }
            case OP_ADD: {
                BINARY_OP(+);
                break;
            }
            case OP_SUBTRACT: {
                BINARY_OP(-);
                break;
            }
            case OP_MULTIPLY: {
                BINARY_OP(*);
                break;
            }
            case OP_DIVIDE: {
                BINARY_OP(/);
                break;
            }
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
            
        }
    }
#undef READ_BTYE
#undef READ_CONSTANT
#undef BINARY_OP
} // End of run()

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk -> code; // We don't use local variables because another process may use it
    return run();
}