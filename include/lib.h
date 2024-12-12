#ifndef __LIB_h__
#define __LIB_h__

#include "types.h"

#define alloca(x) __builtin_alloca(x)
#define NULL 0

size_t strlen(const char *str);

#endif /* __LIB_h__ */