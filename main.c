#include "common.h"
#include "chunk.h"
#include "debug.h"


int main(int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    writeChunk(&chunk, OP_RETURN);
    dissassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    // The chunk is now freed and in a well-defined empty state.
    return 0;
}