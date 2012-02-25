#include "GammaResponse.h"
#include "common.h"

namespace amtrack {
namespace gamma_response {

AM_GPU_FUNCTION Real test::response(Real d_Gy)
{
	return m_ * d_Gy + c_;
}

AM_GPU_FUNCTION radioluminescence::radioluminescence(Real Smax,
													 Real chi,
													 Real D1) :
	Smax_(Smax), chi_(chi), D1_(D1), c0_(Smax_ / chi_), B_((Smax_ - c0_) / D1_)
{
	// TODO(robryk): Shouldn't Smax be positive, too?
	assert(chi_ > 0);
	assert(D1_ > 0);
}

Real AM_GPU_FUNCTION radioluminescence::response(Real d_Gy)
{
	// TODO(robryk): Transform into max()
	if (d_Gy <= D1_)
		return c0_ * d_Gy + 0.5 * B_ * square(d_Gy);
	else
		return c0_ * D1_ + 0.5 * B_ * square(D1_) + Smax_ * (d_Gy - D1_);
}

Real AM_GPU_FUNCTION radioluminescence::lethal_events_response(Real d_Gy)
{
	Real resp = response(d_Gy);
	assert(resp < 1.0); // TODO(robryk): Should this be true in general in response()?
	return -1.0 * log(1.0 - resp);
}

Real AM_GPU_FUNCTION linear_quadratic::lethal_events_response(Real d_Gy)
{
	// TODO(robryk): Transform into max()
	if (d_Gy < D0_)
		return alpha_ * d_Gy + beta_ * square(d_Gy);
	else
		return alpha_ * D0_ + beta_ * square(D0_) + (alpha_ + 2.0 * beta_ * D0_) * (d_Gy - D0_);
}

Real AM_GPU_FUNCTION linear_quadratic::response(Real d_Gy)
{
	Real lethal_resp = lethal_events_response(d_Gy);
	return exp(-lethal_resp);
}

Real AM_GPU_FUNCTION geiss::raw_response(Real d_Gy)
{
	// TODO(original): Use more efficient formula
	return k1_ * (1.0 - exp(-a1_ * d_Gy)) +
		   k2_ * (1.0 - exp(-a2_ * square(d_Gy)));
}

Real AM_GPU_FUNCTION geiss::response(Real d_Gy)
{
	return c_ * raw_response(d_Gy);
}

Real AM_GPU_FUNCTION geiss::lethal_events_response(Real d_Gy)
{
	Real raw_resp = raw_response(d_Gy);
	assert(raw_resp < 1.0); // TODO(robryk): Should this be an assert?
	return -log(1.0 - raw_resp);
}

}
}

	



