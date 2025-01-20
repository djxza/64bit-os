#include "gfx/display.h"

u64 last_frame_time;

// Default to 60 FPS
u16 frame_rate = 60;
f64 seconds_per_frame = 1.0 / 60;

void update_seconds_per_frame() {
    seconds_per_frame = 1.0 / (f64)frame_rate;
}

void frame_start() {
    last_frame_time = get_time();
}

void frame_end() {
    f64 elapsed_time = get_time() - last_frame_time;

    if (elapsed_time >= seconds_per_frame) 
        return;

    // Sleep for the remaining time
    _pit_sleep(seconds_per_frame - elapsed_time);
}

void set_frame_rate(u16 new_frame_rate) {
    if (new_frame_rate == 0) {
        print_err("Frame rate cannot be zero!\n");
        return;
    }
    frame_rate = new_frame_rate;
    update_seconds_per_frame();
}
