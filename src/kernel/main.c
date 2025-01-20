#include "state.h"
#include "types.h"
#include "io.h"
#include "print_buffer.h"
#include "math.h"
#include "multiboot.h"
#include "../../include/kernel/gfx/display.h"
#include "../../include/kernel/time.h"
/*
void kernel_main() {
    print_clear();

    // Initialize system state
    state_t state = init_state();

    // Initialize timer with a frequency of 100 Hz
    init_timer(100);

    // Variables to track frame timing
    u64 last_frame_time = get_time();
    const u16 frame_rate = 60; // Target frame rate
    const u64 time_per_frame = 1000 / frame_rate; // Milliseconds per frame

    while (1) {
        // Time management
        u64 current_time = get_time();
        if (current_time - last_frame_time < time_per_frame) {
            continue; // Skip frame if not enough time has passed
        }
        
        last_frame_time = current_time;

        // Process keyboard events
        poll_keyboard_events(&state.keyboard);

        // Process key states (if needed for display updates)
        process_key_states(&state.keyboard);

        // Clear and redraw the display (or update framebuffer)
        print_clear();
    }
}*/
 // Broj bajtova po redu

// Funkcija za postavljanje piksela
void put_pixel(u32*gfx, u32 x, u32 y, u32 color) {
    if (x >= screen_width || y >= screen_height) {
        return; // Van granica ekrana
    }

    u32 index = y * (pitch / 4) + x; // Pitch / 4 jer je svaki piksel 4 bajta
    gfx[index] = color;
}

// Funkcija za crtanje linije
void draw_line(u32* gfx, int x0, int y0, int x1, int y1, u32 color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; // Greška

    while (1) {
        put_pixel(gfx, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

// Kernel main funkcija
typedef struct {
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
} framebuffer_info_t;

void kernel_main(uint32_t magic, uint32_t addr) {


}