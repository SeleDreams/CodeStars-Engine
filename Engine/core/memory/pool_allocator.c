#include <stdlib.h>
#include "pool_allocator.h"
MemoryPool csMemPoolAllocatorGlobal;
size_t csMemPoolAllocatorAllocatedData;

void initMemoryPool(MemoryPool* pool) {
    pool->freeList = (MemoryBlock*)pool->pool;
    pool->freeList->next = NULL;
    pool->freeList->size = POOL_SIZE - sizeof(MemoryBlock);
    csMemPoolAllocatorAllocatedData = 0;
}

void* pool_malloc(MemoryPool* pool, size_t size) {
    size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);  // Align size
    MemoryBlock* prev = NULL;
    MemoryBlock* block = pool->freeList;

    while (block) {
        // Align the block address
        uintptr_t blockAddr = (uintptr_t)block;
        uintptr_t alignedAddr = (blockAddr + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
        size_t padding = alignedAddr - blockAddr;

        if (block->size >= size + padding) {
            if (block->size >= size + padding + sizeof(MemoryBlock) + ALIGNMENT) {
                MemoryBlock* newBlock = (MemoryBlock*)((char*)block + sizeof(MemoryBlock) + size + padding);
                newBlock->size = block->size - size - padding - sizeof(MemoryBlock);
                newBlock->next = block->next;
                block->next = newBlock;
                block->size = size + padding;
            }
            if (prev) {
                prev->next = block->next;
            } else {
                pool->freeList = block->next;
            }
            return (char*)alignedAddr + sizeof(MemoryBlock);
        }
        prev = block;
        block = block->next;
    }
    return NULL;  // Pool is exhausted
}


void pool_free(MemoryPool* pool, void* ptr) {
    MemoryBlock* block = (MemoryBlock*)((char*)ptr - sizeof(MemoryBlock));
    block->next = pool->freeList;
    pool->freeList = block;
}