#ifndef __STATE_h__
#define __STATE_h__

#include "io.h"

typedef struct {
    keyboard_t keyboard;
} state_t;

state_t init_state();

#endif /* __STATE_h__ */