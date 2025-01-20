#include "print_buffer.h"

#ifndef _TESTING_VIDEO

// Global variables
char* print_buffer = NULL;
u32 size = 0;
u32 pointer = 0;

void print_buffer_show()
{
    print_str(print_buffer);
}

void print_buffer_add(char *str)
{
    if (!str) return; // Guard against NULL input

    size_t len = strlen(str); // Calculate the length once

    // Resize the buffer
    char* new_buffer = realloc(print_buffer, size + len + 1); // +1 for null terminator
    if (!new_buffer) {
        // Handle memory allocation failure
        return;
    }

    print_buffer = new_buffer;

    // Copy the new string into the buffer
    for (size_t i = 0; i < len; ++i) {
        print_buffer[pointer + i] = str[i];
    }

    pointer += len; // Move pointer to the next position
    size += len;    // Update the total size

    print_buffer[pointer] = '\0'; // Null-terminate the buffer
}

void print_buffer_clear() {
    print_clear();
}

#endif