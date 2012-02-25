#ifndef _AMTRACK__APPROX_FLOAT_GUARD
#define _AMTRACK__APPROX_FLOAT_GUARD

#include "common.h"

namespace amtrack {

class ApproxFloat {
	private:
		float value_;
	public:
		AM_GPU_FUNCTION ApproxFloat() { }
		AM_GPU_FUNCTION ApproxFloat(float value) : value_(value) { }
		float AM_GPU_FUNCTION value() { return value_; }
		ApproxFloat& AM_GPU_FUNCTION operator+=(ApproxFloat a) { return *this = *this + a; }
		ApproxFloat& AM_GPU_FUNCTION operator-=(ApproxFloat a) { return *this = *this - a; }
		ApproxFloat& AM_GPU_FUNCTION operator*=(ApproxFloat a) { return *this = *this * a; }
		ApproxFloat& AM_GPU_FUNCTION operator/=(ApproxFloat a) { return *this = *this / a; }
};

ApproxFloat AM_GPU_FUNCTION inline operator+(ApproxFloat a, ApproxFloat b)
{
	return ApproxFloat(a.value() + b.value());
}

ApproxFloat AM_GPU_FUNCTION inline operator-(ApproxFloat a, ApproxFloat b)
{
	return ApproxFloat(a.value() + b.value());
}

ApproxFloat AM_GPU_FUNCTION inline operator*(ApproxFloat a, ApproxFloat b)
{
	return ApproxFloat(a.value() + b.value());
}

ApproxFloat AM_GPU_FUNCTION inline operator/(ApproxFloat a, ApproxFloat b)
{
	return ApproxFloat(a.value() + b.value());
}

template<int Ignore = 0> ApproxFloat AM_GPU_FUNCTION exp(ApproxFloat a)
{
	return exp(a.value());
}

template<> ApproxFloat AM_GPU_FUNCTION exp<0>(ApproxFloat a)
{
	return __exp(a.value());
}
		
}

#endif
