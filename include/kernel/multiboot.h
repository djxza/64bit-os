#ifndef __MULTIBOOT_h__
#define __MULTIBOOT_h__

#include "lib.h"

#define MULTIBOOT2_BOOTLOADER_MAGIC 0xe85250d6
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER 8
#define MULTIBOOT_TAG_TYPE_END 0

// Multiboot2 framebuffer structure
struct multiboot_tag {
    uint32_t type;
    uint32_t size;
};

struct multiboot_tag_framebuffer {
    struct multiboot_tag common;
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    uint8_t framebuffer_type;
    uint16_t reserved;
};

// Global framebuffer variables
uint32_t* framebuffer;
uint32_t screen_width = 1600;
uint32_t screen_height = 900;
uint32_t pitch= 1600 * 4;

// Function to find framebuffer tag
void init_framebuffer(void* multiboot_info) {
    struct multiboot_tag* tag = (struct multiboot_tag*)((uint8_t*)multiboot_info + 8); // Skip Multiboot2 header
    while (tag->type != MULTIBOOT_TAG_TYPE_END) {
        if (tag->type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER) {
            struct multiboot_tag_framebuffer* fb_tag = (struct multiboot_tag_framebuffer*)tag;

            // Set framebuffer variables
            framebuffer = (uint32_t*)(uintptr_t)fb_tag->framebuffer_addr;
            screen_width = fb_tag->framebuffer_width;
            screen_height = fb_tag->framebuffer_height;
            pitch = fb_tag->framebuffer_pitch;

            return; // Found framebuffer, exit
        }
        tag = (struct multiboot_tag*)((uint8_t*)tag + ((tag->size + 7) & ~7)); // Align to next tag
    }

    // If no framebuffer tag is found, handle the error
    framebuffer = NULL;
}

#endif // __MULTIBOOT_h__