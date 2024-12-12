#include "../../include/kernel/io.h"
#include "io.h"

/* TODO: add so that theree are multiple language packages  */
static const char scancode_to_text[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', 
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 
    0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


keyboard_t keyboard_init() {
    return (keyboard_t) {
        .key_states = {0}
    };
}

u8 inb(uint16_t port) {
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

/* Read the last scancode */
uint8_t read_scancode() {
    while (!is_key_ready()); // Wait until data is available
    return inb(PS2_DATA_PORT);
}

int is_key_ready() {
    return inb(PS2_STATUS_PORT) & 0x01; // Bit 0 indicates data is available
}

/* reads the last pressed key */
char read_key() {
    while (!is_key_ready()); // Wait until data is available
    uint8_t scancode = inb(PS2_DATA_PORT);

    // Convert scancode to ASCII (basic mapping for demonstration purposes)
    static const char scancode_to_ascii[128] = {
        0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', 
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
        0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 
        0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    return scancode < 128 ? scancode_to_ascii[scancode] : 0;
}

void read_and_print_key() {
    char key = read_key();

    if (key) {
        // Write the character to the framebuffer or console output
        // (This assumes you have a `put_char` function implemented)
        print_char(key); 
    }
}

void poll_keyboard_events(keyboard_t *keyboard) {
    if (!keyboard) {
        print_err("Keyboard not initialized!\n");
        return;
    }

    uint8_t scancode = read_scancode();
    bool is_release = scancode & 0x80;

    scancode &= 0x7F; // Remove the release bit
    if (scancode >= MAX_KEYS) return;

    keyboard->key_states[scancode] = !is_release;
}

void process_key_states(const keyboard_t *keyboard) {
    if (!keyboard) {
        print_err("Keyboard not initialized!\n");
        return;
    }

    // Clear screen or move cursor to the start of the display if needed
    print_clear(); // Optional: Implement clear_screen() to refresh the display

    for (int i = 0; i < MAX_KEYS; ++i) {
        if (keyboard->key_states[i]) {
            char key = scancode_to_text[i]; // Map scancode to ASCII if necessary
            if (key) {
                print_char(key); // Function to print character to the screen
            }
        }
    }
}