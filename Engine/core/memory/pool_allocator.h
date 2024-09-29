#ifndef CODESTARS_CORE_MEMORY_POOL_ALLOCATOR_H
#define CODESTARS_CORE_MEMORY_POOL_ALLOCATOR_H
#include <stdlib.h>
#include <stdint.h>
#include "memory_chunk.h"

typedef struct csMemPoolAllocator {
    size_t chunksPerBlock;
    csMemoryChunk *memoryChunk;
} csMemPoolAllocator;

#define POOL_SIZE 32  // Adjust this size based on your needs
#define ALIGNMENT 8     // Adjust alignment as needed
typedef struct MemoryBlock {
    struct MemoryBlock* next;
    size_t size;
} MemoryBlock;

typedef struct MemoryPool {
    MemoryBlock* freeList;
    char pool[POOL_SIZE];
    size_t allocated_data;
} MemoryPool;

extern MemoryPool csMemPoolAllocatorGlobal;

void initMemoryPool(MemoryPool* pool);
void* pool_malloc(MemoryPool* pool, size_t size);
void pool_free(MemoryPool* pool, void* ptr);

static inline void *csMalloc(size_t size) {
    return malloc(size);
   //csMemPoolAllocatorGlobal.allocated_data += size; return pool_malloc(&csMemPoolAllocatorGlobal,size);
}
static inline void csFree(void *ptr,size_t size) {
    (void)size;
    free(ptr);
   // csMemPoolAllocatorGlobal.allocated_data -= size; pool_free(&csMemPoolAllocatorGlobal,ptr);
}
static inline unsigned int csAllocatedData(void) {return csMemPoolAllocatorGlobal.allocated_data;}
#endif
