#include "pool_allocator.h"
#include <stdio.h>

#define reinterpret_cast(TO, VAR) \
({                                \
    union                         \
    {                             \
        __typeof__((VAR)) source; \
        TO dest;                  \
    } u = { .source = (VAR) };    \
    (TO)(u.dest);                 \
})

csMemPoolAllocator csMemPoolAllocatorGlobal;

void csMemPoolAllocatorInit(csMemPoolAllocator *allocator, size_t chunksPerBlock) {
    allocator->chunksPerBlock = chunksPerBlock;
    allocator->memoryChunk = NULL;
}

void *csMemPoolAllocatorAlloc(csMemPoolAllocator *allocator, size_t size) {
    if(allocator->memoryChunk == NULL)
    {
        allocator->memoryChunk = csMemPoolAllocatorAllocPool(allocator,size);
    }

    csMemoryChunk *freeChunk = allocator->memoryChunk;
    allocator->memoryChunk = allocator->memoryChunk->next;
    return freeChunk;
}

void csMemPoolAllocatorDealloc(csMemPoolAllocator *allocator, void *ptr, size_t size){
    reinterpret_cast(csMemoryChunk*,ptr)->next = allocator->memoryChunk;
    allocator->memoryChunk = reinterpret_cast(csMemoryChunk*,ptr);
}

csMemoryChunk *csMemPoolAllocatorAllocPool(csMemPoolAllocator *allocator, size_t size){
    //printf("Allocating block (%d chunks) resulting in %d bytes allocated:\n\n",allocator->chunksPerBlock,allocator->chunksPerBlock * size);
    size_t blockSize = allocator->chunksPerBlock * size;
    csMemoryChunk *blockBegin = reinterpret_cast(csMemoryChunk*,malloc(blockSize));
    csMemoryChunk *chunk = blockBegin;
    for (int i = 0; i < allocator->chunksPerBlock - 1;++i)
    {
        chunk->next = reinterpret_cast(csMemoryChunk*,reinterpret_cast(char*,chunk) + size);
        chunk = chunk->next;
    } 
    chunk->next = NULL;
    return blockBegin;
}