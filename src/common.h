#ifndef _AMTRACK__COMMON_GUARD
#define _AMTRACK__COMMON_GUARD

#include <cmath>

// TODO(robryk): Provide own assert
#include <cassert>

/*
 * Functions marked with AM_GPU_FUNCTION will be compiled
 * both for GPU as well as for CPU. All functions used
 * in maps, reductions, ... *must* be marked thus.
 */
//#define AM_GPU_FUNCTION __host__ __device__
#define AM_GPU_FUNCTION

/*
 * Helper function for squaring. Use this one in preference
 * to external library functions, because it will get inlined
 */
template<typename T> inline T square(T v)
{
	return v*v;
}

typedef double Real;

#endif

