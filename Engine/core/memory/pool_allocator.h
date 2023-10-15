#ifndef CODESTARS_CORE_MEMORY_POOL_ALLOCATOR_H
#define CODESTARS_CORE_MEMORY_POOL_ALLOCATOR_H
#include <stdlib.h>
#include "memory_chunk.h"
typedef struct csMemPoolAllocator {
    size_t chunksPerBlock;
    csMemoryChunk *memoryChunk;
} csMemPoolAllocator;

extern csMemPoolAllocator csMemPoolAllocatorGlobal;

extern void csMemPoolAllocatorInit(csMemPoolAllocator *allocator, size_t chunksPerBlock);
extern void *csMemPoolAllocatorAlloc(csMemPoolAllocator *allocator, size_t size);
extern void csMemPoolAllocatorDealloc(csMemPoolAllocator *allocator, void *ptr, size_t size);
extern csMemoryChunk *csMemPoolAllocatorAllocPool(csMemPoolAllocator *allocator, size_t size);

static inline void *csMalloc(size_t size) {return malloc(size);}// csMemPoolAllocatorAlloc(&csMemPoolAllocatorGlobal,size);}
static inline void csFree(void *ptr,size_t size) {free(ptr);}// csMemPoolAllocatorDealloc(&csMemPoolAllocatorGlobal,ptr,size);}
#endif