#ifndef __IO_h__
#define __IO_h__

#include "types.h"
#include "print.h"

// PS/2 Keyboard Controller Ports
#define PS2_DATA_PORT 0x60
#define PS2_STATUS_PORT 0x64
#define MAX_KEYS 128

typedef struct {
    bool key_states[MAX_KEYS]; // 1 if key is pressed, 0 if released
} keyboard_t;

keyboard_t init_keyboard();

// Port I/O functions
u8 inb(uint16_t port);
void outb(uint16_t port, uint8_t value);

/* Read the last scancode */
uint8_t read_scancode();

// Function to check if data is ready to read
int is_key_ready();

// Read a single keypress (blocking)
char read_key();

// Example usage
void read_and_print_key();
void poll_keyboard_events(keyboard_t *keyboard);

void process_key_states(const keyboard_t *keyboard);

#endif /* __IO_h__ */