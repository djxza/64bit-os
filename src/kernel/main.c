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



// Multiboot2 framebuffer tag structure
typedef struct {
    uint32_t framebuffer_addr_low;  // Low 32 bits of framebuffer address
    uint32_t framebuffer_addr_high; // High 32 bits (not used for 32-bit addresses)
    uint32_t framebuffer_pitch;     // Bytes per scanline
    uint32_t framebuffer_width;     // Screen width in pixels
    uint32_t framebuffer_height;    // Screen height in pixels
    uint8_t framebuffer_bpp;        // Bits per pixel
    uint8_t framebuffer_type;       // Framebuffer type (1 for RGB)
    uint8_t reserved[2];
} __attribute__((packed)) framebuffer_info_t;

// Multiboot2 tag structure
typedef struct {
    uint32_t type; // Tag type
    uint32_t size; // Size of the tag, including header
} __attribute__((packed)) multiboot_tag_t;

// Multiboot2 header structure
typedef struct {
    uint32_t total_size; // Total size of multiboot info
    uint32_t reserved;   // Reserved (must be zero)
} __attribute__((packed)) multiboot_info_t;

/*void kernel_main(uint64_t multiboot_info_addr) {
    multiboot_info_t* mbi = (multiboot_info_t*)multiboot_info_addr;

    // Start parsing tags
    multiboot_tag_t* tag = (multiboot_tag_t*)((uintptr_t)mbi + 8); // Skip header (total_size + reserved)

    framebuffer_info_t* framebuffer = NULL;

    // Iterate through tags
    while (tag->type != 0) { // End tag has type 0
        if (tag->type == 8) { // Framebuffer tag
            framebuffer = (framebuffer_info_t*)tag;
            break;
        }
        tag = (multiboot_tag_t*)((uintptr_t)tag + ((tag->size + 7) & ~7)); // Align to next tag
    }

    // Check if framebuffer info was found
    if (framebuffer) {
        // Retrieve framebuffer details
        uint32_t framebuffer_addr = framebuffer->framebuffer_addr_low;
        uint32_t width = framebuffer->framebuffer_width;
        uint32_t height = framebuffer->framebuffer_height;
        uint32_t pitch = framebuffer->framebuffer_pitch;
        uint8_t bpp = framebuffer->framebuffer_bpp;

        // Fill the screen with a simple color gradient (red, green, blue)
        uint32_t* fb = (uint32_t*)framebuffer_addr;
        for (uint32_t y = 0; y < height; y++) {
            for (uint32_t x = 0; x < width; x++) {
                uint32_t color = (x * 255 / width) << 16 | (y * 255 / height) << 8; // RGB gradient
                fb[(y * pitch / 4) + x] = color;
            }
        }
    } else {
        // No framebuffer found; halt the CPU
        while (1) {
            __asm__("hlt");
        }
    }

    // Halt the CPU after rendering
    while (1) {
        __asm__("hlt");
    }
}
*/
/**
void kernel_main(uint64_t multiboot_info_addr) {
    print_clear();
    print_char(4);
    typedef struct {
        uint32_t type;
        uint32_t size;
    } multiboot_tag_t;

    typedef struct {
        uint32_t total_size;
        uint32_t reserved;
    } multiboot_info_t;

    multiboot_info_t* mbi = (multiboot_info_t*)multiboot_info_addr;

    // Start parsing tags
    multiboot_tag_t* tag = (multiboot_tag_t*)((uintptr_t)mbi + 8);

    while (tag->type != 0) {
        // Print the tag type for debugging
        // (Replace with your own output mechanism, e.g., framebuffer, serial port)
        //print_str("Tag Type: ", tag->type);  

        switch (tag->type) {
            case 1:  // Command line tag
                // Handle command line tag
                break;
            case 8:  // Framebuffer tag
                // Handle framebuffer tag
                break;
            default:
                // Unsupported tag
                break;
        }

        // Move to the next tag
        tag = (multiboot_tag_t*)((uintptr_t)tag + ((tag->size + 7) & ~7));
    }

    while (1) {
        __asm__("hlt");
    }
}*/

void kernel_main() {
    *((char*)0xb8000) = 'K';
    while (1) { __asm__("hlt"); }
}