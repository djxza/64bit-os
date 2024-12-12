#include "print.h"

static const size_t NUM_COLS = 80;
static const size_t NUM_ROWS = 25;

struct Char {
    u8 character;
    u8 color;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
u8 color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        .character = ' ',
        .color = color,
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
}

void print_newline() {
    col = 0;

    if (row < NUM_ROWS - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_COLS - 1);
}

void print_char(char character) {
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col > NUM_COLS) {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        .character = (u8) character,
        .color = color,
    };

    col++;
}

void print_str(const char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (u8) str[i];

        if (character == '\0') {
            return;
        }

        print_char(character);
    }
}

void print_set_color(u8 foreground, u8 background) {
    color = foreground + (background << 4);
}

void print_err(const char *msg)
{
    u8 old_color = color;

    /* color for red */
    print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLACK);
    print_str("err: ");
    color = old_color;
    print_str(msg);
    print_char('\n');
}