#ifndef __HEAP_h__
#define __HEAP_h__

#include "print.h"
#include "lib.h"

// Define constants
#define HEAP_SIZE 1024 * 1024 // 1 MB heap
#define ALIGNMENT 8           // Memory alignment (must be power of 2)

// Helper macro to align memory
#define ALIGN(x) (((x) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

// Metadata for each memory block
typedef struct block_meta {
    size_t size;               // Size of the block (excluding metadata)
    bool is_free;               // 1 if the block is free, 0 if allocated
    struct block_meta* next;   // Pointer to the next block
} block_meta_t;

// Initialize the heap (called once)
void init_heap(u32 size);

// Find a suitable block using the first-fit strategy
block_meta_t* find_free_block(size_t size);

// Split a block if it's larger than the requested size
void split_block(block_meta_t* block, size_t size);

// Allocate memory (similar to malloc)
void* malloc(size_t size);

// Free allocated memory (similar to free)
void free(void* ptr);

// Resize allocated memory (similar to realloc)
void* realloc(void* ptr, size_t size);


#endif /* __HEAP_h__ */