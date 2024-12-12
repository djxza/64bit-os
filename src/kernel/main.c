#include "types.h"
#include "io.h"
#include "print_buffer.h"
#include "math.h"

void kernel_main() {
    print_clear();

    keyboard_t keyboard = keyboard_init();

    while (1) {
        // Keep the kernel running
        process_key_states(&keyboard);

        poll_keyboard_events(&keyboard);

        print_clear();
    }
}
