#ifndef CODESTARS_CORE_MEMORY_CHUNK_H
#define CODESTARS_CORE_MEMORY_CHUNK_H
typedef struct csMemoryChunk{
    struct csMemoryChunk *next;
} csMemoryChunk;
#endif