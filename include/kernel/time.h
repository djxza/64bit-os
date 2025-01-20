#include "types.h"
#include "io.h"

#define PIT_CHANNEL_0 0x40
#define PIT_COMMAND   0x43
#define PIT_FREQUENCY 1193182

// Timer interrupt handler
void timer_handler();

// Initialize the timer
void init_timer(u32 frequency);

// Sleep function
void _pit_sleep(u32 milliseconds);

u64 get_time();