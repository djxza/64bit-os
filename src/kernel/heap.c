#include "heap.h"

// The heap memory region

// for now we leave this as null
static uint8_t* heap = NULL;

static bool init = 0;

// Points to the first free block
static block_meta_t* free_list = NULL; 

void init_heap(u32 size) {
    heap = (block_meta_t*) alloca(size);
    
    free_list = (block_meta_t*)heap;
    free_list->size = HEAP_SIZE - sizeof(block_meta_t);
    free_list->is_free = 1;
    free_list->next = NULL;
   
    init = 1;
}

block_meta_t *find_free_block(size_t size)  {
    block_meta_t* current = free_list;
    
    while (current) {
        if (current->is_free && current->size >= size) {
            return current;
        }

        current = current->next;
    }

    return NULL; // No suitable block found
}

void split_block(block_meta_t *block, size_t size) {
    if (block->size >= size + sizeof(block_meta_t) + ALIGNMENT) {
        block_meta_t* new_block = (block_meta_t*)
            ((uint8_t*)block + sizeof(block_meta_t) + size);

        new_block->size = block->size - size - sizeof(block_meta_t);
        new_block->is_free = 1;
        new_block->next = block->next;

        block->size = size;
        block->next = new_block;
    }
}

void* malloc(size_t size) {
    if(!init) {
       print_err("Heap not initialized");
    }

    size = ALIGN(size); // Ensure alignment
    block_meta_t* block = find_free_block(size);

    if (!block) {
       print_err("Out of memory");
        return NULL; // Out of memory
    }

    block->is_free = 0;
    split_block(block, size);
    return (void*)((uint8_t*)block + sizeof(block_meta_t)); // Return the usable memory
}

void free(void* ptr) {
    if (!ptr) {
        return;
    }

    block_meta_t* block = (block_meta_t*)
        ((uint8_t*)ptr - sizeof(block_meta_t));
    block->is_free = 1;

    // Coalesce adjacent free blocks
    block_meta_t* current = free_list;
    while (current) {
        if (current->is_free && current->next && current->next->is_free) {
            current->size += sizeof(block_meta_t) + current->next->size;
            current->next = current->next->next;
        }
        current = current->next;
    }
}

void* realloc(void* ptr, size_t size) {
    if (!ptr) {
        return malloc(size); // Equivalent to malloc if ptr is NULL
    }

    block_meta_t* block = (block_meta_t*)((uint8_t*)ptr - sizeof(block_meta_t));
    if (block->size >= size) {
        return ptr; // Current block is large enough
    }

    void* new_ptr = malloc(size);
    if (new_ptr) {
        // Copy old data to the new block
        for (size_t i = 0; i < block->size; i++) {
            ((uint8_t*)new_ptr)[i] = ((uint8_t*)ptr)[i];
        }

        free(ptr);
    }
    
    return new_ptr;
}