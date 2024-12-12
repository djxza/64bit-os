#include "lib.h"

size_t strlen(const char *str) {
    const char *s = str;
    while (*s) { // Iterate until the null character is found
        ++s;
    }

    return s - str; // Return the difference (number of characters)
}