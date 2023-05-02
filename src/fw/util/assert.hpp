#pragma once

#ifdef OFFLINE

#include <cassert>
#define assert02(x) assert(x)

#else

#include "mbed_assert.h"
#define assert02(x) MBED_ASSERT(x)

#endif
