// This is an implementation file for disassembly of the program
// The program is a simple interpreter for a simple programming language
// The program is written in C and uses the GNU Debugger (GDB) for disassembly
// The program is compiled using the GNU Compiler Collection (GCC) and linked with the GNU Debugger (GDB)
// The program is run using the GNU Debugger (GDB) and disassembled using the GNU Debugger (GDB)

#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s == \n", name);

    for (int offset =0; offset < chunk -> count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

// This function prints the value of a constant in a human-readable format.
// The function takes three arguments: a pointer to a Chunk object, the offset of
// the constant in the Chunk object, and a pointer to a Chunk object. The function
// returns the offset of the next instruction in the Chunk object.
static int constantInstruction(const char* name, Chunk* chunk,
                            int offset) { 
    uint8_t constant = chunk -> code[offset +1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;  // Move past the instruction and the constant index
}


// To disassemble a chunk, we print a little header (so we can tell which chunk
//we’re looking at) and then crank through the bytecode, disassembling each
//instruction. The way we iterate through the code is a little odd. Instead of

//incrementing offset in the loop, we let disassembleInstruction() do it
//for us. When we call that function, after disassembling the instruction at the 
// given offset, it returns the offset of the next instruction

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d", offset);

    if (offset > 0 && chunk -> lines[offset] == chunk -> lines[offset -1]) {
        printf("    | ");
    } else {
        printf("%4d ", chunk -> lines[offset]);
    }
    uint8_t instruction = chunk -> code[offset];

    switch(instruction) {
        case OP_CONSTANT:
            return constantInstuction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}

// OP_RETURN display function

int simpleInstruction(const char* name, int offset){
    printf("%s\n", name);
    return offset + 1;
}