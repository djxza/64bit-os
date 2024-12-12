#ifndef __MATH_h__
#define __MATH_h__

#include "types.h"

u32 abs(const i32 x) {
    return x < 0 ? -x : x;
}

#endif // __MATH_h__