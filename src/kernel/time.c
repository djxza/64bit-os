#include "../../include/kernel/time.h"

// Constants
#define PIT_FREQUENCY 1193182 // Typical PIT clock frequency in Hz
#define PIT_COMMAND 0x43
#define PIT_CHANNEL_0 0x40

// Global variables
static u32 ticks = 0;          // Tick counter
static u32 current_frequency = 100; // Default frequency in Hz

// Timer interrupt handler (increments ticks)
void timer_handler() {
    ticks++;
}

// Initialize the PIT timer with a given frequency
void init_timer(u32 frequency) {
    if (frequency == 0) {
        print_err("Frequency cannot be zero!\n");
        return;
    }
    current_frequency = frequency;
    u32 divisor = PIT_FREQUENCY / frequency;

    // Send command byte and divisor to PIT
    outb(PIT_COMMAND, 0x36);           // Command byte for PIT mode 2 (rate generator)
    outb(PIT_CHANNEL_0, divisor & 0xFF); // Send low byte
    outb(PIT_CHANNEL_0, (divisor >> 8) & 0xFF); // Send high byte
}

// Sleep for a given number of milliseconds
void _pit_sleep(u32 milliseconds) {
    u32 ticks_per_ms = current_frequency / 1000;
    u32 target_ticks = ticks + (milliseconds * ticks_per_ms);
    while (ticks < target_ticks);
}

// Get time elapsed in milliseconds since timer initialization
u64 get_time() {
    return (u64)ticks * (1000 / current_frequency);
}
