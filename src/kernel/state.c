#include "state.h"

state_t init_state()
{
    state_t self;
    self.keyboard = init_keyboard();

    return self;
}