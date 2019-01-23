#pragma once

#include <cassert>
// @TEMPHACK: Will eventually have a custom Assert macro lib

#ifdef DEBUG
#define assertCheck assert
#else
#define assertCheck (void)
#endif
