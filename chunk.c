#include <stdlib.h>

#include "chunk.h"
#include "memory.h"


// The chunk structure is used to hold the bytecode instructions
// and their metadata, such as the count of instructions and their capacity.
// This starts off with no instructions and no capacity.
void initChunk(Chunk* chunk){
    chunk -> count =0;
    chunk -> capacity =0;
    chunk -> code = NULL;
}

// We deallocate all of the memory and then call initChunk() to zero out the
// fields leaving the chunk in a well-defined empty state
void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk -> code, chunk -> capacity);
    initChunk(chunk);
}

// This function writes a byte to the chunk's code array.
// The first thing we need to do is see if the current array already has capacity for
// the new byte. If it doesn’t, then we first need to grow the array to make room.
void writeChunk(Chunk* chunk, uint8_t byte) {
    if (chunk -> capacity < chunk -> count + 1) {
        int oldCapacity = chunk -> capacity;
        chunk -> capacity = GROW_CAPACITY(oldCapacity);
        chunk -> code = GROW_ARRAY(uint8_t, chunk -> code, oldCapacity, chunk -> capacity);
    }

    chunk -> code[chunk->count] = byte;
    chunk-> count++;

}
