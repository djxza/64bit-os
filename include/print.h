#ifndef __PRINT_h__
#define __PRINT_h__
#define __INCLUDED_PRINT_h__ defined(__PRINT_h__)

//#define _TESTING_VIDEO

#include "types.h"

enum {
    PRINT_COLOR_BLACK = 0,
	PRINT_COLOR_BLUE = 1,
	PRINT_COLOR_GREEN = 2,
	PRINT_COLOR_CYAN = 3,
	PRINT_COLOR_RED = 4,
	PRINT_COLOR_MAGENTA = 5,
	PRINT_COLOR_BROWN = 6,
	PRINT_COLOR_LIGHT_GRAY = 7,
	PRINT_COLOR_DARK_GRAY = 8,
	PRINT_COLOR_LIGHT_BLUE = 9,
	PRINT_COLOR_LIGHT_GREEN = 10,
	PRINT_COLOR_LIGHT_CYAN = 11,
	PRINT_COLOR_LIGHT_RED = 12,
	PRINT_COLOR_PINK = 13,
	PRINT_COLOR_YELLOW = 14,
	PRINT_COLOR_WHITE = 15,
};

void print_clear();
void print_char(char character);
void print_str(const char* string);
void print_err(const char* msg);
void print_set_color(u8 foreground, u8 background);
/*TODO: move strlen to lib*/

#endif // __PRINT_h__